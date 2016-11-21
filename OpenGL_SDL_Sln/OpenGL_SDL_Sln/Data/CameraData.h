#pragma once

#include <glm/mat4x4.hpp>

#include "SceneData.h"

namespace TotalGlobal
{
	class CameraData : public SceneData
	{
	private:
		glm::mat4x4 m_ViewTransform;
		glm::mat4x4 m_ProjectionTransform;

	public:
		CameraData(glm::mat4x4 viewTransform, glm::mat4x4 projectionTransform)
			: m_ViewTransform(viewTransform), m_ProjectionTransform(projectionTransform)
		{}

		virtual bool LoadData()
		{
			return true;
		}

		glm::mat4x4 GetViewTransform()
		{
			return m_ViewTransform;
		}

		glm::mat4x4 GetProjectionTransform()
		{
			return m_ProjectionTransform;
		}

	};

}