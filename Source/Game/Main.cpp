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

    
     // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << Cpain::getCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    Cpain::setCurrentDirectory("Assets");
    std::cout << "New directory: " << Cpain::getCurrentDirectory() << "\n\n";

    // Get filenames in the current directory
    std::cout << "Files in Directory:\n";
    auto filenames = Cpain::getFilesInDirectory(Cpain::getCurrentDirectory());
    for (const auto& filename : filenames) {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // Get filename (filename.extension) only
    if (!filenames.empty()) {
        std::cout << "Path Analysis:\n";
        std::string filename = Cpain::getFilename(filenames[0]);
        std::cout << "Filename only: " << filename << "\n";

        // Get extension only
        std::string ext = Cpain::getExtension(filenames[0]);
        std::cout << "Extension: " << ext << "\n\n";
    }

    // Read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    bool success = Cpain::readTextFile("test.txt", str);
    if (success) {
        std::cout << "Contents of test.txt:\n";
        std::cout << str << "\n";
    }
    else {
        std::cout << "Failed to read test.txt\n";
    }
    

   




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