#pragma once

#include <vector>
#include <string>

#include "ObjModelLoader.h"

namespace TotalGlobal
{
	class SceneData
	{

	public:
		SceneData()
		{
		}

		virtual bool LoadData() = 0;

	};

}