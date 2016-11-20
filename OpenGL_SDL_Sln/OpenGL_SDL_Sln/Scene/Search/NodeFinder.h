#pragma once

#include "SceneNode.h"

namespace TotalGlobal
{
	template<typename NodeType>
	class SceneNodeFinder
	{
	// singleton
	public:
		static SceneNodeFinder<NodeType>& getInstance()
		{
			static SceneNodeFinder<NodeType>    instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}
	private:
		SceneNodeFinder() {}                    // Constructor? (the {} brackets) are needed here.

		// C++ 11
		// =======
		// We can use the better technique of deleting the methods
		// we don't want.
	public:
		SceneNodeFinder(SceneNodeFinder<NodeType> const&) = delete;
		void operator=(SceneNodeFinder<NodeType> const&) = delete;

		// Note: Scott Meyers mentions in his Effective Modern
		//       C++ book, that deleted functions should generally
		//       be public as it results in better error messages
		//       due to the compilers behavior to check accessibility
		//       before deleted status

	public:
		NodeType *FindUp(SceneNode *pRoot, bool rootIncluded = true)
		{
			if (pRoot == nullptr)
				return nullptr;

			SceneNode *actSceneNode = pRoot;
			if (rootIncluded == false)
				actSceneNode = actSceneNode->GetParentNode();

			while (actSceneNode != nullptr)
			{
				NodeType *pNode = dynamic_cast<NodeType *>(actSceneNode);
				if (pNode != nullptr)
					return pNode;

				actSceneNode = actSceneNode->GetParentNode();
			}

			return nullptr;
		}

		//NodeType *FindDown(SceneNode *pRoot, bool rootIncluded = true)
		//{
		//	if (pRoot == nullptr)
		//		return nullptr;

		//	SceneNode *pActSceneNode = pRoot;
		//	if (rootIncluded == false)
		//		pActSceneNode = pActSceneNode->GetParentNode();

		//	while (actSceneNode != nullptr)
		//	{
		//		NodeType *pNode = dynamic_cast<NodeType *>(pActSceneNode);
		//		if (pNode != nullptr)
		//			return pNode;

		//		pActSceneNode = pActSceneNode->GetParentNode();
		//	}

		//	return nullptr;

		//}



	};


}