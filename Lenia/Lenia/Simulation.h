#pragma once

#include "GLFW/glfw3.h"

namespace Lenia
{
	class Simulation
	{
	public:
		Simulation();
		virtual ~Simulation();
		static void init();
		static void run();

	private:
		static GLFWwindow* s_window;
	};
}