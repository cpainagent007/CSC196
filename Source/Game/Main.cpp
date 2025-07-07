#include "Math/Math.h"
#include "Math/Vector2.h"

#include "Core/Random.h"

#include "Renderer/Renderer.h"

#include <SDL3/SDL.h>
#include <iostream>


int main(int argc, char* argv[]) {

    Cpain::Renderer renderer;
	renderer.initialize();
	renderer.createWindow("Cpain Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.setColor(Cpain::CRandom::getRandomInt(256),
            Cpain::CRandom::getRandomInt(256),
            Cpain::CRandom::getRandomInt(256));
        renderer.clear();

		renderer.present();
    }
	renderer.shutdown();

    return 0;
}