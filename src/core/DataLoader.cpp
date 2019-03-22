#include "DataLoader.h"


std::map<std::string, ofImage*> DataLoader::m_images;

void DataLoader::unloadImages() {
	for (auto& it : m_images) {
		delete it.second;
	}
    m_images.clear();
}

void DataLoader::loadImage(const char* file) {
    auto name = getFileName(file);
    m_images[name] = new ofImage(file);
    m_images[name]->resize(
        m_images[name]->getWidth() * 0.1f,
        m_images[name]->getHeight() * 0.1f
    );
    m_images[name]->setAnchorPercent(0.5f, 0.5f);
}

std::string DataLoader::getFileName(const std::string& file) {
    std::string name;
    for (auto& it : file) {
        if (it == '.')
            break;
        name += it;
    }
    return name;
}

void DataLoader::loadImages() {
    loadImage("ship.png");
    loadImage("bullet.png");
}

ofImage* DataLoader::getImage(const char* name) {
	auto it = m_images.find(name);
	if (it != m_images.end()) {
		return it->second;
	}
	return nullptr; 
}
