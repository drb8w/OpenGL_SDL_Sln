#include "ObjModelLoader.h"

#include "objloader.hpp"
#include "texture.hpp"

#include "SOIL.h"

namespace TotalGlobal
{
	// load model
	bool ObjModelLoader::Load()
	{
		// clear error state
		glGetError();

		// -------------------------------------------------------------------
		// Load the texture
		// -------------------------------------------------------------------

		glActiveTexture(m_TextureUnitId);

		// version 1.0: use a texture generator
		// ---------------------------------------------------------
		//m_TextureId = loadDDS(m_Filename_texture.c_str());

		/* load an image file directly as a new OpenGL texture */
		//m_TextureId = SOIL_load_OGL_texture
		//	(
		//	m_Filename_texture.c_str(),
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		//	);

		//m_TextureId = SOIL_load_OGL_texture(m_Filename_texture.c_str(),
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
		//	);

		// version 2.0: generate own texture out of loaded file
		// ---------------------------------------------------------
		int width;
		int height;
		int channels;
		unsigned char *pImageData = SOIL_load_image(m_Filename_texture.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
		if (pImageData != nullptr)
		{
			glGenTextures(1, &m_TextureId);
			glBindTexture(GL_TEXTURE_2D, m_TextureId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData);

			glGenerateMipmap(GL_TEXTURE_2D);

			SOIL_free_image_data(pImageData);

			const char *result = SOIL_last_result();

		}
		GLenum err = glGetError();

		// -------------------------------------------------------------------
		// Read our .obj file
		// -------------------------------------------------------------------

		bool res = loadOBJ(m_Filename_obj.c_str(), m_Vertices, m_TextureCoordinates, m_Normals);

		// all model data into one array, 
		// i.e. cartesian coordinates, texture UV coordinates, vertex normals
		m_pModelData = new float[m_Vertices.size()*(3+2+3)];
		for (unsigned int idx = 0; idx < m_Vertices.size(); idx++)
		{
			m_pModelData[idx * 8] = m_Vertices[idx].x;
			m_pModelData[idx * 8 + 1] = m_Vertices[idx].y;
			m_pModelData[idx * 8 + 2] = m_Vertices[idx].z;

			m_pModelData[idx * 8 + 3] = m_TextureCoordinates[idx].r;
			m_pModelData[idx * 8 + 4] = m_TextureCoordinates[idx].s;
			
			m_pModelData[idx * 8 + 5] = m_Normals[idx].x;
			m_pModelData[idx * 8 + 6] = m_Normals[idx].y;
			m_pModelData[idx * 8 + 7] = m_Normals[idx].z;
		}

		m_ModelDataSize = m_Vertices.size() * (3 + 2 + 3) * sizeof(float);

		// -------------------------------------------------------------------
		// create a vertex buffer object and a vertex array object
		// -------------------------------------------------------------------

		// https://open.gl/drawing
		glGenBuffers(1, &m_VBO); // Generate 1 buffer

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_ModelDataSize, m_pModelData, GL_STATIC_DRAW);

		// Create Vertex Array Object
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// stride, or how many bytes are between each position attribute in the array
		// offset, or how many bytes from the start of the array the attribute occurs

		if (m_AttribId_CoordCart != UINT_MAX)
		{
			glEnableVertexAttribArray(m_AttribId_CoordCart); // 0
			glVertexAttribPointer(m_AttribId_CoordCart, 3, GL_FLOAT, GL_FALSE, (2 + 3) * sizeof(float), m_pModelData);  // 3 floats f�r Position
		}
		if (m_AttribId_CoordTex != UINT_MAX)
		{
			glEnableVertexAttribArray(m_AttribId_CoordTex); // 1
			glVertexAttribPointer(m_AttribId_CoordTex, 2, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(float), m_pModelData + 3); // 2 floats als Textur-Koordinaten 
		}
		if (m_AttribId_NormCart != UINT_MAX)
		{
			glEnableVertexAttribArray(m_AttribId_NormCart); // 2
			glVertexAttribPointer(m_AttribId_NormCart, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), m_pModelData + (3 + 2)); // 3 floats f�r den Normalenvektor
		}
		// unbind VAO and VBO to avoid accidental changes
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return true;
	}





}