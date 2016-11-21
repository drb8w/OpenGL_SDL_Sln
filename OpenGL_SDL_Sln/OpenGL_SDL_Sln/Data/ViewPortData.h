#pragma once

#include "SceneData.h"

namespace TotalGlobal
{

	class ViewPortData : public SceneData
	{
	private:
		GLsizei m_Width;
		GLsizei m_Height;
	public:
		ViewPortData(GLsizei width, GLsizei height)
			: m_Width(width), m_Height(height)
		{}

		virtual bool LoadData()
		{
			return true;
		}

		GLsizei GetWidth()
		{
			return m_Width;
		}

		GLsizei GetHeight()
		{
			return m_Height;
		}

	};

}