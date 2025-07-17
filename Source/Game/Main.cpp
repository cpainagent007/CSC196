#include "Audio/AudioSystem.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Game/Actor.h"
#include "Game/Scene.h"

#include "Input/InputSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include "Game/Player.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    // Initialize SDL/Renderer

    std::unique_ptr<Cpain::Renderer> renderer = std::make_unique<Cpain::Renderer>();
	renderer->initialize();
	renderer->createWindow("Cpain Engine", 1280, 1024);

    // Initialize Input

    std::unique_ptr<Cpain::CInput::InputSystem> input = std::make_unique<Cpain::CInput::InputSystem>();
	input->initialize();

    Cpain::CTime::Time time;

	// Initialize Audio

	std::unique_ptr<Cpain::CAudio::AudioSystem> audio = std::make_unique<Cpain::CAudio::AudioSystem>();
	audio->initialize();

    // Initialize Scene

	Cpain::CScene::Scene scene;

	// Additional Initialization

    SDL_Event e;
    bool quit = false;

    // (Stars)

    std::vector<Cpain::CVec2::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1024));
    }

    // (Model)

    std::vector<Cpain::CVec2::vec2> points{
        {-1, 4},
        {-1, 2},
        {-1, 1},
        {0, 2},
        {1, 1},
        {1, 2},
        {1, 4},
        {2, 1},
        {2, -2},
        {4, 0},
        {1, 0},
        {0, -2},
        {-1, 0},
        {-4, 0},
        {-2, -2},
        {0, -2},
        {-2, -4},
        {-2, -2},
        {2, -2},
        {2, -4},
        {0, -2},
        {-2, -2},
        {-2, 1},
        {-1, 4}
    };

    std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(points, Cpain::CVec3::vec3{ 0, 1, 0 });

    // (Actor, Transform)

    for(int i = 0; i < 50; i++) {
        Cpain::Transform transform

        { Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1020), 
            Cpain::CRandom::getRandomFloat() * 360, 
            Cpain::CRandom::getRandomFloat() * 10 };

        std::unique_ptr<Player> player = std::make_unique<Player>( transform, model );
		scene.addActor(std::move(player));
    }
	
	// Main Loop
    while (!quit) {
        time.tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		// Update Systems
        
		input->update();
		audio->update();

        // Update Input

		float shipSpeed = 200.0f;

		Cpain::CVec2::vec2 inputDirection{ 0, 0 };
        if (input->getKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
		if (input->getKeyDown(SDL_SCANCODE_S)) inputDirection.y = 1;
        if (input->getKeyDown(SDL_SCANCODE_D)) inputDirection.x = 1;
		if (input->getKeyDown(SDL_SCANCODE_W)) inputDirection.y = -1;
        if (input->getKeyDown(SDL_SCANCODE_A)) inputDirection.x = -1;

        if (inputDirection.lengthSqrd() > 0) {
            inputDirection = inputDirection.normalized();
        }

        // Draw
        Cpain::CVec3::vec3 color{ 0, 0, 0 };

		renderer->setColor(color.r, color.g, color.b);
        renderer->clear();

		Cpain::CVec2::vec2 starSpeed{ 0, 100 };
		float length = starSpeed.length();

        for (auto& star : stars) {
            star += starSpeed * time.getDeltaTime();

            if (star[1] > 1024) star[1] = 0;

            renderer->setColor(1.0f, 1.0f, 1.0f);
            renderer->drawPoint(star.x, star.y);
        }

        scene.draw(*renderer);
        
        // Display
		renderer->present();
    }

	renderer->shutdown();
	audio->shutdown();

    return 0;
}