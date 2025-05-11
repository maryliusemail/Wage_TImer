#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
        std::cerr << "SDL/TTF init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    const int width = 600, height = 200;
    SDL_Window* window = SDL_CreateWindow("Wage Timer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("pixel.ttf", 30); // Ensure this font exists in working directory
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        return 1;
    }

    // --- Get wage input from user via SDL text box ---
    std::string wage_input = "";
    bool wage_entered = false;

    SDL_StartTextInput();

    while (!wage_entered) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return 0;
            if (e.type == SDL_TEXTINPUT) wage_input += e.text.text;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && !wage_input.empty()) {
                    wage_input.pop_back();
                }
                if (e.key.keysym.sym == SDLK_RETURN && !wage_input.empty()) {
                    wage_entered = true;
                }
            }
        }

        std::ostringstream prompt;
        prompt << "Enter hourly wage: " << wage_input;

        SDL_Color white = {255, 255, 255};
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, prompt.str().c_str(), white);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        SDL_Rect text_rect;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;
        text_rect.x = (width - text_rect.w) / 2;
        text_rect.y = (height - text_rect.h) / 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_RenderPresent(renderer);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);

        SDL_Delay(16);
    }

    SDL_StopTextInput();

    // Convert wage string to double
    double wage = std::stod(wage_input);
    double wage_per_sec = wage / 3600.0;
    double total_secs = 0;
    int hr = 0, min = 0, sec = 0;
    Uint32 last_time = SDL_GetTicks();
    bool running = true;

    // --- Main timer loop ---
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_time >= 1000) {
            last_time = current_time;
            sec++;
            total_secs++;
            if (sec == 60) { sec = 0; min++; }
            if (min == 60) { min = 0; hr++; }
        
            // Wage timer string
            std::ostringstream oss;
            oss << std::setfill('0') << std::setw(2) << hr << ":"
                << std::setw(2) << min << ":"
                << std::setw(2) << sec
                << " | $" << std::fixed << std::setprecision(2) << wage_per_sec * total_secs;
        
            SDL_Color white = {255, 255, 255};
        
            SDL_Surface* text_surface = TTF_RenderText_Solid(font, oss.str().c_str(), white);
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            SDL_Rect text_rect;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;
            text_rect.x = (width - text_rect.w) / 2;
            text_rect.y = (height - text_rect.h) / 2;
        
            // Time and date string
            std::time_t now = std::time(nullptr);
            std::tm* local_time = std::localtime(&now);
            std::ostringstream time_stream;
            time_stream << std::put_time(local_time, "%A, %Y-%m-%d %H:%M:%S");
        
            SDL_Surface* time_surface = TTF_RenderText_Solid(font, time_stream.str().c_str(), white);
            SDL_Texture* time_texture = SDL_CreateTextureFromSurface(renderer, time_surface);
            SDL_Rect time_rect;
            time_rect.w = time_surface->w;
            time_rect.h = time_surface->h;
            time_rect.x = width - time_rect.w - 10;  // right corner
            time_rect.y = 10;                        // top corner
        
            // Draw everything
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);   // wage timer
            SDL_RenderCopy(renderer, time_texture, NULL, &time_rect);   // real clock
            SDL_RenderPresent(renderer);
        
            // Free resources
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(time_surface);
            SDL_DestroyTexture(time_texture);
        }
        

        SDL_Delay(10);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
