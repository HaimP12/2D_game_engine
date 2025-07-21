//
// Created by haimash on 7/20/25.
//

#include <iostream>
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
                 m_tileMap(nullptr),
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

    res = res && ((IMG_INIT_JPG | IMG_INIT_PNG) == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG));

    if (res)
    {
        m_pSDLWindow = SDL_CreateWindow(m_sGameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         m_u32WindowWidth, m_u32WindowHeight, SDL_WINDOW_SHOWN);

        m_pRender = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    res = res && TextureManager::getInstance().loadImage("tileset", "../images/themed_tileset.png", m_pRender);

    SDL_Texture* texture = TextureManager::getInstance().getTexture("tileset");
    int textureWidth = 0, textureHeight = 0;
    if (texture)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    }
    else
    {
        std::cerr << "Failed to get texture 'tileset'\n";
    }

    m_tileMap = new TileMap(32, 32, 0, 0, textureWidth, "tileset");
    m_tileMap->LoadFromCSV("../CSV/map100x100_from_uploaded_tileset.csv");

    if (res && m_pSDLWindow && m_pRender)
    {
        m_bIsRunning = true;
    }

    return m_bIsRunning;
}

void gameApp::Shutdown()
{
    TextureManager::getInstance().cleanImage();

    delete m_tileMap;

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
    const float scrollSpeed = 4.0f;

    const int32_t tilesInViewX = m_u32WindowWidth / 32;
    const int32_t tilesInViewY = m_u32WindowHeight / 32;

    auto amountOfMovement = (int32_t)(scrollSpeed * deltaTime);

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_W) || m_inputManager.IsKeyPressed(SDL_SCANCODE_UP))
    {
        m_tileMap->SetCameraY(m_tileMap->GetCameraY() - scrollSpeed);
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_S) || m_inputManager.IsKeyPressed(SDL_SCANCODE_DOWN))
    {
        m_tileMap->SetCameraY(m_tileMap->GetCameraY() + scrollSpeed);
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_A) || m_inputManager.IsKeyPressed(SDL_SCANCODE_LEFT))
    {
        m_tileMap->SetCameraX(m_tileMap->GetCameraX() - scrollSpeed);
    }

    if (m_inputManager.IsKeyPressed(SDL_SCANCODE_D) || m_inputManager.IsKeyPressed(SDL_SCANCODE_RIGHT))
    {
        m_tileMap->SetCameraX(m_tileMap->GetCameraX() + scrollSpeed);
    }

    float maxScrollX = m_tileMap->GetNumOfCol() * 32 - m_u32WindowWidth;
    float maxScrollY = m_tileMap->GetNumOfRows() * 32 - m_u32WindowHeight;

    m_tileMap->SetCameraX(std::clamp(m_tileMap->GetCameraX(), 0.0f, maxScrollX));
    m_tileMap->SetCameraY(std::clamp(m_tileMap->GetCameraY(), 0.0f, maxScrollY));

//    m_tileMap->SetCameraX(std::clamp(m_tileMap->GetCameraX(), 0, m_tileMap->GetNumOfCol() - tilesInViewX));
//    m_tileMap->SetCameraY(std::clamp(m_tileMap->GetCameraY(), 0, m_tileMap->GetNumOfRows() - tilesInViewY));
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
    SDL_RenderClear(m_pRender);

    m_tileMap->Render(m_pRender);

    SDL_RenderPresent(m_pRender);
}
