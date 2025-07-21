//
// Created by haimash on 7/20/25.
//

#ifndef GAME_TEXTUREMANAGER_H
#define GAME_TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>

class TextureManager
{
public:
    /// get instance of the texture manager
    /// \return reference to the texture manager
    static TextureManager& getInstance();

    /// laod image from file
    /// \param id the name of the image
    /// \param imagePath the path to the image
    /// \param pRenderer pointer to renderer object
    /// \return true for success, otherwise false
    [[nodiscard]] bool loadImage(const std::string& id, const std::string& imagePath, SDL_Renderer* pRenderer);

    /// draw to image on the screen
    /// \param id the name of the image
    /// \param srcRect what part of the texture to draw
    /// \param destRect where and at what size to draw
    /// \param pRenderer pointer to renderer object
    void drawImage(const std::string& id, const SDL_Rect& srcRect,
                   const SDL_Rect& destRect,
                   SDL_Renderer* pRenderer);

    /// clean the image from the window
    void cleanImage();

    SDL_Texture* getTexture(const std::string& id) const;

private:
    TextureManager() = default;

    std::unordered_map<std::string, SDL_Texture*> m_textureMap;
};


#endif //GAME_TEXTUREMANAGER_H
