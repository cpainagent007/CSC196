#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
        //SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        for (int i = 0; i < 10; i++) {
			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;
			int a = rand() % 256;
			SDL_SetRenderDrawColor(renderer, r, g, b, a); // Set random color
			int startx = rand() % 1280;
			int starty = rand() % 1024;
			int endx = rand() % 1280;
			int endy = rand() % 1024;
			SDL_RenderLine(renderer, startx, starty, endx, endy); // Render random lines
        }
        for (int i = 0; i < 20; i++) {
			int x = rand() % 1280;
			int y = rand() % 1024;
			SDL_RenderPoint(renderer, x, y); // Render random points
        }

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}