#include "TextureLoader.h"

TextureLoader::TextureLoader()
    : m_tileWidth(128), m_tileHeight(128), m_tilesetWidth(0), m_tilesetHeight(0)
{
}

void TextureLoader::loadTextureAssets()
{
    m_tilesetTexture = make_shared<Texture>();
    if (!m_tilesetTexture->loadFromFile("../assets/tiles1.png")) {
        std::cerr << "Erreur lors du chargement du tileset" << std::endl;
        return;
    }

    m_tilesetWidth = m_tilesetTexture->getSize().x / m_tileWidth;
    m_tilesetHeight = m_tilesetTexture->getSize().y / m_tileHeight;
}

Sprite TextureLoader::getTileFromCoordinates(int tileX, int tileY)
{
    int x = tileX * m_tileWidth;
    int y = tileY * m_tileHeight;

    Sprite tileSprite(*m_tilesetTexture);
    tileSprite.setTextureRect(IntRect(x, y, m_tileWidth, m_tileHeight));

    return tileSprite;
}

void TextureLoader::clearTexture()
{
    m_tilesetTexture.reset();
}
