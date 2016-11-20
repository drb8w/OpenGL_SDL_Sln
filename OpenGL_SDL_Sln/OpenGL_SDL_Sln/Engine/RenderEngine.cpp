#include "RenderEngine.h"

#include <algorithm>

#include "shader.hpp"
#include "SceneNodeFactory.h"
#include "GUIDFinder.h"

namespace TotalGlobal
{

	bool RenderingEngine::Init(const std::vector<SceneNodeData *> &sceneNodeDataSet)
	{
		// traverse scene graph data and build scene graph

		m_sceneNodeDataSet = sceneNodeDataSet;

		// find root node
		std::vector<SceneNodeData *>::const_iterator it = std::find_if(sceneNodeDataSet.begin(), sceneNodeDataSet.end(), ParentGUIDFinder(GUIDFinder::ZeroGuid));
		if (it == sceneNodeDataSet.end())
			return false;

		if (it == sceneNodeDataSet.end())
			return false;

		m_pSceneNodeDataRoot = *it;

		m_pSceneNodeRoot = Init(m_pSceneNodeDataRoot, nullptr, sceneNodeDataSet);

		if (m_pSceneNodeRoot == nullptr)
			return false;

		return true;
	}

	SceneNode *RenderingEngine::Init(SceneNodeData *pActSceneNodeData, SceneNode *pPartentSceneNode, const std::vector<SceneNodeData *> &sceneNodeDataSet)
	{
		if (pActSceneNodeData == nullptr)
			return nullptr;

		//// early loading
		//// load the data
		//pActSceneNodeData->LoadData();

		// create corresponding scene graph node
		SceneNode *pActSceneNode = SceneNodeFactory::getInstance().CreateSceneNode(pActSceneNodeData->GetData(), pPartentSceneNode);

		// late loading
		pActSceneNode->LoadData();

		// traverse children
		std::vector<GUID> children = pActSceneNodeData->GetChildNodeIdSet();
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			// find child node
			std::vector<SceneNodeData *>::const_iterator it_child = std::find_if(sceneNodeDataSet.begin(), sceneNodeDataSet.end(), GUIDFinder(*it));

			if (it_child != sceneNodeDataSet.end())
			{
				SceneNodeData *childSceneNodeData = *it_child;
				Init(childSceneNodeData, pActSceneNode, sceneNodeDataSet);
			}
		}

		return pActSceneNode;
	}

	bool RenderingEngine::Render()
	{
		// traverse scene graph

		// doing it implicit and let node do recursive calling
		return m_pSceneNodeRoot->Render();

	}

}