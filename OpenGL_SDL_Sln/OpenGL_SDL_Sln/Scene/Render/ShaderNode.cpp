#include "ShaderNode.h"

namespace TotalGlobal
{

	bool ShaderNode::LoadData()
	{
		return m_pShaderData->LoadData();
	}

	bool ShaderNode::Render()
	{
		glUseProgram(m_pShaderData->GetProgramId());

		//// ViewPort-Setup
		//// TODO: move to own Node !!!

		//// EXTREME HACK
		//static const GLfloat gray[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//static const GLfloat ones[] = { 1.0f };
		//glClearBufferfv(GL_COLOR, 0, gray);
		//glClearBufferfv(GL_DEPTH, 0, ones);
		//glViewport(0, 0, 512, 512);
		//glEnable(GL_DEPTH_TEST);

		// ===============================================================================================================

		// traverse the children
		RenderChildren();

		return true;
	}

}