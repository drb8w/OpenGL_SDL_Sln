#pragma once

#include <vector>
#include <map>
#include <string>

#include "ObjModelLoader.h"
#include "SceneData.h"

namespace TotalGlobal
{
	enum AttributeType { CoordCart, CoordTex, NormCart };

	class ModelData : public SceneData
	{
	private:
		// input
		std::string m_ObjectFilename;
		std::string m_TextureFilename;

		std::map<AttributeType, std::string> m_AttributeTypeNameSet;

		// output
		GLuint m_TextureUnitId = UINT_MAX;
		GLuint m_TextureId = UINT_MAX;
		GLuint m_VBOId = UINT_MAX;
		GLuint m_VAOId = UINT_MAX;
		GLsizei m_No_Vertices = 0;

	public:
		ModelData(const std::string &objectFilename, const std::string &textureFilename, 
			const std::map<AttributeType, std::string> &attributeTypeNameSet)
			: m_ObjectFilename(objectFilename), m_TextureFilename(textureFilename), m_AttributeTypeNameSet(attributeTypeNameSet)
		{
		}

		ModelData(const ModelData& other)
		{
			// check for self-assignment
			if (&other == this)
				return;

			m_ObjectFilename = other.m_ObjectFilename;
			m_TextureFilename = other.m_TextureFilename;

		}

		ModelData& operator=(const ModelData& other)
		{
			// check for self-assignment
			if (&other == this)
				return *this;

			m_ObjectFilename = other.m_ObjectFilename;
			m_TextureFilename = other.m_TextureFilename;

			return *this;
		}

		std::string GetObjectFilename(){ return m_ObjectFilename; }
		std::string GetTextureFilename(){ return m_TextureFilename; }
		std::map<AttributeType, std::string> GetAttributeTypeNameSet(){ return m_AttributeTypeNameSet; }

		std::string GetAttributeName(AttributeType attributeType)
		{
			auto it = m_AttributeTypeNameSet.find(attributeType);
			if (it != m_AttributeTypeNameSet.end())
				return it->second;

			return "";
		}

		virtual bool LoadData()
		{
			// without connection to shader node use default values

			GLuint attribId_CoordCart = 0;
			GLuint attribId_CoordTex = 1;
			GLuint attribId_NormCart = 2;

			return LoadModel(attribId_CoordCart, attribId_CoordTex, attribId_NormCart);
		}

		bool LoadModel(GLuint attribId_CoordCart, GLuint attribId_CoordTex, GLuint attribId_NormCart)
		{
			if (m_VBOId != UINT_MAX)
				return false;

			ObjModelLoader loader(m_ObjectFilename, m_TextureFilename,
				attribId_CoordCart, attribId_CoordTex, attribId_NormCart);

			if (loader.Load())
			{
				m_TextureUnitId = loader.GetTextureUnitId();
				m_TextureId = loader.GetTextureId();
				m_VBOId = loader.GetVBO();
				m_VAOId = loader.GetVAO();
				m_No_Vertices = loader.GetVertices().size();
			}
			return true;
		}

		GLuint GetTextureUnitId()
		{
			return m_TextureUnitId;
		}

		GLuint GetTextureId()
		{
			return m_TextureId;
		}

		GLuint GetVBOId()
		{
			return m_VBOId;
		}

		GLuint GetVAOId()
		{
			return m_VAOId;
		}

		GLsizei GetNoVertices()
		{
			return m_No_Vertices;
		}
		
	};

}