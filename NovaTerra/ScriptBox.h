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
	void loadScript(string textPathType);
	void updateScriptBox(float deltaTime);
	void formatText();
	void drawBox(RenderWindow& window);
	Script();



private:
	Font m_font;
	Text m_text;
	Sprite m_visibleBox;
	unique_ptr<Texture> m_boxTexture;
	string m_displayedText;
	RectangleShape m_textBox;

	vector<string> m_textFormat;
	vector<string> m_textPath;
	vector<string> m_textFile;
	vector<string> m_textLine;
	size_t m_currentLine;
	size_t m_maxLines;

	int m_line;
	int m_char;

	bool m_isScipting;
	bool m_isTyping;
	float m_typingCoolDown;
	float m_typingIncr;
	float m_timeChange;
};