#pragma once

#include <set>
#include <map>

class Input {
public:	

	static void load();

	static void update();

	static void setKeyPressed(int key);
	static void setKeyReleased(int key);

	static bool getKeyPressed(int key);
	static bool getKeyReleased(int key);
	static bool getKeyDown(int key);

	static void setButton(std::string name, int key);
	
	static bool getButtonPressed(const std::string& name);
	static bool getButtonDown(const std::string& name);
	static bool getButtonReleased(const std::string& name);

private:

	static std::set<int> m_pressedKeys, m_downKeys, m_releasedKeys;
	static std::map<std::string, int> m_buttons;

};

