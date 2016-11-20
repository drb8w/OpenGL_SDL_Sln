#pragma once

#include <vector>

namespace TotalGlobal
{

	class SceneNode
	{
	protected:
		SceneNode * m_pParentNode = nullptr;
		std::vector<SceneNode *> m_ChildNodeSet;

	public:
		SceneNode() {}

		SceneNode(SceneNode * pParentNode,
			std::vector<SceneNode *> childNodeSet)
			: m_pParentNode(pParentNode), m_ChildNodeSet(childNodeSet)
		{
		}

		SceneNode * GetParentNode()
		{
			return m_pParentNode;
		}

		std::vector<SceneNode *> &GetChildNodeSet()
		{
			return m_ChildNodeSet;
		}

		bool SetParent(SceneNode *pParentNode)
		{
			m_pParentNode = pParentNode;
			return true;
		}

		bool AddChild(SceneNode *pChildNode)
		{
			m_ChildNodeSet.push_back(pChildNode);
			return true;
		}

		virtual bool LoadData() = 0;

		virtual bool Render() = 0;

	};

}