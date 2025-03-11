#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;

using namespace sf;
using namespace std;

class TextureLoader {
private:
	vector<shared_ptr<Texture>> textureList;

	vector<string> imagesPath;
	void loadTexture(string& imagePathType);

public:
	TextureLoader(string imagePathType);
};