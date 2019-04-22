#pragma once
#include <map>
#include <string>

#include "ofSoundPlayer.h"
#include "ofImage.h"

class DataManager {
public:

    static void load();    
    static void unload();

    static ofImage* getImage(const char* name);
    static ofSoundPlayer* getSound(const std::string& name);
    static void saveInputConfig(const std::map<std::string, int>& buttons, const std::string& filename);
    static void loadInputConfig(const std::string&);

private:

    static void loadFiles(std::vector<std::string>& files);
    static void loadImage(const std::string& file);
    static void loadSound(const std::string& file);

    static std::string getFileExtension(const std::string& file);
    static std::string getFileName(const std::string& file);
    static std::vector<std::string> getFileList(const std::string& path);

    static std::map<std::string, ofImage*> m_images;
    static std::map<std::string, ofSoundPlayer*> m_sounds;
};

