//
// Created by haimash on 7/20/25.
//

#ifndef GAME_GAMEAPP_H
#define GAME_GAMEAPP_H

#include <SDL.h>
#include <string>

class gameApp
{
public:
    /// create the core of the game app
    /// \param gameTitle the title of the game
    /// \param u32WindowHeight the height of the window
    /// \param u32WindowWidth the width of the window
    /// \param u32gameFPS the FPS needed for the game
    explicit gameApp(const std::string& gameTitle, const uint32_t u32WindowHeight, const uint32_t u32WindowWidth, const uint32_t u32gameFPS);
    ~gameApp();

    /// initialize the core game
    /// \return true for success, otherwise false
    [[nodiscard]] bool Init();
    /// stop the game
    void Shutdown();
    /// start running the game
    void Run();

protected:
    /// the logic of the game
    /// \param deltaTime the time between the frames
    void Update(float deltaTime);
    void HandleEvents();
    void Render();

private:
    std::string m_sGameTitle;
    uint32_t m_u32WindowHeight;
    uint32_t m_u32WindowWidth;
    uint32_t m_u32GameFPS;

    bool m_bIsRunning;

    SDL_Window* m_pSDLWindow;
    SDL_Renderer* m_pRender;
};


#endif //GAME_GAMEAPP_H
