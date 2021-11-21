#pragma once

#include <stdint.h>
#include <vector>

namespace Lenia
{
	struct RendererData
	{
		uint32_t VBO, EBO;
		uint32_t VAO;
		uint32_t shaderProgram;
	};

	class Renderer
	{
	public:
		static void init();
		static void setDrawInfo();
		static void draw();
	private:
		static struct RendererData s_rendererData;
	};
}