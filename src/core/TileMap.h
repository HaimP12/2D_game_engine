//
// Created by haimash on 7/21/25.
//

#ifndef GAME_TILEMAP_H
#define GAME_TILEMAP_H

#include <string>
#include <vector>
#include <SDL.h>

class TileMap
{
public:
    /// create tile map
    /// \param n32TileWidth the width of each tile
    /// \param n32TileHeight the height of each tile
    /// \param n32NumOfRows the number of rows in the map
    /// \param n32NumOfCol the number of columns in the map
    /// \param strTextureID the unique name id of the tile set
    TileMap(int32_t n32TileWidth, int32_t n32TileHeight,
            int32_t n32NumOfRows, int32_t n32NumOfCol,
            int32_t tilesetWidth, const std::string &strTextureID);

    /// load the data map
    /// \param mapData
    void LoadMap(const std::vector<int32_t>& mapData);
    void Render(SDL_Renderer* renderer);

    [[nodiscard]] int32_t GetTile(int32_t row, int32_t col) const;
    void SetTile(int32_t row, int32_t col, int32_t tileID);

    bool LoadFromCSV(const std::string& filePath);

    void SetCameraX(float newX);
    void SetCameraY(float newY);

    float GetCameraX() const;
    float GetCameraY() const;

    int32_t GetNumOfRows() const;
    int32_t GetNumOfCol() const;

    typedef struct camera
    {
        float xScroll;
        float yScroll;
    }camera;


private:
    [[nodiscard]] uint32_t Index(int32_t row, int32_t col) const;

private:
    int32_t m_n32TileWidth;
    int32_t m_n32TileHeight;
    int32_t m_n32Rows;
    int32_t m_n32Cols;
    int32_t m_n32TilesSetWidth;
    std::string m_textureID;
    std::vector<int32_t> m_mapData;
    camera m_camera;
};


#endif //GAME_TILEMAP_H
