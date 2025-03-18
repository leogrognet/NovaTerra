#include "TextureLoader.h"
#include <iostream>

bool TextureLoader::loadTexture(const string& name, const string& filename)
{
    if (m_mapTextures.find(name) != m_mapTextures.end()) {
        return true;
    }

    auto texture = make_shared<Texture>();
    if (!texture->loadFromFile(filename)) {
        return false;
    }

    m_mapTextures[name] = texture;
    m_mapFilePaths[name] = filename;
    return true;
}

pair<shared_ptr<Texture>, IntRect> TextureLoader::GetTexture(int type)
{
    switch (type) {
    case 3:
    {
        loadTexture("tileset", "../assets/tiles1.png");

        if (m_mapTextures.find("tileset") != m_mapTextures.end()) {
            return { m_mapTextures["tileset"], IntRect(128, 384, 128, 128) };
        }
        break;
    }
    default:
        return { nullptr, IntRect() };
    }
    return { nullptr, IntRect() };
}
