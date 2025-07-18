#include "Model.h"
#include "Renderer.h"

namespace Cpain {

	
	void Model::draw(class Renderer& renderer, const Cpain::CVec2::vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;

		renderer.setColor( m_color.r, m_color.g, m_color.b );

		for (int i = 0; i < m_points.size() - 1; i++) {
			Cpain::CVec2::vec2 p1 = (m_points[i].rotate(rotation) * scale) + position;
			Cpain::CVec2::vec2 p2 = (m_points[i + 1].rotate(rotation) * scale) + position;

			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}


	void Model::draw(class Renderer& renderer, const Transform& transform) {
		draw(renderer, transform.position, transform.rotation, transform.scale);
	}

}