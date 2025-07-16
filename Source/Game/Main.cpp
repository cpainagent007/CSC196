#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Game/Actor.h"

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

    // (Stars)

    std::vector<Cpain::CVec2::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1024));
    }

    // (Model)

    std::vector<Cpain::CVec2::vec2> points{
        {5, 5},
        {5, -5},
        {-5, -5},
        {-5, 5},
        {5, 5}
    };

    Cpain::Model* model = new Cpain::Model(points, {0, 1, 0});

	// (Transform)

	

    // (Actor)

	std::vector<Cpain::CActor::Actor> actors;
    for(int i = 0; i < 100; i++) {
        Cpain::Transform transform
        { Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1020), 
            Cpain::CRandom::getRandomFloat() * 360, 
            Cpain::CRandom::getRandomFloat() * 10 };
        Cpain::CActor::Actor actor{ transform, model };
		actors.push_back(actor);
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
        
		input.update();

        // Update Input

		float shipSpeed = 200.0f;

		Cpain::CVec2::vec2 inputDirection{ 0, 0 };
        if (input.getKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
		if (input.getKeyDown(SDL_SCANCODE_S)) inputDirection.y = 1;
        if (input.getKeyDown(SDL_SCANCODE_D)) inputDirection.x = 1;
		if (input.getKeyDown(SDL_SCANCODE_W)) inputDirection.y = -1;
        if (input.getKeyDown(SDL_SCANCODE_A)) inputDirection.x = -1;

        if (inputDirection.lengthSqrd() > 0) {
            inputDirection = inputDirection.normalized();
            for (auto& actor : actors) {
				actor.getTransform().position += (inputDirection * shipSpeed) * time.getDeltaTime();
            }
        }

        // Draw
        Cpain::CVec3::vec3 color{ 0, 0, 0 };

		renderer.setColor(color.r, color.g, color.b);
        renderer.clear();

		Cpain::CVec2::vec2 starSpeed{ 0, 100 };
		float length = starSpeed.length();

        for (auto& star : stars) {
			star += starSpeed * time.getDeltaTime();

			if (star[1] > 1024) star[1] = 0;

			renderer.setColor(1.0f, 1.0f, 1.0f);
			renderer.drawPoint(star.x, star.y);
        }

        for (auto& actor : actors) {
            actor.update(time.getDeltaTime());
            actor.draw(renderer);
		}
        
        // Display
		renderer.present();
    }
	renderer.shutdown();

    return 0;
}