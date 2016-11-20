#pragma once

#include <glm/mat4x4.hpp>

#include "SceneData.h"

namespace TotalGlobal
{

	class TransformData : public SceneData
	{
	private:
		glm::mat4x4 m_Transform;

	public:
		TransformData(glm::mat4x4 transform)
			: m_Transform(transform)
		{}

		virtual bool LoadData()
		{
			return true;
		}

		glm::mat4x4 GetTransform()
		{
			return m_Transform;
		}

	};

}