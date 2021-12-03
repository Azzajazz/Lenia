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

			layout (location = 0) in vec3 inPos;
			layout (location = 1) in float inColour;

			out float aColour;

			void main()
			{
				gl_Position = vec4(inPos, 1.0);
				aColour = inColour;
			}
		)";

		const char* fragmentSrc = R"(
			#version 430 core
			
			in float aColour;
			out vec4 outColour;

			void main()
			{
				outColour = vec4(aColour, aColour, aColour, 1.0);
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

	void Renderer::setDrawInfo(const std::vector<uint32_t>& grid, uint32_t width, uint32_t height)
	{
		// Bind vertex array
		glBindVertexArray(s_rendererData.VAO);

		// Set number of elements and vertices for future use
		s_rendererData.elementCount = width * height * 6;
		s_rendererData.vertexCount = width * height * 4;

		// Initialise buffer sizes
		glBufferData(GL_ARRAY_BUFFER, s_rendererData.vertexCount * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_rendererData.elementCount * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

		// Input quad data
		for (uint32_t j = 0; j < height; j++)
		{
			for (uint32_t i = 0; i < width; i++)
			{
				float topLeftCoords[3] = {
					2 * (float)i / (float)width - 1, 2 * (float)(height - j) / (float)width - 1, 0.0f
				};
				float topRightCoords[3] = {
					2 * (float)(i + 1) / (float)width - 1, 2 * (float)(height - j) / (float)width - 1, 0.0f
				};
				float bottomRightCoords[3] = {
					2 * (float)(i + 1) / (float)width - 1, 2 * (float)(height - j - 1) / (float)width - 1, 0.0f
				};
				float bottomLeftCoords[3] = {
					2 * (float)i / (float)width - 1, 2 * (float)(height - j - 1) / (float)width - 1, 0.0f
				};
				float vertices[4 * 4] = {
					topLeftCoords[0], topLeftCoords[1], topLeftCoords[2], (float)grid[j * width + i],
					topRightCoords[0], topRightCoords[1], topRightCoords[2], (float)grid[j * width + i],
					bottomRightCoords[0], bottomRightCoords[1], bottomRightCoords[2], (float)grid[j * width + i],
					bottomLeftCoords[0], bottomLeftCoords[1], bottomLeftCoords[2], (float)grid[j * width + i],
				};

				uint32_t indices[6] = {
					(j * width + i) * 4, (j * width + i) * 4 + 1, (j * width + i) * 4 + 2,
					(j * width + i) * 4 + 2, (j * width + i) * 4 + 3, (j * width + i) * 4
				};

				glBufferSubData(GL_ARRAY_BUFFER, (j * width + i) * sizeof(vertices), sizeof(vertices), vertices);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (j * width + i) * sizeof(indices), sizeof(indices), indices);
			}
		}

		// Specify layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void Renderer::draw()
	{
		glUseProgram(s_rendererData.shaderProgram);
		glBindVertexArray(s_rendererData.VAO);
		glDrawElements(GL_TRIANGLES, s_rendererData.elementCount, GL_UNSIGNED_INT, 0);
	}

	struct RendererData Renderer::s_rendererData = { 0 };
}