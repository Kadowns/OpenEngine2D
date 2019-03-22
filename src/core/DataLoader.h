#pragma once
#include <map>
#include <string>

#include "ofImage.h"

class DataLoader {
public:

    static void loadImages();    
    static void unloadImages();

    static ofImage* getImage(const char* name);

private:
    static void loadImage(const char* file);
    static std::string getFileName(const std::string& file);

    static std::map<std::string, ofImage*> m_images;
};

