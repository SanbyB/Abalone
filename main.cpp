#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "include/board.h"
#include "include/EventHandler.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Abalone", 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         800, 600, 
                                         SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    EventHandler eventHandler;
    
    // Main game loop
    while (!eventHandler.shouldQuit()) {
        eventHandler.handleEvents();
        
        // Example: Print mouse info when any button is pressed
        if (eventHandler.isAnyButtonPressed()) {
            std::cout << "Mouse at (" << eventHandler.getMouseX() 
                      << ", " << eventHandler.getMouseY() << ") - ";
            
            if (eventHandler.isLeftButtonPressed()) std::cout << "LEFT ";
            if (eventHandler.isRightButtonPressed()) std::cout << "RIGHT ";
            if (eventHandler.isMiddleButtonPressed()) std::cout << "MIDDLE ";
            std::cout << "pressed" << std::endl;
        }
        
        // Add your game logic here
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



// int main(){
    
//     Board board = Board(10);
//     board.init();
//     board.print();
//     board.move(1, 0, 3, 3, 3, 2);
//     board.move(2, 4, 1, 4, 2, 4);
//     board.move(2, 3, 3, 4, 3, 5);
//     board.move(2, 3, 3, 4, 3, 3);
//     board.move(2, 3, 3, 2, 3, 3);
//     board.move(2, 1, 7, 5, 8, 5, 9, 5);
//     board.move(2, 1, 7, 5, 8, 5, 6, 5);
//     board.move(1, 0, 4, 4);
//     board.move(2, 1, 7, 5, 5, 5, 6, 5);
//     board.move(2, 3, 4, 5, 5, 5, 6, 5);



//     board.print();


//     return 0;
// }