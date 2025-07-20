//
// Created by haimash on 7/20/25.
//

#include "gameApp.h"
#include "TextureManager.h"

gameApp::gameApp(const std::string &gameTitle, const uint32_t u32WindowHeight, const uint32_t u32WindowWidth,
                 const uint32_t u32gameFPS) :
                 m_sGameTitle(gameTitle),
                 m_u32WindowHeight(u32WindowHeight),
                 m_u32WindowWidth(u32WindowWidth),
                 m_u32GameFPS(u32gameFPS),
                 m_bIsRunning(false),
                 m_pSDLWindow(nullptr),
                 m_pRender(nullptr),
                 m_inputManager(),
                 m_n32ImageYAxisLocation(100),
                 m_n32ImageXAxisLocation(100)
{

}

gameApp::~gameApp()
{
    Shutdown();
}

bool gameApp::Init()
{
    bool res = false;
    res = (0 == SDL_Init(SDL_INIT_VIDEO));

    res = res && (IMG_INIT_JPG == IMG_Init(IMG_INIT_JPG));

    if (res)
    {
        m_pSDLWindow = SDL_CreateWindow(m_sGameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         m_u32WindowWidth, m_u32WindowHeight, SDL_WINDOW_SHOWN);

        m_pRender = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    res = res && TextureManager::getInatnce().loadImage("the one ring", "../images/one_ring.jpeg", m_pRender);

    if (res && m_pSDLWindow && m_pRender)
    {
        m_bIsRunning = true;
    }

    return m_bIsRunning;
}

void gameApp::Shutdown()
{
    TextureManager::getInatnce().cleanImage();

    if (m_pRender)
    {
        SDL_DestroyRenderer(m_pRender);
    }

    if(m_pSDLWindow)
    {
        SDL_DestroyWindow(m_pSDLWindow);
    }

    SDL_Quit();
}

void gameApp::Run()
{
    const uint32_t frameDelay = 1000 / m_u32GameFPS;

    uint32_t frameStart;
    uint32_t frameTime;

    while (m_bIsRunning)
    {
        frameStart = SDL_GetTicks();

        HandleEvents();
        Update((1.0f / m_u32GameFPS));
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void gameApp::Update(float deltaTime)
{
    const int32_t PixelsPerSecond = 200;

    auto amountOfMovement = (int32_t)(PixelsPerSecond * deltaTime);

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_W) || m_inputManager.IsKeyPressed(SDL_SCANCODE_UP))
    {
        m_n32ImageYAxisLocation -= amountOfMovement;
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_S) || m_inputManager.IsKeyPressed(SDL_SCANCODE_DOWN))
    {
        m_n32ImageYAxisLocation += amountOfMovement;
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_A) || m_inputManager.IsKeyPressed(SDL_SCANCODE_LEFT))
    {
        m_n32ImageXAxisLocation -= amountOfMovement;
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_D) || m_inputManager.IsKeyPressed(SDL_SCANCODE_RIGHT))
    {
        m_n32ImageXAxisLocation += amountOfMovement;
    }

}

void gameApp::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_bIsRunning = false;
        }
    }

    /// check if there is input from the keyboard
    m_inputManager.Update();
}

void gameApp::Render()
{
    SDL_SetRenderDrawColor(m_pRender, 20, 20, 20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_pRender);

    TextureManager::getInatnce().drawImage("the one ring",
                                           m_n32ImageXAxisLocation, m_n32ImageYAxisLocation,
                                           256, 256, m_pRender);
    SDL_RenderPresent(m_pRender);
}
