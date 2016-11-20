#pragma once

#include "SceneNode.h"
#include "ShaderData.h"

namespace TotalGlobal
{

	class ShaderNode : public SceneNode
	{
	private:
		ShaderData * m_pShaderData;

	public:
		ShaderNode(ShaderData *pShaderData)
			: SceneNode(), m_pShaderData(pShaderData)
		{
		}

		ShaderNode(SceneNode * pParentNode,
			std::vector<SceneNode *> childNodeSet, ShaderData *pShaderData)
			: SceneNode(pParentNode, childNodeSet), m_pShaderData(pShaderData)
		{
		}

		ShaderData *GetShaderData(){ return m_pShaderData; }

		virtual bool LoadData();

		virtual bool Render();

	};

}