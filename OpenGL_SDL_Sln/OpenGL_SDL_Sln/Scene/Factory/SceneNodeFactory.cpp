#include "SceneNodeFactory.h"

#include "ModelNodeData.h"
#include "ShaderNodeData.h"
#include "TransformNodeData.h"

#include "ModelNode.h"
#include "ShaderNode.h"
#include "TransformNode.h"

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
		
		if (pSceneNode == nullptr)
			return nullptr;

		pSceneNode->SetParent(pParentNode);
		if (pParentNode != nullptr)
			pParentNode->AddChild(pSceneNode);
		
		return pSceneNode;
	}


}