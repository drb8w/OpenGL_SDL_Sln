#include "SceneNodeFactory.h"

#include "ModelNodeData.h"
#include "ShaderNodeData.h"
#include "TransformNodeData.h"
#include "CameraNodeData.h"
#include "ViewPortNodeData.h"

#include "ModelNode.h"
#include "ShaderNode.h"
#include "TransformNode.h"
#include "CameraNode.h"
#include "ViewPortNode.h"

namespace TotalGlobal
{
	SceneNode *SceneNodeFactory::CreateSceneNode(SceneData *pNodeData, SceneNode *pParentNode)
	{
		ModelData *pModelData = dynamic_cast<ModelData *>(pNodeData);
		SceneNode *pSceneNode = nullptr;
		if (pModelData != nullptr)
			pSceneNode = new ModelNode(pModelData);

		ShaderData *pShaderData = dynamic_cast<ShaderData *>(pNodeData);
		if (pShaderData != nullptr)
			pSceneNode = new ShaderNode(pShaderData);
		
		TransformData *pTransformData = dynamic_cast<TransformData *>(pNodeData);
		if (pTransformData != nullptr)
			pSceneNode = new TransformNode(pTransformData);
		
		CameraData *pCameraData = dynamic_cast<CameraData *>(pNodeData);
		if (pCameraData != nullptr)
			pSceneNode = new CameraNode(pCameraData);

		ViewPortData *pViewPortData = dynamic_cast<ViewPortData *>(pNodeData);
		if (pViewPortData != nullptr)
			pSceneNode = new ViewPortNode(pViewPortData);

		// Light

		if (pSceneNode == nullptr)
			return nullptr;

		pSceneNode->SetParent(pParentNode);
		if (pParentNode != nullptr)
			pParentNode->AddChild(pSceneNode);
		
		return pSceneNode;
	}


}