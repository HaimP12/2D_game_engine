//
// Created by haimash on 7/20/25.
//

#include "InputManager.h"

void InputManager::Update()
{
    SDL_PumpEvents(); /// update keyboard state
    m_cKeyBoardState = SDL_GetKeyboardState(nullptr);
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const
{
    return m_cKeyBoardState && m_cKeyBoardState[key];
}
