#include "Renderer.h"
#include "glad/glad.h"
#include <string>
#include <iostream>

namespace Lenia
{
	void Renderer::init()
	{
		// Initialise VAO, VBO, EBO and bind them.
		glGenVertexArrays(1, &s_rendererData.VAO);
		glBindVertexArray(s_rendererData.VAO);
		glGenBuffers(1, &s_rendererData.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, s_rendererData.VBO);
		glGenBuffers(1, &s_rendererData.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_rendererData.EBO);

		// Shader source code
		const char* vertexSrc = R"(
			#version 430 core
			layout (location = 0) in vec3 lPos;
			layout (location = 1) in vec3 lColour;

			out vec3 aColour;

			void main()
			{
				gl_Position = vec4(lPos, 1.0);
				aColour = lColour;
			}
		)";

		const char* fragmentSrc = R"(
			#version 430 core
			
			in vec3 aColour;
			out vec4 fColour;

			void main()
			{
				fColour = vec4(aColour, 1.0);
			}
		)";

		// Vertex shader compilation and error reports
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
		}

		// Fragment shader compilation and error reports
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
		}

		// Linking and error reports
		s_rendererData.shaderProgram = glCreateProgram();
		glAttachShader(s_rendererData.shaderProgram, vertexShader);
		glAttachShader(s_rendererData.shaderProgram, fragmentShader);
		glLinkProgram(s_rendererData.shaderProgram);
		glGetProgramiv(s_rendererData.shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(s_rendererData.shaderProgram, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::LINK_FAILED\n" << infoLog << "\n";
		}

		// Use program and delete vertex/fragment shaders
		glUseProgram(s_rendererData.shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Renderer::setDrawInfo()
	{
		float vertices[6 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.1f,
			0.0f, 0.5f, 0.0f, 0.2f, 0.0f, 0.1f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.1f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void Renderer::draw()
	{
		glUseProgram(s_rendererData.shaderProgram);
		glBindVertexArray(s_rendererData.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	struct RendererData Renderer::s_rendererData = { 0 };
}