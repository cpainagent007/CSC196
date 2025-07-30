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

    
    // Test getInt() variants
    std::cout << "Integer Functions:\n";
    std::cout << "getInt(): " << Cpain::getInt() << "\n";
    std::cout << "getInt(): " << Cpain::getInt() << "\n";
    std::cout << "getInt(10): " << Cpain::getInt(10) << "\n";
    std::cout << "getInt(10): " << Cpain::getInt(10) << "\n";
    std::cout << "getInt(5, 15): " << Cpain::getInt(5, 15) << "\n";
    std::cout << "getInt(5, 15): " << Cpain::getInt(5, 15) << "\n";
    std::cout << "getInt(-10, 10): " << Cpain::getInt(-10, 10) << "\n\n";

    // Test getReal() variants with float
    std::cout << "Float Functions:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "getReal<float>(): " << Cpain::getReal<float>() << "\n";
    std::cout << "getReal<float>(): " << Cpain::getReal<float>() << "\n";
    std::cout << "getReal<float>(5.0f): " << Cpain::getReal<float>(5.0f) << "\n";
    std::cout << "getReal<float>(2.5f, 7.5f): " << Cpain::getReal<float>(2.5f, 7.5f) << "\n";
    std::cout << "getReal<float>(-1.0f, 1.0f): " << Cpain::getReal<float>(-1.0f, 1.0f) << "\n\n";

    // Test getReal() variants with double
    std::cout << "Double Functions:\n";
    std::cout << std::setprecision(10);
    std::cout << "getReal<double>(): " << Cpain::getReal<double>() << "\n";
    std::cout << "getReal<double>(100.0): " << Cpain::getReal<double>(100.0) << "\n";
    std::cout << "getReal<double>(0.0, 2.0): " << Cpain::getReal<double>(0.0, 2.0) << "\n\n";

    // Test getBool()
    std::cout << "Boolean Functions:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "getBool(): " << std::boolalpha << Cpain::getBool() << "\n";
    }
    std::cout << "\n";
    

   




    // Initialize SDL/Renderer

	Cpain::getEngine().initialize();

    // Initialize Game

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->initialize();

    // Add Sounds

	Cpain::getEngine().getAudio().addSound("bass.wav", "bass");

    // Add Font and Text

    Cpain::Font* font = new Cpain::Font();
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
        game->draw();
        
        // Display
        Cpain::getEngine().getRenderer().present();
    }
	game->shutdown();
    game.release();
	Cpain::getEngine().shutdown();

    return 0;
}