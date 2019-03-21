#include "DataLoader.h"


std::string DataLoader::getFileName(const std::string & file) {
	std::string name;
	for (auto& it : file) {
		if (it == '.')
			break;
		name += it;
	}
	return name;
}

DataLoader::DataLoader() {
	m_images["ship"] = new ofImage("ship.png");
	m_images["ship"]->resize(
		m_images["ship"]->getWidth() * 0.1f,
		m_images["ship"]->getHeight() * 0.1f
	);
	m_images["ship"]->setAnchorPercent(0.5f, 0.5f);

	m_images["bullet"] = new ofImage("bullet.png");
	m_images["bullet"]->resize(
		m_images["bullet"]->getWidth() * 0.1f,
		m_images["bullet"]->getHeight() * 0.1f
	);
	m_images["bullet"]->setAnchorPercent(0.5f, 0.5f);
}


DataLoader& DataLoader::instance() {
	static DataLoader s_instance;
	return s_instance;
}

DataLoader::~DataLoader() {

	for (auto& it : m_images) {
		delete it.second;
	}
}

ofImage* DataLoader::getImage(const char* name) {
	auto it = m_images.find(name);
	if (it != m_images.end()) {
		return it->second;
	}
	return nullptr; 
}
