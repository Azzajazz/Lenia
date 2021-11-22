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
		uint32_t vertexCount;
		uint32_t elementCount;
	};

	class Renderer
	{
	public:
		static void init();
		static void setDrawInfo(uint32_t* grid, uint32_t width, uint32_t height);
		static void draw();
	private:
		static struct RendererData s_rendererData;
	};
}