#include "Math/Math.h"
#include "Math/Vector2.h"

#include "Core/Random.h"
#include "Core/Time.h"

#include "Renderer/Renderer.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>


int main(int argc, char* argv[]) {

    Cpain::CTime::Time time;
    Cpain::Renderer renderer;
	renderer.initialize();
	renderer.createWindow("Cpain Engine", 1280, 1024);

    

    SDL_Event e;
    bool quit = false;

    std::vector<Cpain::CVec2::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1024));
    }

    while (!quit) {
        time.tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		renderer.setColor(0, 0, 0);
        renderer.clear();

        Cpain::CVec2::vec2 speed(0.0f, 0.005f);
		float length = speed.length();

        for (Cpain::CVec2::vec2& star : stars) {
            star += (speed * time.getDeltaTime());
            if (star[1] > 1024) star[1] = 0;
			renderer.setColor(255, 255, 255);
            renderer.drawPoint(star.x, star.y);
        }

		renderer.present();
    }
	renderer.shutdown();

    return 0;
}