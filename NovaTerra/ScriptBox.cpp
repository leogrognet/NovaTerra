#include "ScriptBox.h"

void Script::setScript()
{
	for (const auto& text : m_textPath) {
		ifstream file(text);
		if (!file) {
			cerr << "Erreur lors de l'ouverture du fichier : " << text << endl;
			continue;
		}
		string line;
		int lineCount = 0;
		while (getline(file, line)) {
			m_textLine.push_back(line);
		}
	}



}

void Script::loadScript(string& textPathType)
{
	try {
		for (const auto& entry : fs::directory_iterator(textPathType)) {
			m_textPath.push_back(entry.path().string());
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Erreur de système de fichiers lors de l'itération du répertoire " << textPathType
			<< " : " << e.what() << std::endl;
	}
}

void Script::updateScriptBox(float deltaTime)
{
	m_typingIncr += deltaTime;

		for (auto& line : m_textLine) {
			if (m_isTyping && m_typingIncr > m_typingCoolDown) {

				for (auto& chr : line) {
					displayedText +=
				}
		}
	}

}


void Script::displayerBox() {

}

void Script::drawBox(RenderWindow& window)
{
	window.draw(m_box);

}


