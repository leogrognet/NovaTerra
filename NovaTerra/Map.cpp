#include "Map.h"


Map::Map(string& file, RenderWindow& window) : m_levelEditor(window)
{
    loadFromFile(file);
}

void Map::loadFromFile(const string& filename) {
    m_currentLevel = filename;
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de charger le fichier " << filename << std::endl;
        return;
    }

    m_tiles.clear();


    int x, y, tileID, textureIndex;
    while (file >> x >> y >> tileID >> textureIndex) {
        m_tiles[{x, y}] = { tileID, textureIndex };
    }

    file.close();
    std::cout << "Niveau chargé depuis " << filename << std::endl;

}


vector<shared_ptr<Entity>> Map::generateTiles(vector<shared_ptr<Texture>> textureList, vector<shared_ptr<Entity>> collideVec)
{
    vector<shared_ptr<Entity>> allEntities;
    for (const auto& [pos, tileID] : m_tiles) {
        entityType entity;
        entity = static_cast<entityType>(tileID.first);
        auto rect = make_unique<RectangleShape>();
        switch (entity)
        {
        case BIOME_1_PLAT:
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_1.at(tileID.second)));
            break;
        case BIOME_2_PLAT:
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_2.at(tileID.second)));
            break;
        case BIOME_3_PLAT:
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_1.at(tileID.second)));
            break;
        case GOLEM:
            allEntities.push_back(make_shared<GolemEnemy>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), false, false));
            break;
        case PUNGUS:
            allEntities.push_back(make_shared<Pungus>(400, 500, false, false));
        case CROC:
            //allEntities.push_back(make_shared<>());a
            break;
        case MOVE_PLAT:
            allEntities.push_back(make_shared<MovePlat>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true));
            break;
        case BOUNCE_PLAT:
            allEntities.push_back(make_shared<Bounce>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true));
            break;
        case GRIND_VINE:
            allEntities.push_back(make_shared<Vine>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), 1, 1, true, false));
            break;
        case DOOR:
            //allEntities.push_back(make_shared<Plateform>());
            break;
        case FALLING_PLAT:
            allEntities.push_back(make_shared<FallingPlat>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.25f, 0.25f), true, true));
            break;
        default:
            break;
        }

    }
    for (const auto& [pos, tileID] : m_tiles) {
        entityType entity;
        entity = static_cast<entityType>(tileID.first);
        auto rect = make_unique<RectangleShape>();
        switch (entity)
        {
        case PLAYER:
            allEntities.push_back(make_shared<Player>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), false, true));
            break;
        default:
            break;
        }

    }
    return allEntities;
}