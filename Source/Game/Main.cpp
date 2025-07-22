#include "Audio/AudioSystem.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"

#include "Input/InputSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include "Engine.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    // Initialize SDL/Renderer

	Cpain::getEngine().initialize();

    // Initialize Game

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->initialize();

    // Add Sounds

	Cpain::getEngine().getAudio().addSound("bass.wav", "bass");
	
    // Initialize Scene

	Cpain::Scene scene;

	// Additional Initialization

    SDL_Event e;
    bool quit = false;

    std::vector<Cpain::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::vec2(Cpain::getRandomFloat() * 1280, Cpain::getRandomFloat() * 1024));
    }
	
	// Main Loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		// Update Systems
        
		Cpain::getEngine().update();
        scene.update(Cpain::getEngine().getTime().getDeltaTime());

        // Update Input

        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Draw
        Cpain::vec3 color{ 0, 0, 0 };

		Cpain::getEngine().getRenderer().setColor(color.r, color.g, color.b);
        Cpain::getEngine().getRenderer().clear();

		Cpain::vec2 starSpeed{ 0, 100 };
		float length = starSpeed.length();

        for (auto& star : stars) {
            star += starSpeed * Cpain::getEngine().getTime().getDeltaTime();

            if (star[1] > 1024) star[1] = 0;

            Cpain::getEngine().getRenderer().setColor(1.0f, 1.0f, 1.0f);
            Cpain::getEngine().getRenderer().drawPoint(star.x, star.y);
        }

        scene.draw(Cpain::getEngine().getRenderer());
        
        // Display
        Cpain::getEngine().getRenderer().present();
    }

	Cpain::getEngine().shutdown();

    return 0;
}