//
// Created by haimash on 7/20/25.
//

#include "TextureManager.h"

TextureManager &TextureManager::getInatnce()
{
    static TextureManager textureManager;

    return textureManager;
}

bool TextureManager::loadImage(const std::string &id, const std::string &imagePath, SDL_Renderer *pRenderer)
{
    bool res = false;
    SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());
    SDL_Texture* imageTexture = nullptr;

    if (imageSurface)
    {
        imageTexture = SDL_CreateTextureFromSurface(pRenderer, imageSurface);
        SDL_FreeSurface(imageSurface);

        if (imageTexture)
        {
            res = true;
        }
    }

    m_textureMap[id] = imageTexture;

    return res;
}

void TextureManager::drawImage(const std::string &id, int imageLocationX, int imageLocationY, int width,
                               int height, SDL_Renderer *pRenderer)
{
    const SDL_Rect destRect = {imageLocationX, imageLocationY, width, height};
    SDL_RenderCopy(pRenderer, m_textureMap[id], nullptr, &destRect);
}

void TextureManager::cleanImage()
{
    for (const auto& iter : m_textureMap)
    {
        SDL_DestroyTexture(iter.second);
    }

    m_textureMap.clear();
}
