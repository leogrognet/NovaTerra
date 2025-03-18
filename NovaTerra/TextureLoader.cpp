#include "TextureLoader.h"

void TextureLoader::loadTexture(string& imagePathType, vector<shared_ptr<Texture>>& textureList)
{
	try {

		try {
			for (const auto& entry : fs::directory_iterator(imagePathType)) {
				imagesPath.push_back(entry.path().string());
			}
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Erreur de syst�me de fichiers lors de l'it�ration du r�pertoire " << imagePathType
				<< " : " << e.what() << std::endl;
		}

		for (auto image : imagesPath) {
			try {
				textureList.push_back(std::make_shared<sf::Texture>());
				if (!textureList.back()->loadFromFile(image)) {
					std::cerr << "Erreur : impossible de charger la texture depuis " << image << std::endl;
				}
				textureList.back()->setSmooth(true);
			}
			catch (const exception& e) {
				std::cerr << "Erreur lors du chargement de la texture " << image << " : " << e.what() << std::endl;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Une erreur s'est produite lors du chargement des textures : " << e.what() << std::endl;
	}
}



TextureLoader::TextureLoader()
{
}

