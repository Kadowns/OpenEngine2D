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
	m_images[getFileName(PATH_IMAGE_SHIP).data()] = new ofImage(PATH_IMAGE_SHIP);
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
	if (m_images.find(name) != m_images.end()) {
		return	m_images.at(name);
	}
	return nullptr;
}
