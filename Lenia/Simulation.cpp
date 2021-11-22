#pragma once

#include "glad/glad.h"
#include "Simulation.h"
#include "Logging.h"
#include "Renderer.h"

namespace Lenia
{
	void errorCallback(int code, const char* message)
	{
		LENIA_INFO(message);
	}

	Simulation::Simulation()
	{
	}

	Simulation::~Simulation()
	{
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

		uint32_t grid[10 * 10] = {
			0, 1, 0, 0, 0, 1, 1, 1, 0, 1,
			0, 1, 1, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
			0, 1, 0, 0, 1, 0, 0, 0, 0, 1,
			1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
			0, 1, 0, 0, 0, 1, 1, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
			1, 0, 0, 1, 1, 0, 1, 1, 0, 1
		};

		Renderer::setDrawInfo(grid, 10, 10);
	}

	void Simulation::run()
	{
		while (!glfwWindowShouldClose(s_window))
		{
			glfwSwapBuffers(s_window);
			Renderer::draw();
			glfwPollEvents();
		}

		glfwTerminate();
	}
	
	GLFWwindow* Simulation::s_window = nullptr;
}