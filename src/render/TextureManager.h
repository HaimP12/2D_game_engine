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
    static TextureManager& getInatnce();

    /// laod image from file
    /// \param id the name of the image
    /// \param imagePath the path to the image
    /// \param pRenderer pointer to renderer object
    /// \return true for success, otherwise false
    bool loadImage(const std::string& id, const std::string& imagePath, SDL_Renderer* pRenderer);
    /// draw to image on the screen
    /// \param id the name of the image
    /// \param imageLocationX the start of the image on the X axis
    /// \param imageLocationY the start of the image on the y axis
    /// \param width the width of the image on the window
    /// \param height the height of the image on the window
    /// \param pRenderer pointer to renderer object
    void drawImage(const std::string& id, int imageLocationX, int imageLocationY, int width,
                   int height,SDL_Renderer* pRenderer);

    /// clean the image from the window
    void cleanImage();

private:
    TextureManager() = default;

    std::unordered_map<std::string, SDL_Texture*> m_textureMap;
};


#endif //GAME_TEXTUREMANAGER_H
