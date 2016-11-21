#pragma once

#include <glm/mat4x4.hpp>

#include "SceneNodeData.h"

#include "ViewPortData.h"

namespace TotalGlobal
{

	class ViewPortNodeData : public SceneNodeData
	{
	private:
		ViewPortData *m_pViewPortData;

	public:
		ViewPortNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet, GLsizei width, GLsizei height)
			: SceneNodeData(nodeId, parentNodeId, childNodeIdSet)
		{
			m_pViewPortData = new ViewPortData(width, height);
		}

		//bool virtual LoadData()
		//{
		//	return true;
		//}

		virtual SceneData *GetData()
		{
			return m_pViewPortData;
		}

		ViewPortData *GetTransformData()
		{
			return m_pViewPortData;
		}

	};

}