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

    std::vector<std::vector<Cpain::CVec2::vec2>> lines;
    bool isDrawing = false;


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

        

        // Draw
		renderer.setColor(0, 0, 0);
        renderer.clear();

        if (input.getMouseButtonDown(Cpain::CInput::InputSystem::MouseButton::Left)) {
            Cpain::CVec2::vec2 position = input.getMousePosition();

            if (!isDrawing) {
                // Start a new stroke
                lines.push_back({});
                isDrawing = true;
            }

            std::vector<Cpain::CVec2::vec2>& currentLine = lines.back();

            if (currentLine.empty() || (position - currentLine.back()).length() > 10) {
                currentLine.push_back(position);
            }
        }
        else {
            isDrawing = false;
        }

        for (const auto& line : lines) {
            for (int i = 0; i < (int)line.size() - 1; i++) {
                renderer.setColor(255, 255, 255);
                renderer.drawLine(line[i].x, line[i].y, line[i + 1].x, line[i + 1].y);
            }
        }


        // Display
		renderer.present();
    }
	renderer.shutdown();

    return 0;
}