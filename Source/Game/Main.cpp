#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include "Audio/AudioSystem.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    // Initialize SDL/Systems

    Cpain::Renderer renderer;
	renderer.initialize();
	renderer.createWindow("Cpain Engine", 1280, 1024);

    Cpain::CInput::InputSystem input;
	input.initialize();

    Cpain::CTime::Time time;

    // Create Audio (FMOD)

	Cpain::CAudio::AudioSystem audio;

	// Additional Initialization
    SDL_Event e;
    bool quit = false;

    std::vector<Cpain::CVec2::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1024));
    }

    std::vector<Cpain::CVec2::vec2> points{
        {-5, -5},
        {5, -5},
        {5, 5},
        {-5, 5}
    };

    Cpain::Model model(points, {1, 0, 0});

	// Main Loop
    while (!quit) {
        time.tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		// Update Systems
        
		input.update();

        // Update Input

        if (input.getKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Draw
        Cpain::CVec3::vec3 color{ 0, 0, 0 };

		renderer.setColor(color.r, color.g, color.b);
        renderer.clear();

		Cpain::CVec2::vec2 speed{ 0, 100 };
		float length = speed.length();

        for (auto& star : stars) {
			star += speed * time.getDeltaTime();

			if (star[1] > 1024) star[1] = 0;

			renderer.setColor(1.0f, 1.0f, 1.0f);
			renderer.drawPoint(star.x, star.y);
        }

		model.draw(renderer, input.getMousePosition(), time.getTime(), 10.0f);

        // Display
		renderer.present();
    }
	renderer.shutdown();

    return 0;
}