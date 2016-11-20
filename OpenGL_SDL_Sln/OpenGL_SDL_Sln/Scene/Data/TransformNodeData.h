#pragma once

#include <glm/mat4x4.hpp>

#include "SceneNodeData.h"

#include "TransformData.h"

namespace TotalGlobal
{

	class TransformNodeData : public SceneNodeData
	{
	private:
		TransformData *m_pTransform;


	public:
		TransformNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet, glm::mat4x4 transform)
			: SceneNodeData(nodeId, parentNodeId, childNodeIdSet)
		{
			m_pTransform = new TransformData(transform);
		}

		//bool virtual LoadData()
		//{
		//	return true;
		//}

		virtual SceneData *GetData()
		{
			return m_pTransform;
		}

		TransformData *GetTransformData()
		{
			return m_pTransform;
		}

	};

}