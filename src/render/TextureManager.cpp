//
// Created by haimash on 7/20/25.
//

#include <iostream>
#include "TextureManager.h"

TextureManager &TextureManager::getInstance()
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
            SDL_SetTextureBlendMode(imageTexture, SDL_BLENDMODE_BLEND);
            res = true;
        }

        if (imageTexture)
        {
            res = true;
        }
    }

    if (false == res)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << "\n";
        return false;
    }

    m_textureMap[id] = imageTexture;

    return res;
}

void TextureManager::drawImage(const std::string &id, const SDL_Rect& srcRect,
                               const SDL_Rect& destRect,
                               SDL_Renderer *pRenderer)
{
    SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::cleanImage()
{
    for (const auto& iter : m_textureMap)
    {
        SDL_DestroyTexture(iter.second);
    }

    m_textureMap.clear();
}

SDL_Texture* TextureManager::getTexture(const std::string& id) const
{
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end())
    {
        return it->second;
    }
    return nullptr;
}
