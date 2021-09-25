#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    /* This method initializes SDL2 library. This function must be executed before any other SDL2 functions are called. */
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    /* This method creates a window that will be centered in the screen, visible, titled SDL2 Window, with dimentions 680 width * 480 height. */
    SDL_Window * window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }
    
    /* This method creates the surface that we will be blitting images to that is contained within the window we previously created. */
    SDL_Surface * window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }
    
    /* This method updates the surface contained in window. We can call this in a loop to achieve animation. */
    SDL_UpdateWindowSurface(window);
    
    /* Below block of code is the event loop which will execute until an SDL_QUIT event is encountered.
       In the case of this example that will be us clicking the exit button. */    
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
      if (SDL_PollEvent( & event)) {
          if (event.type == SDL_QUIT) {
              isquit = true;
            }
      }
    }
}
