#include "DataManager.h"

#include "boost/filesystem.hpp"

#include "InputManager.h"


std::map<std::string, ofImage*> DataManager::m_images;
std::map<std::string, ofSoundPlayer*> DataManager::m_sounds;

void DataManager::unload() {
	for (auto& it : m_images) {
		delete it.second;
	}
    m_images.clear();
}

void DataManager::loadFiles(std::vector<std::string>& files) {
    for (auto file : files) {
        auto extension = getFileExtension(file);
        if (extension == ".png" || extension == ".jpg") {
            loadImage(file);
        }
        else if (extension == ".mp3" || extension == ".ogg") {
            loadSound(file);
        }
        else if (extension == ".input") {
            loadInputConfig(file);
        }
    }
}

void DataManager::loadImage(const std::string& file) {
    auto name = getFileName(file);
    m_images[name] = new ofImage(file);
    m_images[name]->resize(
        m_images[name]->getWidth() * 0.1f,
        m_images[name]->getHeight() * 0.1f
    );
    m_images[name]->setAnchorPercent(0.5f, 0.5f);
}

void DataManager::loadSound(const std::string& file) {
    auto name = getFileName(file);
    m_sounds[name] = new ofSoundPlayer();
    m_sounds[name]->load(file);
}

std::string DataManager::getFileExtension(const std::string& file) {        
    return file.substr(file.find('.'));
}

std::string DataManager::getFileName(const std::string& file) {
    return file.substr(0, file.find('.'));
}

void DataManager::load() {    

    auto files = getFileList("bin/data");
    loadFiles(files);
}

std::vector<std::string> DataManager::getFileList(const std::string& path) {
    std::vector<std::string> fileList;
    if (!path.empty()) {
        namespace fs = boost::filesystem;

        fs::path dirPath(path);
        fs::recursive_directory_iterator end;

        for (fs::recursive_directory_iterator i(dirPath); i != end; ++i) {
            const fs::path cp = (*i);
            std::string filename = cp.string().substr(cp.string().find("data\\") + 5);//gambiarra
            fileList.push_back(filename);
            std::cout << filename << std::endl;
        }
    }
    return fileList;
}

ofImage* DataManager::getImage(const char* name) {
	auto it = m_images.find(name);
	if (it != m_images.end()) {
		return it->second;
	}
	return nullptr; 
}

ofSoundPlayer* DataManager::getSound(const std::string & name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        return it->second;
    }
    return nullptr;
}

void DataManager::saveInputConfig(const std::map<std::string, int>& buttons, const std::string& filename) {
    ofstream file;
    file.open("bin/data/" + filename);
    for (auto it : buttons) {
        file << it.first << ":" << it.second << std::endl;
    }    
    file.close();
}

void DataManager::loadInputConfig(const std::string& path) {

    std::map<std::string, int> buttons;
    ifstream file;
    file.open("bin/data/" + path);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            buttons[line.substr(0, line.find(":"))] = std::stoi(line.substr(line.find(":") + 1));
        }
    }
    file.close();
    InputManager::setButtonMap(buttons);
}
