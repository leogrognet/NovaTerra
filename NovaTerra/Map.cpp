#include "Map.h"

//Map::Map(const string& filename, const string& tilesetPath, const string& itemsetPath, int tileSize, vector<int> blockedTileValues, vector<int> blockedItemValues)
//    : tileSize(tileSize), blockedTileValues(blockedTileValues), blockedItemValues(blockedItemValues) {

Map::Map(const string& filename, const string& tilesetPath, int tileSize, vector<int> blockedTileValues)
    : tileSize(tileSize), blockedTileValues(blockedTileValues) {

    if (!tileSet.loadFromFile(tilesetPath)) {
        cerr << "Erreur de chargement du tileset principal" << endl;
    }
    //if (!itemSet.loadFromFile(itemsetPath)) {
    //    cerr << "Erreur de chargement du tileset des items" << endl;
    //}

    loadFromFile(filename);

    generateTiles();
    //generateItems();
}

// CHARGEMENT DU FICHIER DE LA CARTE

void Map::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de charger le fichier " << filename << std::endl;
        return;
    }

    m_tiles.clear();

    int x, y, tileID;
    while (file >> x >> y >> tileID) {
        m_tiles[{x, y}] = tileID;
    }

    file.close();
    std::cout << "Niveau chargé depuis " << filename << std::endl;
}

    

// GÉNÉRATION DES OBJETS



// GÉNÉRATION DES TUILES

void Map::generateTiles() {
    for (const auto& [pos, tileID] : m_tiles) {
        m_entityTypeTile = static_cast<entityType>(tileID);
        switch (m_entityTypeTile)
        {
        case GOLEM:
            break;
        case PLAYER:
            break;
        case TILE:
            break;
        case NOTYPE:
            break;
        default:
            break;
        }
    }
}

// COLLISIONS

bool Map::isWalkable(Vector2f position, Vector2f playerSize, FloatRect hitboxBounds) {
    //Vérifie la collision avec les tuiles bloquantes (y compris les 99)
    for (const auto& tile : blockedTiles) {
        FloatRect tileBounds(tile.x * tileSize, tile.y * tileSize, tileSize, tileSize);
        if (hitboxBounds.intersects(tileBounds)) {
            return false;
        }
    }
    //Vérifie la collision avec les items bloquants (mais PAS les `99`)
    //for (const auto& item : blockedItemTiles) {
    //    FloatRect itemBounds(item.x * tileSize, item.y * tileSize, tileSize, tileSize);
    //    if (hitboxBounds.intersects(itemBounds)) {
    //        return false;
    //    }
    //}

    return true;
}


// AFFICHAGE DE LA CARTE

void Map::draw(RenderWindow& window) {
    if (tiles.empty()) {
        cerr << "Erreur : Aucun tile à afficher !" << endl;
        return;
    }

    for (const auto& tile : tiles) {
        window.draw(tile);
    }

    //for (const auto& item : items) {
    //    window.draw(item);
    //}
}




// GUETTERS

int Map::getTileAt(const Vector2f& position) {
    int tileX = static_cast<int>(position.x / tileSize);
    int tileY = static_cast<int>(position.y / tileSize);

    if (tileX < 0 || tileX >= tileMap[0].size() || tileY < 0 || tileY >= tileMap.size()) {
        cerr << "Erreur : Position (" << tileX << "," << tileY << ") hors de la carte !" << endl;
        return -1;
    }

    return tileMap[tileY][tileX];
}

//int Map::getItemAt(const Vector2f& position) {
//    int tileX = static_cast<int>(position.x / tileSize);
//    int tileY = static_cast<int>(position.y / tileSize);
//
//    //Vérification si itemMap est vide AVANT d'y accéder
//    if (itemMap.empty()) {
//        cerr << "Erreur critique : itemMap est totalement vide !" << endl;
//        return -1;
//    }
//
//    if (itemMap[0].empty()) {
//        cerr << "Erreur : itemMap[0] est vide, aucune colonne n'est définie !" << endl;
//        return -1;
//    }
//
//    //Vérification des limites de la carte
//    if (tileY < 0 || tileY >= static_cast<int>(itemMap.size())) {
//        cerr << "Erreur : Y hors limites (" << tileY << " / " << itemMap.size() << ")" << endl;
//        return -1;
//    }
//
//    if (tileX < 0 || tileX >= static_cast<int>(itemMap[tileY].size())) {
//        cerr << "Erreur : X hors limites (" << tileX << " / " << itemMap[tileY].size() << ")" << endl;
//        return -1;
//    }
//
//    return itemMap[tileY][tileX]; //Retourne l'ID de l'item à cette position
//}