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
#include "Firecamp.h"
#include "FallingPlatform.h"
#include "KillerEnemy.h"


using namespace sf;
using namespace std;

// Class Map avec comme exemple pour le moment un map avec vu du dessus, class normalement modulable pour le side-scrolling

class Map {
private:

    map<pair<int, int>, pair<int, int>> m_tiles;



    entityType m_entityTypeTile;
    vector<vector<int>> tileMap;
    vector<shared_ptr<Entity>> m_allEntities;



public:
    Map(string& file, RenderWindow& window);

    void loadFromFile(const string& filename);

    string m_currentLevel;


    LevelEditor m_levelEditor;
    vector<shared_ptr<Entity>> generateTiles(vector<shared_ptr<Texture>> textureList, vector<shared_ptr<Entity>> collideVec);
};

#endif