#pragma once

#include "SceneNodeData.h"
#include "ShaderData.h"

namespace TotalGlobal
{
	class ShaderNodeData : public SceneNodeData
	{
	private:
		ShaderData * m_pShaderData;

	public:
		ShaderNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet,
			const std::string &vertexShaderName, const std::string &fragmentShaderName,
			std::vector<std::string> uniformNames, std::vector<std::string> attributeNames)
			: SceneNodeData(nodeId, parentNodeId, childNodeIdSet)
		{
			m_pShaderData = new ShaderData(vertexShaderName, fragmentShaderName, uniformNames, attributeNames);
		}

		//bool virtual LoadData()
		//{
		//	return m_pShaderData->LoadData();
		//}

		virtual SceneData *GetData()
		{
			return m_pShaderData;
		}

		ShaderData * GetShaderData(){ return m_pShaderData; }


	};

}