#pragma once

#include "SceneNode.h"
#include "ModelData.h"

namespace TotalGlobal
{

	class ModelNode : public SceneNode
	{
	private:
		ModelData *m_pModelData = nullptr;

	public:
		ModelNode(ModelData *pModelData)
			: SceneNode(), m_pModelData(pModelData)
		{
		}

		ModelNode(SceneNode *pParentNodeData,
			std::vector<SceneNode *> childNodeDataSet,
			ModelData *pModelData)
			: SceneNode(pParentNodeData, childNodeDataSet), m_pModelData(pModelData)
		{
		}

		ModelData *GetModelData() const
		{
			return m_pModelData;
		}

		virtual bool LoadData();

		virtual bool Render();

	};


}