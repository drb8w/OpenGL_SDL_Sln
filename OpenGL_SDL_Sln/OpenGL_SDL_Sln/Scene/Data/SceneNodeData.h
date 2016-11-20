#pragma once

#include <vector>
#include <guiddef.h>

#include "SceneData.h"

namespace TotalGlobal
{

	class SceneNodeData
	{
	private:
		GUID m_NodeId;
		GUID m_ParentNodeId;
		std::vector<GUID> m_ChildNodeIdSet;

	public:
		SceneNodeData(GUID nodeId, GUID parentNodeId, std::vector<GUID> childNodeIdSet)
			: m_NodeId(nodeId), m_ParentNodeId(parentNodeId), m_ChildNodeIdSet(childNodeIdSet)
		{
		}

		//virtual bool LoadData() = 0;
		virtual SceneData *GetData() = 0;

		GUID GetNodeId()
		{
			return m_NodeId;
		}

		GUID GetParentNodeId()
		{
			return m_ParentNodeId;
		}

		std::vector<GUID> GetChildNodeIdSet()
		{
			return m_ChildNodeIdSet;
		}
	};


}