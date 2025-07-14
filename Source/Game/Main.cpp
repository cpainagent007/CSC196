#include "Math/Math.h"
#include "Math/Vector2.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

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

	audio.addSound("bass.wav", "bass");
	audio.addSound("snare.wav", "snare");
	audio.addSound("clap.wav", "clap");
	audio.addSound("open-hat.wav", "open-hat");

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
        audio.update();

        // Update Input

        // Draw
		renderer.setColor(0, 0, 0);
        renderer.clear();

        // Display
		renderer.present();
    }
	renderer.shutdown();
    audio.shutdown();

    return 0;
}