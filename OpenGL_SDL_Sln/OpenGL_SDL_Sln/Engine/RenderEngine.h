#pragma once

#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>

//#include "ObjModelLoader.h"
//#include "ShaderData.h"
//#include "ModelData.h"
#include "SceneNodeData.h"
#include "SceneNode.h"

namespace TotalGlobal
{

	class RenderingEngine
	{
	private:
		//std::vector<ObjModelLoader *> m_Loaders;

		std::vector<SceneNodeData *> m_sceneNodeDataSet;

		SceneNodeData *m_pSceneNodeDataRoot = nullptr;
		SceneNode *m_pSceneNodeRoot = nullptr;


	public:
		bool Init(const std::vector<SceneNodeData *> &sceneNodeDataSet);

		bool Render();

	private:
		SceneNode *Init(SceneNodeData *pActSceneNodeData, SceneNode *pPartentSceneNode, const std::vector<SceneNodeData *> &sceneNodeDataSet);

		//bool LoadSceneGraph(SceneNodeData &sceneNodeDataRoot);

	};


}