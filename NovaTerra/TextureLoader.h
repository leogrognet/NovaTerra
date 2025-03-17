#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;

using namespace sf;
using namespace std;

class TextureLoader {
private:
	vector<string> imagesPath;
	

public:
	void loadTexture(string& imagePathType, vector<shared_ptr<Texture>>& textureList);
	TextureLoader();
};