#include "ModelNode.h"

#include "ShaderNode.h"
#include "ShaderData.h"
#include "NodeFinder.h"

namespace TotalGlobal
{

	bool ModelNode::LoadData()
	{
		// get the necessary shader attributes from parent shader node

		SceneNodeFinder<ShaderNode> &shaderNodeFinder = SceneNodeFinder<ShaderNode>::getInstance();
		ShaderNode *pShaderNode = shaderNodeFinder.FindUp(this);

		if (pShaderNode != nullptr)
		{
			ShaderData *pShaderData = pShaderNode->GetShaderData();

			std::string attribName_CoordCart = m_pModelData->GetAttributeName(AttributeType::CoordCart);
			GLuint attribId_CoordCart = pShaderData->GetAttributeId(attribName_CoordCart);

			std::string attribName_CoordTex = m_pModelData->GetAttributeName(AttributeType::CoordTex);
			GLuint attribId_CoordTex = pShaderData->GetAttributeId(attribName_CoordTex);

			std::string attribName_NormCart = m_pModelData->GetAttributeName(AttributeType::NormCart);
			GLuint attribId_NormCart = pShaderData->GetAttributeId(attribName_NormCart);

			return m_pModelData->LoadModel(attribId_CoordCart, attribId_CoordTex, attribId_NormCart);
		}

		return m_pModelData->LoadData();
	}

	bool ModelNode::Render()
	{
		// TODO: change upon usage of element buffers !!!
		glBindVertexArray(m_pModelData->GetVAOId());
		glDrawArrays(GL_TRIANGLES, 0, m_pModelData->GetNoVertices());

		// traverse the children
		RenderChildren();

		return true;
	}

}