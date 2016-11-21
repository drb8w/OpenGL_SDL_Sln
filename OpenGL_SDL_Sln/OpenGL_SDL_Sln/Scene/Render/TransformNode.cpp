#include "TransformNode.h"

#include "NodeFinder.h"

namespace TotalGlobal
{

	bool TransformNode::LoadData()
	{
		m_pTransform->LoadData();

		return true;
	}

	glm::mat4x4 TransformNode::GetLocalTransform()
	{
		return m_pTransform->GetTransform();
	}

	glm::mat4x4 TransformNode::GetGlobalTransform()
	{
		TransformNode *pParentTransformNode = SceneNodeFinder<TransformNode>::getInstance().FindUp(this, false);

		if (pParentTransformNode != nullptr)
			return pParentTransformNode->GetGlobalTransform() * m_pTransform->GetTransform();

		return m_pTransform->GetTransform();
	}

	bool TransformNode::Render()
	{
		// TODO: update transform matrices

		// ===============================================================================================================

		// traverse the children
		RenderChildren();

		return true;
	}

}