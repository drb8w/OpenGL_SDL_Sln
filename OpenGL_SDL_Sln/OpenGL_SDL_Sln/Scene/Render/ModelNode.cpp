#include "ModelNode.h"

#include <glm/gtc/type_ptr.hpp>

#include "ShaderNode.h"
#include "TransformNode.h"
#include "CameraNode.h"
#include "ShaderData.h"
#include "NodeFinder.h"

#include "MathMisc.h"

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
		// get the necessary shader uniforms from parent shader node
		SceneNodeFinder<ShaderNode> &shaderNodeFinder = SceneNodeFinder<ShaderNode>::getInstance();
		ShaderNode *pShaderNode = shaderNodeFinder.FindUp(this);

		if (pShaderNode != nullptr)
		{
			ShaderData *pShaderData = pShaderNode->GetShaderData();
			
			SceneNodeFinder<TransformNode> &transformNodeFinder = SceneNodeFinder<TransformNode>::getInstance();
			TransformNode *pTransformNode = transformNodeFinder.FindUp(this);

			// set model matrix
			// ---------------------------------------------------------------------------------------------
			std::string uniformName_ModelMatrix = m_pModelData->GetUniformName(UniformType::ModelMatrix);
			GLuint uniformId_ModelMatrix = pShaderData->GetUniformId(uniformName_ModelMatrix);
			if (uniformId_ModelMatrix != UINT_MAX)
			{
				// http://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4
				const float *modelMatrixArray = nullptr;
				if (pTransformNode != nullptr)
					modelMatrixArray = (const float*)glm::value_ptr(pTransformNode->GetGlobalTransform());
				else
					modelMatrixArray = (const float*)glm::value_ptr(g_IdentityMat4x4);

				glUniformMatrix4fv(uniformId_ModelMatrix, 1, GL_FALSE, modelMatrixArray);
			}

			SceneNodeFinder<CameraNode> &cameraNodeFinder = SceneNodeFinder<CameraNode>::getInstance();
			CameraNode *pCameraNode = cameraNodeFinder.FindUp(this);

			if (pCameraNode != nullptr)
			{
				// set view matrix
				// ---------------------------------------------------------------------------------------------
				std::string uniformName_ViewMatrix = m_pModelData->GetUniformName(UniformType::ViewMatrix);
				GLuint uniformId_ViewMatrix = pShaderData->GetUniformId(uniformName_ViewMatrix);

				if (uniformId_ViewMatrix != UINT_MAX)
				{
					// http://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4
					const float *viewMatrixArray = (const float*)glm::value_ptr(pCameraNode->GetGlobalViewTransform());
					glUniformMatrix4fv(uniformId_ViewMatrix, 1, GL_FALSE, viewMatrixArray);
				}

				// set projection matrix
				// ---------------------------------------------------------------------------------------------
				std::string uniformName_ProjectionMatrix = m_pModelData->GetUniformName(UniformType::ProjectionMatrix);
				GLuint uniformId_ProjectionMatrix = pShaderData->GetUniformId(uniformName_ProjectionMatrix);

				if (uniformId_ProjectionMatrix != UINT_MAX)
				{
					// http://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4
					const float *projectionMatrixArray = (const float*)glm::value_ptr(pCameraNode->GetProjectionTransform());
					glUniformMatrix4fv(uniformId_ProjectionMatrix, 1, GL_FALSE, projectionMatrixArray);
				}

				// set model view matrix
				// ---------------------------------------------------------------------------------------------
				std::string uniformName_ModelViewMatrix = m_pModelData->GetUniformName(UniformType::ModelViewMatrix);
				GLuint uniformId_ModelViewMatrix = pShaderData->GetUniformId(uniformName_ModelViewMatrix);

				if (uniformId_ModelViewMatrix != UINT_MAX)
				{
					glm::mat4x4 modelViewMatrix;
					if (pTransformNode != nullptr)
						modelViewMatrix = pCameraNode->GetGlobalViewTransform() * pTransformNode->GetGlobalTransform();
					else
						modelViewMatrix = pCameraNode->GetGlobalViewTransform();

					// http://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4
					const float *modelViewMatrixArray = (const float*)glm::value_ptr(modelViewMatrix);
					glUniformMatrix4fv(uniformId_ModelViewMatrix, 1, GL_FALSE, modelViewMatrixArray);
				}

				// set model view projection matrix
				// ---------------------------------------------------------------------------------------------
				std::string uniformName_ModelViewProjectionMatrix = m_pModelData->GetUniformName(UniformType::ModelViewProjectionMatrix);
				GLuint uniformId_ModelViewProjectionMatrix = pShaderData->GetUniformId(uniformName_ModelViewProjectionMatrix);

				if (uniformId_ModelViewProjectionMatrix != UINT_MAX)
				{
					glm::mat4x4 modelViewProjectionMatrix;
					if (pTransformNode != nullptr)
						modelViewProjectionMatrix = pCameraNode->GetProjectionTransform() * pCameraNode->GetGlobalViewTransform() * pTransformNode->GetGlobalTransform();
					else
						modelViewProjectionMatrix = pCameraNode->GetProjectionTransform() * pCameraNode->GetGlobalViewTransform();

					// http://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4
					const float *modelViewProjectionMatrixArray = (const float*)glm::value_ptr(modelViewProjectionMatrix);
					glUniformMatrix4fv(uniformId_ModelViewProjectionMatrix, 1, GL_FALSE, modelViewProjectionMatrixArray);
				}
			}

			// set Texture2D00, Texture2D01, Texture2D02, Texture2D03, TextureCubeMap00, TextureCubeMap01
			// ------------------------------------------------------------------------------------------
			GLuint textureUnitId = m_pModelData->GetTextureUnitId();
			if (textureUnitId != UINT_MAX)
			{
				std::string uniformName_Texture2D00 = m_pModelData->GetUniformName(UniformType::Texture2D00);
				GLuint uniformId_Texture2D00 = pShaderData->GetUniformId(uniformName_Texture2D00);
				if (uniformId_Texture2D00 != UINT_MAX)
				{
					// Bind our texture in Texture Unit 
					glActiveTexture(textureUnitId);
					glBindTexture(GL_TEXTURE_2D, m_pModelData->GetTextureId());
					// Set our texture sampler to user Texture Unit
					glUniform1i(m_pModelData->GetTextureId(), textureUnitId - GL_TEXTURE0); // ATTENTION, using index here
				}
			}
		}

		// ===============================================================================================================

		// TODO: change upon usage of element buffers !!!
		glBindVertexArray(m_pModelData->GetVAOId());
		glDrawArrays(GL_TRIANGLES, 0, m_pModelData->GetNoVertices());

		// ===============================================================================================================

		// traverse the children
		RenderChildren();

		return true;
	}

}