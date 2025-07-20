//
// Created by haimash on 7/20/25.
//

#ifndef GAME_INPUTMANAGER_H
#define GAME_INPUTMANAGER_H

#include <SDL.h>

class InputManager
{
public:
    void Update();
    [[nodiscard]] bool IsKeyPressed(SDL_Scancode key) const;

private:
    const uint8_t* m_cKeyBoardState = nullptr;
};


#endif //GAME_INPUTMANAGER_H
