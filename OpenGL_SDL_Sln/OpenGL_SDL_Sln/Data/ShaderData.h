#pragma once

#include <string>
#include <map>
#include <vector>

#include <GL/glew.h>

#include "objloader.hpp"
#include "shader.hpp"

#include "SceneData.h"

namespace TotalGlobal
{
	class ShaderData : public SceneData
	{
	private:
		// input
		std::string m_VertexShaderName;
		std::string m_FragmentShaderName;
		std::vector<std::string> m_UniformNames;
		std::vector<std::string> m_AttributeNames;

		// output
		GLuint m_ProgramId = UINTMAX_MAX;
		std::map<std::string, GLuint> m_UniformNameIdMap;
		std::map<std::string, GLuint> m_AttributeNameIdMap;

	public:
		ShaderData(const std::string &vertexShaderName, const std::string &fragmentShaderName,
			std::vector<std::string> uniformNames, std::vector<std::string> attributeNames)
		: m_VertexShaderName(vertexShaderName), m_FragmentShaderName(fragmentShaderName),
		m_UniformNames(uniformNames), m_AttributeNames(attributeNames)
		{
		}

		ShaderData(const ShaderData& other)
		{
			// check for self-assignment
			if (&other == this)
				return;

			m_VertexShaderName = other.m_VertexShaderName;
			m_FragmentShaderName = other.m_FragmentShaderName;
			m_UniformNames = other.m_UniformNames;
			m_AttributeNames = other.m_AttributeNames;

			if (m_ProgramId == UINTMAX_MAX)
			{
				LoadShader();
			}
			else
			{
				m_ProgramId = other.m_ProgramId;

				// deep copy of maps
				for (std::map<std::string, GLuint>::const_iterator it = other.m_UniformNameIdMap.cbegin(); it != other.m_UniformNameIdMap.cend(); ++it)
					m_UniformNameIdMap.insert(std::pair<std::string, GLuint>(it->first, it->second));

				for (std::map<std::string, GLuint>::const_iterator it = other.m_AttributeNameIdMap.cbegin(); it != other.m_AttributeNameIdMap.cend(); ++it)
					m_AttributeNameIdMap.insert(std::pair<std::string, GLuint>(it->first, it->second));
			}
		}

		ShaderData& operator=(const ShaderData& other)
		{
			// check for self-assignment
			if (&other == this)
				return *this;

			m_VertexShaderName = other.m_VertexShaderName;
			m_FragmentShaderName = other.m_FragmentShaderName;
			m_UniformNames = other.m_UniformNames;
			m_AttributeNames = other.m_AttributeNames;

			if (m_ProgramId == UINTMAX_MAX)
			{
				LoadShader();
			}
			else
			{
				m_ProgramId = other.m_ProgramId;

				// deep copy of maps
				for (std::map<std::string, GLuint>::const_iterator it = other.m_UniformNameIdMap.cbegin(); it != other.m_UniformNameIdMap.cend(); ++it)
					m_UniformNameIdMap.insert(std::pair<std::string, GLuint>(it->first, it->second));

				for (std::map<std::string, GLuint>::const_iterator it = other.m_AttributeNameIdMap.cbegin(); it != other.m_AttributeNameIdMap.cend(); ++it)
					m_AttributeNameIdMap.insert(std::pair<std::string, GLuint>(it->first, it->second));
			}

			return *this;
		}

		std::string GetVertexShaderName(){ return m_VertexShaderName; }
		std::string GetFragmentShaderName(){ return m_FragmentShaderName; }
		std::vector<std::string> GetUniformNames(){ return m_UniformNames; }
		std::vector<std::string> GetAttributeNames(){ return m_AttributeNames; }

		GLuint GetProgramId(){ return m_ProgramId; }
		std::map<std::string, GLuint> GetUniformNameIdMap(){ return m_UniformNameIdMap; }
		std::map<std::string, GLuint> GetAttributeNameIdMap(){ return m_AttributeNameIdMap; }

		GLuint GetAttributeId(const std::string & attributeName)
		{
			auto it = m_AttributeNameIdMap.find(attributeName);

			if (it != m_AttributeNameIdMap.end())
				return it->second;

			return UINT_MAX;
		}

		virtual bool LoadData()
		{
			return LoadShader();
		}

		bool LoadShader()
		{
			if (m_ProgramId != UINTMAX_MAX)
				return false;

			// Create and compile our GLSL program from the shaders
			m_ProgramId = ::LoadShaders(m_VertexShaderName.c_str(), m_FragmentShaderName.c_str());

			// glGetUniformLocation
			for (auto it = m_UniformNames.begin(); it != m_UniformNames.end(); ++it)
				m_UniformNameIdMap.insert(std::pair<std::string, GLuint>(*it, glGetUniformLocation(m_ProgramId, it->c_str())));

			// glBindAttribLocation or get with glGetAttribLocation
			for (auto it = m_AttributeNames.begin(); it != m_AttributeNames.end(); ++it)
				m_AttributeNameIdMap.insert(std::pair<std::string, GLuint>(*it, glGetAttribLocation(m_ProgramId, it->c_str())));

			return true;
		}


	};

}