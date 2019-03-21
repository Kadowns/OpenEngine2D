#include "Input.h"
#include "ofConstants.h"

std::set<int> Input::m_downKeys;
std::set<int> Input::m_pressedKeys;
std::set<int> Input::m_releasedKeys;
std::map<std::string, int> Input::m_buttons;

void Input::load() {

	setButton("turnleft0", 'a');
	setButton("turnright0", 'd');
	setButton("moveup0", 'w');
	setButton("movedown0", 's');
	setButton("fire0", ' ');

	setButton("turnleft1", OF_KEY_LEFT);
	setButton("turnright1", OF_KEY_RIGHT);
	setButton("moveup1", OF_KEY_UP);
	setButton("movedown1", OF_KEY_DOWN);
	setButton("fire1", OF_KEY_RIGHT_CONTROL);

}

void Input::update() {
	m_pressedKeys.clear();
	m_releasedKeys.clear();
}

void Input::setKeyPressed(int key) {
	m_pressedKeys.insert(key);
	m_downKeys.insert(key);
}

void Input::setKeyReleased(int key) {
	m_releasedKeys.insert(key);
	m_downKeys.erase(key);
}

bool Input::getKeyPressed(int key) {
	return m_pressedKeys.find(key) != m_pressedKeys.end();
}

bool Input::getKeyReleased(int key) {
	return m_releasedKeys.find(key) != m_releasedKeys.end();
}

bool Input::getKeyDown(int key) {
	return m_downKeys.find(key) != m_downKeys.end();
}

void Input::setButton(std::string name, int key) {
	std::cout << name << ": " << key << std::endl;
	m_buttons[name] = key;
}

bool Input::getButtonPressed(const std::string& name) {
	return getKeyPressed(m_buttons[name]);
}

bool Input::getButtonDown(const std::string& name) {
	return getKeyDown(m_buttons[name]);
}

bool Input::getButtonReleased(const std::string& name) {
	return getKeyReleased(m_buttons[name]);
}
