#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <ctime>
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_vulkan.h>

using namespace std;

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;

SDL_Window* g_main_window;
SDL_Renderer* g_main_renderer;

namespace Colors 
{
    const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE};    
}

static bool Init()
{
    // Check for any errors when creating a new window
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL_Init failed to open with error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }
    
    // Define a new window 
    g_main_window = SDL_CreateWindow(
        "Progmatic Engine 0.0.1-alpha",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_VULKAN
    );

    // Check if the window was not created properly and gracefully handle it.
    if(g_main_window == nullptr)
    {
        cout << "Failed to create window. Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    // Create the new window! this is so cool wow!
    g_main_renderer = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_PRESENTVSYNC);
    
    // Return true if there are no errors
    return true;
}

// Clean up the program and free memory on close.
void Shutdown()
{
    if(g_main_window != nullptr)
    {
        SDL_DestroyWindow(g_main_window);
        g_main_window = nullptr;
    }

    if(g_main_renderer != nullptr)
    {
        SDL_DestroyRenderer(g_main_renderer);
        g_main_renderer = nullptr;
    }
    cout << "Shutting down engine" << endl;
    SDL_Quit();
}

static void ClearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
    SDL_RenderClear(renderer);
}

int main()
{
    cout << "Creating new SDL window." << endl;
    if (Init() == false)
    {
        Shutdown();
    }

    // Main engine loop, I gotta actually make gameplay shit for this :(
    SDL_Event event;
    bool isRunning = true;

    while(isRunning)
    {
        ClearScreen(g_main_renderer);

        // Check for inputs, this apparently has to be done once before the window can be rendered
        if(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    isRunning = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    break;
                }
                case SDL_QUIT:
                {
                    isRunning = false;
                    break;
                }
                default:
                    break;
            }
        }

        SDL_RenderPresent(g_main_renderer);
    }
    
    Shutdown();
    return EXIT_SUCCESS;
}
