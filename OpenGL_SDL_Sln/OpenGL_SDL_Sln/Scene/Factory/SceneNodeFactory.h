#pragma once

#include "SceneNode.h"
#include "SceneNodeData.h"

namespace TotalGlobal
{

	class SceneNodeFactory
	{
		// singleton pattern
	public:
		static SceneNodeFactory& getInstance()
		{
			static SceneNodeFactory    instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}
	private:
		SceneNodeFactory() {}                    // Constructor? (the {} brackets) are needed here.

		// C++ 11
		// =======
		// We can use the better technique of deleting the methods
		// we don't want.
	public:
		SceneNodeFactory(SceneNodeFactory const&) = delete;
		void operator=(SceneNodeFactory const&) = delete;

		// Note: Scott Meyers mentions in his Effective Modern
		//       C++ book, that deleted functions should generally
		//       be public as it results in better error messages
		//       due to the compilers behavior to check accessibility
		//       before deleted status


	public:

		//SceneNode *CreateSceneNode(SceneNodeData *pNodeData, SceneNode *pParentNode);
		SceneNode *CreateSceneNode(SceneData *pNodeData, SceneNode *pParentNode);

	};


}