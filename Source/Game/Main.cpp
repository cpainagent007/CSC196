#include "Math/Math.h"
#include "Math/Vector2.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

#include <SDL3/SDL.h>
#include <fmod.hpp>

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
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);

    std::vector<FMOD::Sound*> sounds;
    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

	// Additional Initialization
    SDL_Event e;
    bool quit = false;

    std::vector<Cpain::CVec2::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1024));
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

        audio->update();

        // Update Input

        if(input.getKeyDown(SDL_SCANCODE_Q) && !input.getPrevKeyDown(SDL_SCANCODE_Q)) {
			audio->playSound(sounds[0], 0, false, nullptr);
		}

        if (input.getKeyDown(SDL_SCANCODE_W) && !input.getPrevKeyDown(SDL_SCANCODE_W)) {
            audio->playSound(sounds[1], 0, false, nullptr);
        }

        if (input.getKeyDown(SDL_SCANCODE_E) && !input.getPrevKeyDown(SDL_SCANCODE_E)) {
            audio->playSound(sounds[2], 0, false, nullptr);
        }

        // Draw
		renderer.setColor(0, 0, 0);
        renderer.clear();


        Cpain::CVec2::vec2 speed(0.0f, 0.005f);
		float length = speed.length();

        for (Cpain::CVec2::vec2& star : stars) {
            star += speed;
            if (star[1] > 1024) star[1] = 0;
			renderer.setColor(255, 255, 255);
            renderer.drawPoint(star.x, star.y);
        }

        // Display
		renderer.present();
    }
	renderer.shutdown();

    return 0;
}