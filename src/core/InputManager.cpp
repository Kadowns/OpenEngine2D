#include "InputManager.h"
#include "ofConstants.h"

#include "DataManager.h"

std::set<int> InputManager::m_downKeys;
std::set<int> InputManager::m_pressedKeys;
std::set<int> InputManager::m_releasedKeys;
std::map<std::string, int> InputManager::m_buttons;

Event<int, int>::EventListener InputManager::m_onMouseMoveCallback;
Event<int, int>::EventListener InputManager::m_onMouseClickCallback;
Event<int, int>::EventListener InputManager::m_onMouseReleasedCallback;

ofVec2f InputManager::m_mousePosition;

void InputManager::setup() {


    /*setButton("leftMouse", OF_MOUSE_BUTTON_1);
    setButton("rightMouse", OF_MOUSE_BUTTON_3);

	setButton("turnleft0", 'a');
	setButton("turnright0", 'd');
	setButton("forward0", 'w');
	setButton("backward0", 's');
	setButton("fire0", ' ');
    setButton("special0", OF_KEY_LEFT_CONTROL);

	setButton("turnleft1", OF_KEY_LEFT);
	setButton("turnright1", OF_KEY_RIGHT);
	setButton("forward1", OF_KEY_UP);
	setButton("backward1", OF_KEY_DOWN);
	setButton("fire1", OF_KEY_RIGHT_CONTROL);
    setButton("special1", OF_KEY_RIGHT_SHIFT);*/

    //DataManager::saveInputConfig(m_buttons, ".input");

    m_onMouseClickCallback = InputManager::onMouseClick;
    EventManager::onMousePressed += &m_onMouseClickCallback;

    m_onMouseMoveCallback = InputManager::onMouseMoved;
    EventManager::onMouseMove += &m_onMouseMoveCallback;

    m_onMouseReleasedCallback = InputManager::onMouseReleased;
    EventManager::onMouseReleased += &m_onMouseReleasedCallback;

}

void InputManager::update() {
	m_pressedKeys.clear();
	m_releasedKeys.clear();
}

void InputManager::setKeyPressed(int key) {
	m_pressedKeys.insert(key);
	m_downKeys.insert(key);
}

void InputManager::setKeyReleased(int key) {
	m_releasedKeys.insert(key);
	m_downKeys.erase(key);
}

bool InputManager::getKeyPressed(int key) {
	return m_pressedKeys.find(key) != m_pressedKeys.end();
}

bool InputManager::getKeyReleased(int key) {
	return m_releasedKeys.find(key) != m_releasedKeys.end();
}

bool InputManager::getKeyDown(int key) {
	return m_downKeys.find(key) != m_downKeys.end();
}

ofVec2f InputManager::getMousePosition() {
    return m_mousePosition;
}

void InputManager::setButtonMap(const std::map<std::string, int>& buttons) {
    m_buttons = buttons;
}

void InputManager::setButton(std::string name, int key) {	
	m_buttons[name] = key;
}

bool InputManager::getButtonPressed(const std::string& name) {
	return getKeyPressed(m_buttons[name]);
}

bool InputManager::getButtonDown(const std::string& name) {
	return getKeyDown(m_buttons[name]);
}

bool InputManager::getButtonReleased(const std::string& name) {
	return getKeyReleased(m_buttons[name]);
}

void InputManager::onMouseClick(int x, int y) {
    onMouseMoved(x, y);
}

void InputManager::onMouseReleased(int x, int y) {
    onMouseMoved(x, y);
}

void InputManager::onMouseMoved(int x, int y) {
    m_mousePosition.set(x, y);
}

