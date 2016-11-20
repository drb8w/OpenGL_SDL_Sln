#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <GL/glew.h>

namespace TotalGlobal
{
	class ObjModelLoader
	{
	private:
		// input
		std::string m_Filename_obj;
		std::string m_Filename_texture;

		// output
		GLuint m_TextureUnitId = 7; // TODO: check for a free texture unit
		GLuint m_TextureId;
		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec2> m_TextureCoordinates;
		std::vector<glm::vec3> m_Normals;

		float *m_pModelData = nullptr;
		GLsizeiptr m_ModelDataSize = 0;

		GLuint m_VBO;
		GLuint m_VAO;

		// set with glBindAttribLocation or get with glGetAttribLocation from corresponding vertex program
		GLuint m_AttribId_CoordCart = 0;
		GLuint m_AttribId_CoordTex = 1;
		GLuint m_AttribId_NormCart = 2;

	public:
		ObjModelLoader(const std::string &filename_obj, const std::string &filename_texture)
			: m_Filename_obj(filename_obj), m_Filename_texture(filename_texture)
		{}

		ObjModelLoader(const std::string &filename_obj, const std::string &filename_texture,
			GLuint attribId_CoordCart, GLuint attribId_CoordTex, GLuint attribId_NormCart)
			: m_Filename_obj(filename_obj), m_Filename_texture(filename_texture),
			m_AttribId_CoordCart(attribId_CoordCart), m_AttribId_CoordTex(attribId_CoordTex), m_AttribId_NormCart(attribId_NormCart)
		{}

		// load model
		bool Load();

		// access data
		GLuint GetTextureUnitId()
		{
			return m_TextureUnitId;
		}

		GLuint GetTextureId()
		{
			return m_TextureId;
		}

		std::vector<glm::vec3> &GetVertices()
		{
			return m_Vertices;
		}

		std::vector<glm::vec2> &GetTextureCoordinates()
		{
			return m_TextureCoordinates;
		}

		std::vector<glm::vec3> &GetNormals()
		{
			return m_Normals;
		}
		
		GLuint GetVBO()
		{
			return m_VBO;
		}

		GLuint GetVAO()
		{
			return m_VAO;
		}

	};



}