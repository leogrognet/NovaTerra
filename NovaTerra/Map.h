#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Entity.h";
#include "MovingPlatform.h"
#include "Plateform.h"
#include "GolemEnemy.h"
#include "Pungus.h"
#include "BouncingPlatform.h"
#include "VineLadder.h"
#include "LevelEditor.h"
 

using namespace sf;
using namespace std;

// Class Map avec comme exemple pour le moment un map avec vu du dessus, class normalement modulable pour le side-scrolling

class Map {
private:
    //Calques de la carte

    map<pair<int, int>, pair<int, int>> m_tiles;



    entityType m_entityTypeTile;
    vector<vector<int>> tileMap; 


    vector<shared_ptr<Entity>> m_allEntities;
    //vector<vector<int>> itemMap;
    //vector<vector<int>> entityMap;

    //Blocages (collision)
    vector<int> blockedTileValues;
    //vector<int> blockedItemValues;
    vector<Vector2i> blockedTiles;
    //vector<Vector2i> blockedItemTiles;

    //item speciaux
    //vector<Vector2f> potionPositions;
    //vector<Vector2f> chestPositions;

    //Entités du jeu
    //vector<Vector2f> chaserEnemyPositions;
    //Vector2f bossPosition;
    //vector<Vector2f> patternEnemyPositions;
    //vector<Vector2f> npcPositions;
    //Vector2f playerStartPosition = {0, 0};
    //Vector2f alternativeSpawnPosition = { 0, 0 };

    //Graphiques
    Texture tileSet;
    //Texture itemSet;
    vector<Sprite> tiles;
    //vector<Sprite> items;

    int tileSize;


    //Fonctions de chargement
    void loadFromFile(const string& filename);
    
public:
    //Constructeur
    Map(const string& filename, const string& tilesetPath, int tileSize, vector<int> blockedTileValues, RenderWindow& window);

    LevelEditor m_levelEditor;
    vector<shared_ptr<Entity>> generateTiles(vector<shared_ptr<Texture>> textureList, vector<shared_ptr<Entity>> collideVec);
    //void generateItems();

    //Guetters
    /*vector<Vector2f> getChaserEnemyPositions() const { return chaserEnemyPositions; }
    vector<Vector2f> getPatternEnemyPositions() const { return patternEnemyPositions; }
    Vector2f getBossPosition() const { return bossPosition; }
    Vector2f getPlayerStartPosition() const { return playerStartPosition; }
    vector<Vector2f> getNpcPositions() const { return npcPositions; }
    vector<Vector2f> getPotionPositions() const { return potionPositions; }
    vector<Vector2f> getChestPositions() const { return chestPositions; }*/
    int getTileAt(const Vector2f& position);
    //int getItemAt(const Vector2f& position);
    int getWidth() const { return tileMap.size(); }
    int getHeight() const { return (tileMap.empty() ? 0 : tileMap[0].size()); }
    int getTileCount() const { return tiles.size(); }
    /*int getItemCount() const { return items.size(); }
    Vector2f getSpawnPoint1() const { return playerStartPosition; }
    Vector2f getSpawnPoint2() const { return alternativeSpawnPosition; }*/



    //Fonctions principales
    void draw(RenderWindow& window);
    bool isWalkable(Vector2f position, Vector2f playerSize, FloatRect hitboxBounds);
};

#endif