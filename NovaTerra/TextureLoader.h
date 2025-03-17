#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;
using namespace sf;

class TextureLoader {
public:

	bool loadTexture(const string& name, const string& filename);
	pair<shared_ptr<Texture>, IntRect> GetTexture(int type);

private:
	unordered_map <string, shared_ptr<Texture>> m_mapTextures;
	unordered_map<string, IntRect> m_mapTileRects;
	unordered_map<string, string> m_mapFilePaths;


};
