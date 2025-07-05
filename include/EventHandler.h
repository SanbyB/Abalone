#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

class EventHandler {
private:
    SDL_Event event;
    int mouseX, mouseY;
    bool leftButtonPressed;
    bool rightButtonPressed;
    bool middleButtonPressed;
    bool quit;

public:
    EventHandler() : mouseX(0), mouseY(0), leftButtonPressed(false), 
                    rightButtonPressed(false), middleButtonPressed(false), quit(false) {}

    // Process all pending events
    void handleEvents() {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    handleMouseButtonDown();
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    handleMouseButtonUp();
                    break;
                
                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
            }
        }
    }

    // Get mouse position
    int getMouseX() const { return mouseX; }
    int getMouseY() const { return mouseY; }
    
    // Get mouse position as a pair
    std::pair<int, int> getMousePosition() const {
        return std::make_pair(mouseX, mouseY);
    }

    // Check button states
    bool isLeftButtonPressed() const { return leftButtonPressed; }
    bool isRightButtonPressed() const { return rightButtonPressed; }
    bool isMiddleButtonPressed() const { return middleButtonPressed; }
    
    // Check if any mouse button is pressed
    bool isAnyButtonPressed() const {
        return leftButtonPressed || rightButtonPressed || middleButtonPressed;
    }

    // Check if quit was requested
    bool shouldQuit() const { return quit; }

    // Reset quit flag (useful if you want to handle quit differently)
    void resetQuit() { quit = false; }

private:
    void handleMouseButtonDown() {
        switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                leftButtonPressed = true;
                break;
            case SDL_BUTTON_RIGHT:
                rightButtonPressed = true;
                break;
            case SDL_BUTTON_MIDDLE:
                middleButtonPressed = true;
                break;
        }
    }

    void handleMouseButtonUp() {
        switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                leftButtonPressed = false;
                break;
            case SDL_BUTTON_RIGHT:
                rightButtonPressed = false;
                break;
            case SDL_BUTTON_MIDDLE:
                middleButtonPressed = false;
                break;
        }
    }
};

#endif // EVENT_HANDLER_H