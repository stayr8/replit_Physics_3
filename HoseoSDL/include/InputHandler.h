﻿#pragma once

#include "main.h"
#include "Game.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
public:
    ~InputHandler() {}
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }
    void update();
    void clean() {}

    // 키보드
    bool isKeyDown(SDL_Scancode key);

    // 마우스 
    bool isKeyOneDown(SDL_Scancode key);
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition();
    void onMouseMove(SDL_Event event);
    void onMouseButtonDown(SDL_Event event);
    void onMouseButtonUp(SDL_Event event);
    void onKeyDown();
    void onKeyUp();


private:
    InputHandler();
    static InputHandler* s_pInstance;

    // 키보드
    const Uint8* m_keystates;

    // 마우스
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
};

typedef InputHandler TheInputHandler;