#include "Audio/AudioSystem.h"

#include "Core/File.h"
#include "Core/Random.h"
#include "Core/Time.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"

#include "Input/InputSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include "Engine.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

	Cpain::setCurrentDirectory("Assets");

    // Initialize SDL/Renderer

	Cpain::getEngine().initialize();

    // Initialize Game

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->initialize();

    // Add Sounds

	Cpain::getEngine().getAudio().addSound("bass.wav", "bass");

    // Add Font and Text
    

    auto font = std::make_shared<Cpain::Font>();
    font->load("QuirkyRobot.ttf", 20);
    Cpain::Text* text = new Cpain::Text(font);
    text->create(Cpain::getEngine().getRenderer(), "Hello World", Cpain::vec3{ 1, 1, 1 });
    

	// Additional Initialization

    SDL_Event e;
    bool quit = false;
	
	// Main Loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		// Update Systems
        
		Cpain::getEngine().update();
		game->update(Cpain::getEngine().getTime().getDeltaTime());

        // Update Input

        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Draw
        Cpain::vec3 color{ 0, 0, 0 };
		Cpain::getEngine().getRenderer().setColor(color.r, color.g, color.b);
        Cpain::getEngine().getRenderer().clear();

        text->draw(Cpain::getEngine().getRenderer(), 40.0f, 40.0f);
        game->draw(Cpain::getEngine().getRenderer());
        
        // Display
        Cpain::getEngine().getRenderer().present();
    }
	game->shutdown();
    game.release();
	Cpain::getEngine().shutdown();

    return 0;
}