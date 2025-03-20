#include "Map.h"

Map::Map(const string& filename, const string& tilesetPath, int tileSize, vector<int> blockedTileValues, RenderWindow& window)
    : tileSize(tileSize), blockedTileValues(blockedTileValues), m_levelEditor(window) {

    if (!tileSet.loadFromFile(tilesetPath)) {
        cerr << "Erreur de chargement du tileset principal" << endl;
    }

    loadFromFile("../NovaTerra/assets/map/lobby.txt");
}


// CHARGEMENT DU FICHIER DE LA CARTE

void Map::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erreur : Impossible de charger le fichier " << filename << endl;
        return;
    }

    m_tiles.clear();


    int x, y, tileID, textureIndex;
    while (file >> x >> y >> tileID >> textureIndex) {
        m_tiles[{x, y}] = { tileID, textureIndex };
    }

    file.close();
    cout << "Niveau chargé depuis " << filename << endl;

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
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128/2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_1.at(tileID.second)));
            break;
        case BIOME_2_PLAT:
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_2.at(tileID.second)));
            break;
        case BIOME_3_PLAT:
            allEntities.push_back(make_shared<Plateform>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(0.5f, 1.f), true, true, m_levelEditor.m_SperatedTileTextures_1.at(tileID.second)));
            break;
        case GOLEM:
            allEntities.push_back(make_shared<GolemEnemy>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), false,false));
            break;
        case PUNGUS:
            allEntities.push_back(make_shared<Pungus>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), false, false));
        case CROC:
            //allEntities.push_back(make_shared<>());
            break;
        case MOVE_PLAT:
            allEntities.push_back(make_shared<MovePlat>(float(pos.first*128 / 2),float(pos.second*128 / 2),Vector2f(0.5f, 1.f),true,true));
            break;
        case BOUNCE_PLAT:
            allEntities.push_back(make_shared<Bounce>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), Vector2f(1, 1), true, true));
            break;
        case GRIND_VINE:
            allEntities.push_back(make_shared<Vine>(float(pos.first * 128 / 2), float(pos.second * 128 / 2), 1, 1, true, false));
            break;
        case DOOR:
            //allEntities.push_back(make_shared<Plateform>());
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

// COLLISIONS

bool Map::isWalkable(Vector2f position, Vector2f playerSize, FloatRect hitboxBounds) {
    for (const auto& tile : blockedTiles) {
        FloatRect tileBounds(tile.x * tileSize, tile.y * tileSize, tileSize, tileSize);
        if (hitboxBounds.intersects(tileBounds)) {
            return false;
        }
    }
    return true;
}

int Map::getTileAt(const Vector2f& position) {
    int tileX = static_cast<int>(position.x / tileSize);
    int tileY = static_cast<int>(position.y / tileSize);

    if (tileX < 0 || tileX >= tileMap[0].size() || tileY < 0 || tileY >= tileMap.size()) {
        cerr << "Erreur : Position (" << tileX << "," << tileY << ") hors de la carte !" << endl;
        return -1;
    }

    return tileMap[tileY][tileX];
}