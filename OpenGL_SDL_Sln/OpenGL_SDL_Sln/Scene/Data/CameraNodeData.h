#pragma once

#include "SceneNodeData.h"
#include "CameraData.h"

namespace TotalGlobal
{

	class CameraNodeData : public SceneNodeData
	{
	private:
		CameraData * m_CameraData = nullptr;

	public:
		CameraNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet, glm::mat4x4 viewTransform, glm::mat4x4 projectionTransform)
			: SceneNodeData(nodeId, parentNodeId, childNodeIdSet)
		{
			m_CameraData = new CameraData(viewTransform, projectionTransform);
		}
	
		virtual SceneData *GetData()
		{
			return m_CameraData;
		}
	};

}