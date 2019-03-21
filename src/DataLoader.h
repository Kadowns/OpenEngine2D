#pragma once
#include <map>
#include <string>

#include <ofImage.h>

class DataLoader {

private:

	DataLoader();

	std::map<std::string, ofImage*> m_images;

	const std::string PATH_IMAGE_SHIP = "ship.png";

	std::string getFileName(const std::string& file);
	

public:

	static DataLoader& instance();

	~DataLoader();

	ofImage* getImage(const char* name);

};

