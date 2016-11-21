#pragma once

#include <glm/mat4x4.hpp>

#include "SceneNode.h"
#include "TransformData.h"

namespace TotalGlobal
{
	class TransformNode : public SceneNode
	{
	private:
		TransformData *m_pTransform;

	public:
		TransformNode(TransformData *pTransform)
			: SceneNode(), m_pTransform(pTransform)
		{}

		TransformNode(SceneNode * parentNodeData,
			std::vector<SceneNode *> childNodeDataSet, TransformData *pTransform)
			: SceneNode(parentNodeData, childNodeDataSet), m_pTransform(pTransform)
		{}

		TransformData *GetTransformData()
		{
			return m_pTransform;
		}

		virtual bool LoadData();

		glm::mat4x4 GetLocalTransform();
		glm::mat4x4 GetGlobalTransform();

		virtual bool Render();

	};

}