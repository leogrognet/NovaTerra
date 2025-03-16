#include "ScriptBox.h"
#include <sstream>

void Script::setScript()
{
    m_textLine.clear();
    for (const auto& text : m_textPath) {
        std::ifstream file(text);
        if (!file) {
            std::cerr << "Erreur lors de l'ouverture du fichier : " << text << std::endl;
            continue;
        }
        std::string line;
        while (std::getline(file, line)) {
            m_textLine.push_back(line);
        }
    }

    formatText();
}

void Script::loadScript(std::string textPathType)
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

    setScript();
}

void Script::formatText()
{
    float maxWidth = m_textBox.getGlobalBounds().width - 10;
    m_textFormat.clear();

    for (const auto& line : m_textLine) {
        if (line.empty()) {
            m_textFormat.push_back("");
            continue;
        }

        std::istringstream words(line);
        std::string word, newLine;

        while (words >> word) {
            std::string testLine = m_currentLine + newLine.empty() ? word : newLine + " " + word;

            m_text.setString(testLine);

            if (m_text.getLocalBounds().width > maxWidth) {
                m_textFormat.push_back(newLine);
                newLine = word;
            }
            else {
                newLine = testLine;
            }
        }

        if (!newLine.empty())
            m_textFormat.push_back(newLine);
    }
    m_currentLine = 0;
    m_displayedText = "";
}

void Script::updateScriptBox(float deltaTime)
{
    m_typingIncr += deltaTime;

    if (m_textFormat.empty()) {
        m_isTyping = false;
        return;
    }

    if (m_isTyping && m_typingIncr > m_typingCoolDown) {
        if (m_currentLine < m_textFormat.size() && m_char < m_textFormat[m_currentLine].size()) {
            m_displayedText += m_textFormat[m_currentLine][m_char++];
            m_text.setString(m_displayedText);
            m_typingIncr = 0;
        }

        if (m_char >= m_textFormat[m_currentLine].size()) {
            m_char = 0;
            m_currentLine++;

            if (m_currentLine >= m_textFormat.size() || m_currentLine >= m_maxLines) {
                m_isTyping = false;
                return;
            }

            m_displayedText += "\n";
            m_text.setString(m_displayedText);
        }
    }
}

void Script::drawBox(sf::RenderWindow& window)
{
    window.draw(m_visibleBox);
    window.draw(m_text);
    window.draw(m_textBox);
}

Script::Script()
    : m_line(0), m_char(0), m_currentLine(0), m_maxLines(4), m_isTyping(true), m_typingCoolDown(0.005f), m_typingIncr(0.0f)
{
    m_boxTexture = std::make_unique<sf::Texture>();
    if (!m_boxTexture->loadFromFile("C:/Users/leoam/source/repos/NovaTerra/NovaTerra/assets/Image de Scipt/Box.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de la boîte !" << std::endl;
    }
    m_visibleBox.setTexture(*m_boxTexture);
    m_visibleBox.setScale(0.8f, 0.8f);
    m_visibleBox.setPosition(40.f, 400.f);

    m_textBox.setSize(sf::Vector2f(m_visibleBox.getGlobalBounds().width - 220, m_visibleBox.getGlobalBounds().height - 70));
    m_textBox.setPosition(m_visibleBox.getPosition().x + 90, m_visibleBox.getPosition().y + 35);
    m_textBox.setFillColor(sf::Color::Transparent);
    m_textBox.setOutlineColor(sf::Color::Red);
    m_textBox.setOutlineThickness(2);

    if (!m_font.loadFromFile("C:/Users/leoam/source/repos/NovaTerra/NovaTerra/assets/font/default.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(m_textBox.getPosition().x, m_textBox.getPosition().y);
}
