#pragma once

#include <guiddef.h>
#include <memory>

#include "SceneNodeData.h"

namespace TotalGlobal
{
	class GUIDFinder
	{
	public:
		static GUID ZeroGuid;

	protected:
		GUID m_Guid;

	public:
		GUIDFinder(GUID guid) : m_Guid(guid) {}

		bool operator()(SceneNodeData * pSceneNodeData) const
		{
			if (pSceneNodeData->GetNodeId() == m_Guid)
				return true;
			return false;
		}

		static bool IsNull(GUID guid) {
			if (guid == GUIDFinder::ZeroGuid)
				return true;
			return false;
		}

	};

	class ParentGUIDFinder : public GUIDFinder
	{
	public:
		ParentGUIDFinder(GUID guid) : GUIDFinder(guid) {}

		bool operator()(SceneNodeData * pSceneNodeData) const
		{
			if (pSceneNodeData->GetParentNodeId() == m_Guid)
				return true;
			return false;
		}

	};

	class ChildGUIDFinder : public GUIDFinder
	{
	public:
		ChildGUIDFinder(GUID guid) : GUIDFinder(guid) {}

		bool operator()(SceneNodeData * pSceneNodeData) const
		{
			std::vector<GUID> childNodeIdSet = pSceneNodeData->GetChildNodeIdSet();

			for (auto it = childNodeIdSet.begin(); it != childNodeIdSet.end(); ++it)
				if (*it == m_Guid)
					return true;

			return false;
		}

	};
}