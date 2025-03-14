#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;


namespace fs = std::filesystem;

class Script {
public:
	
	void setScript();
	void loadScript(string& textPathType);
	void updateScriptBox();
	void drawBox(RenderWindow& window);
	


private:
	Font m_font;
	Text m_text;
	Sprite m_box;
	vector<string> m_textPath;
	vector<string> m_textFile;
	vector<string> m_textLine;

	bool m_isTyping;
};