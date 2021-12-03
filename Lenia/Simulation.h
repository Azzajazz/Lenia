#pragma once

#include "GLFW/glfw3.h"
#include "GameOfLife.h"

namespace Lenia
{
	class Simulation
	{
	public:
		static void init();
		static void run();

	private:
		static GLFWwindow* s_window;
		static GoL* s_golLogic;
	};
}