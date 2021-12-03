#pragma once

#include "glad/glad.h"
#include "Simulation.h"
#include "Logging.h"
#include "Renderer.h"
#include <vector>
#include <chrono>
#include <thread>

namespace Lenia
{
	constexpr double TICKRATE = 7.0;

	void errorCallback(int code, const char* message)
	{
		LENIA_INFO(message);
	}

	void Simulation::init()
	{
		glfwSetErrorCallback(errorCallback);
		LENIA_ASSERT(glfwInit(), "Failed to initialise GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		s_window = glfwCreateWindow(800, 800, "Hello, World!", NULL, NULL);
		if (s_window == nullptr)
		{
			std::cerr << "[X]Failed to create glfw window\n";
			glfwTerminate();
			exit(1);
		}
		glfwMakeContextCurrent(s_window);

		LENIA_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to retrieve GL loader");
		LENIA_ASSERT(gladLoadGL(), "Failed to load GL functions");

		glViewport(0, 0, 800, 800);

		Renderer::init();

		std::vector<uint32_t> grid = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		s_golLogic = new GoL(grid, 18, 18);
	}

	void Simulation::run()
	{
		double startTime = glfwGetTime();
		while (!glfwWindowShouldClose(s_window))
		{
			double updateTime = glfwGetTime();
			if (updateTime - startTime > 1 / TICKRATE)
			{
				s_golLogic->updateGrid();
				startTime = glfwGetTime();
			}
			Renderer::setDrawInfo(*s_golLogic->getGrid(), s_golLogic->getWidth(), s_golLogic->getHeight());
			Renderer::draw();
			glfwSwapBuffers(s_window);
			glfwPollEvents();
		}

		glfwTerminate();
	}
	
	GLFWwindow* Simulation::s_window = nullptr;
	GoL* Simulation::s_golLogic = nullptr;
}