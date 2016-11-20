#include "TransformNode.h"

namespace TotalGlobal
{

	bool TransformNode::LoadData()
	{
		m_pTransform->LoadData();

		return true;
	}

	bool TransformNode::Render()
	{
		// TODO: update transform matrices

		// traverse the children
		RenderChildren();

		return true;
	}

}