#pragma once
#include "Renderer.h"
#include "Font.h"
#include "../Math/Vector3.h"

namespace Cpain {
	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool create(Renderer& renderer, const std::string& text, const vec3& color);
		void draw(Renderer& renderer, float x, float y);

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}