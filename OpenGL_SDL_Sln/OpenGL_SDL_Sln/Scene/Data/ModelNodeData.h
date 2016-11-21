#pragma once

#include "SceneNodeData.h"

#include "ModelData.h"

namespace TotalGlobal
{

	class ModelNodeData : public SceneNodeData
	{
	private:
		// input
		// version 2.0
		ModelData *m_pModelData = nullptr;

	public:
		ModelNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet,
			const std::string &objectFilename, const std::string &textureFilename,
			const std::map<UniformType, std::string> &uniformTypeNameSet,
			const std::map<AttributeType, std::string> &attributeTypeNameSet)
			: SceneNodeData(nodeId, parentNodeId, childNodeIdSet)
		{
			m_pModelData = new ModelData(objectFilename, textureFilename, uniformTypeNameSet, attributeTypeNameSet);
		}

		//virtual bool LoadData()
		//{
		//	// without connection to shader node use default values
		//	return m_pModelData->LoadData();
		//}

		virtual SceneData *GetData()
		{
			return m_pModelData;
		}

		ModelData *GetModelData()
		{
			return m_pModelData;
		}

	};

}