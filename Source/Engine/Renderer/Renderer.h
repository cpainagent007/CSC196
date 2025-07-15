#pragma once
#include <SDL3/SDL.h>
#include <iostream>

namespace Cpain {
	class Renderer {

	public:
		Renderer() = default;

		bool initialize();
		bool createWindow(const std::string& name, int width, int height);
		void present();

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void setColor(float r, float g, float b, float a = 1.0f);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(float x, float y);
		void clear();

		void shutdown();

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

	};
}
