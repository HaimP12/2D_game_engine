//
// Created by haimash on 7/21/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "TileMap.h"
#include "TextureManager.h"

TileMap::TileMap(int32_t n32TileWidth, int32_t n32TileHeight, int32_t n32NumOfRows, int32_t n32NumOfCol,
                 int32_t tilesetWidth, const std::string &strTextureID) :
                                                    m_n32TileWidth(n32TileWidth),
                                                    m_n32TileHeight(n32TileHeight),
                                                    m_n32Rows(n32NumOfRows),
                                                    m_n32Cols(n32NumOfCol),
                                                    m_n32TilesSetWidth(tilesetWidth),
                                                    m_textureID(strTextureID)
{
    m_mapData.resize(m_n32Rows * m_n32Cols, 0);
    m_camera = {0,0};
}

bool TileMap::LoadFromCSV(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open CSV file: " << filePath << "\n";
        return false;
    }

    std::string line;
    m_mapData.clear();
    m_n32Cols = 0;
    m_n32Rows = 0;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        int colCount = 0;

        while (std::getline(ss, cell, ','))
        {
            if (!cell.empty())
            {
                m_mapData.push_back(std::stoi(cell));
                ++colCount;
            }
        }

        // Set column count from the first row
        if (m_n32Rows == 0)
            m_n32Cols = colCount;

        ++m_n32Rows;
    }

    file.close();

    // Sanity check
    if (m_n32Cols * m_n32Rows != static_cast<int>(m_mapData.size()))
    {
        std::cerr << "CSV size mismatch: " << m_mapData.size()
                  << " values vs " << m_n32Cols << "x" << m_n32Rows << "\n";
        return false;
    }

    return true;
}

void TileMap::LoadMap(const std::vector<int32_t> &mapData)
{
    if (mapData.size() != (m_n32Cols * m_n32Rows))
    {

    }

    m_mapData = mapData;
}

void TileMap::Render(SDL_Renderer *pRenderer)
{
    const int32_t tilesPerRow = m_n32TilesSetWidth / m_n32TileWidth;

    const int32_t mapPixelWidth = m_n32Cols * m_n32TileWidth;
    const int32_t mapPixelHeight = m_n32Rows * m_n32TileHeight;

    const int32_t windowWidth = 640;
    const int32_t windowHeight = 480;

    const int32_t tilesInViewX = windowWidth / m_n32TileWidth;
    const int32_t tilesInViewY = windowHeight / m_n32TileHeight;

    int32_t startCol = static_cast<int32_t>(m_camera.xScroll) / m_n32TileWidth;
    int32_t startRow = static_cast<int32_t>(m_camera.yScroll) / m_n32TileHeight;

    int32_t offsetX = static_cast<int32_t>(m_camera.xScroll) % m_n32TileWidth;
    int32_t offsetY = static_cast<int32_t>(m_camera.yScroll) % m_n32TileHeight;

//    m_camera.xScroll = std::clamp(m_camera.xScroll, 0, m_n32Cols - tilesInViewX);
//    m_camera.yScroll = std::clamp(m_camera.yScroll, 0, m_n32Rows - tilesInViewY);

    for (int32_t row = 0; row < tilesInViewY; row++)
    {
        for (int32_t col = 0; col < tilesInViewX; col++)
        {
            int32_t mapRow = startRow + row;
            int32_t mapCol = startCol + col;

            if (mapRow >= m_n32Rows || mapCol >= m_n32Cols)
                continue;

            int32_t tileIndex = GetTile(mapRow, mapCol);

            int32_t srcX = (tileIndex % tilesPerRow) * m_n32TileWidth;
            int32_t srcY = (tileIndex / tilesPerRow) * m_n32TileHeight;

            int32_t dstX = col * m_n32TileWidth - offsetX;
            int32_t dstY = row * m_n32TileHeight - offsetY;

            SDL_Rect srcRect = {srcX, srcY, m_n32TileWidth, m_n32TileHeight};
            SDL_Rect dstRect = {dstX, dstY, m_n32TileWidth, m_n32TileHeight};

            TextureManager::getInstance().drawImage(m_textureID, srcRect, dstRect, pRenderer);
        }
    }
}

int32_t TileMap::GetTile(int32_t row, int32_t col) const
{
    return m_mapData[Index(row, col)];
}

void TileMap::SetTile(int32_t row, int32_t col, int32_t tileID)
{
    m_mapData[Index(row, col)] = tileID;
}

uint32_t TileMap::Index(int32_t row, int32_t col) const
{
    return static_cast<uint32_t>(row * m_n32Cols + col);
}

void TileMap::SetCameraX(float newX)
{
    m_camera.xScroll = newX;
}

void TileMap::SetCameraY(float newY)
{
    m_camera.yScroll = newY;
}

float TileMap::GetCameraY() const
{
    return m_camera.yScroll;
}

float TileMap::GetCameraX() const
{
    return m_camera.xScroll;
}

int32_t TileMap::GetNumOfCol() const
{
    return m_n32Cols;
}

int32_t TileMap::GetNumOfRows() const
{
    return m_n32Rows;
}
