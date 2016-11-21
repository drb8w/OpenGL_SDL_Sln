#pragma once

#include <glm/mat4x4.hpp>

#include "SceneNode.h"
#include "ViewPortData.h"

namespace TotalGlobal
{
	class ViewPortNode : public SceneNode
	{
	private:
		ViewPortData *m_pViewPortData;

	public:
		ViewPortNode(ViewPortData *pViewPortData)
			: SceneNode(), m_pViewPortData(pViewPortData)
		{}

		ViewPortNode(SceneNode * parentNodeData,
			std::vector<SceneNode *> childNodeDataSet, ViewPortData *pViewPortData)
			: SceneNode(parentNodeData, childNodeDataSet), m_pViewPortData(pViewPortData)
		{}

		ViewPortData *GetTransformData()
		{
			return m_pViewPortData;
		}

		virtual bool LoadData()
		{
			m_pViewPortData->LoadData();
			return true;
		}

		virtual bool Render()
		{
			glViewport(0, 0, m_pViewPortData->GetWidth(), m_pViewPortData->GetHeight());

			// ===============================================================================================================

			// traverse the children
			RenderChildren();

			return true;
		}

	};

}