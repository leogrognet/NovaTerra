#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory> // Pour shared_ptr

using namespace std;
using namespace sf;

class TextureLoader {
public:
    TextureLoader();

    void loadTextureAssets();  // Charge le tileset
    Sprite getTileSprite(int tileIndex);  // Retourne un sprite pour une tuile spécifique dans le tileset
    Sprite getTileFromCoordinates(int tileX, int tileY); // Retourne un sprite basé sur les coordonnées d'une tuile
    void clearTexture();  // Vider la map des textures

private:
    shared_ptr<Texture> m_tilesetTexture;  // Texture principale (le tileset)
    int m_tileWidth;  // Largeur d'une tuile
    int m_tileHeight; // Hauteur d'une tuile
    int m_tilesetWidth; // Largeur du tileset (en tuiles)
    int m_tilesetHeight; // Hauteur du tileset (en tuiles)
};
