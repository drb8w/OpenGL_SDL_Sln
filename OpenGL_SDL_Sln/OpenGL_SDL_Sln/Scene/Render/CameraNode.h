#pragma once

#include "SceneNode.h"
#include "TransformNode.h"
#include "CameraData.h"
#include "NodeFinder.h"

namespace TotalGlobal
{

	class CameraNode : public SceneNode
	{
	private:
		CameraData *m_pCameraData;
	
	public:
		CameraNode(CameraData *pCameraData) : SceneNode(), m_pCameraData(pCameraData) {}

		CameraNode(SceneNode * pParentNode,
			std::vector<SceneNode *> childNodeSet, CameraData *pCameraData)
			: SceneNode(pParentNode, childNodeSet), m_pCameraData(pCameraData)
		{
		}

		virtual bool LoadData()
		{
			m_pCameraData->LoadData();
			return true;
		}

		CameraData *GetCameraData()
		{
			return m_pCameraData;
		}

		glm::mat4x4 GetGlobalViewTransform()
		{
			TransformNode *pParentTransformNode = SceneNodeFinder<TransformNode>::getInstance().FindUp(this, false);

			if (pParentTransformNode != nullptr)
				return pParentTransformNode->GetGlobalTransform() * m_pCameraData->GetViewTransform();
		
			return m_pCameraData->GetViewTransform();
		}

		glm::mat4x4 GetProjectionTransform()
		{
			return m_pCameraData->GetProjectionTransform();
		}

		virtual bool Render()
		{
			// ===============================================================================================================

			// traverse the children
			RenderChildren();

			return true;
		}
	};

}