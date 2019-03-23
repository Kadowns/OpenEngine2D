#pragma once

#include <set>
#include <map>

#include "ofVectorMath.h"

#include "EventManager.h"

class InputManager {
public:	

	static void load();

	static void update();

	static void setKeyPressed(int key);
	static void setKeyReleased(int key);

	static bool getKeyPressed(int key);
	static bool getKeyReleased(int key);
	static bool getKeyDown(int key);
    static ofVec2f getMousePosition();

	static void setButton(std::string name, int key);
	
	static bool getButtonPressed(const std::string& name);
	static bool getButtonDown(const std::string& name);
	static bool getButtonReleased(const std::string& name);

private:

    static void onMouseClick(int x, int y);
    static void onMouseReleased(int x, int y);
    static void onMouseMoved(int x, int y);

    static Event<int, int>::EventListener m_onMouseMoveCallback;
    static Event<int, int>::EventListener m_onMouseClickCallback;
    static Event<int, int>::EventListener m_onMouseReleasedCallback;

    static ofVec2f m_mousePosition;

	static std::set<int> m_pressedKeys, m_downKeys, m_releasedKeys;
	static std::map<std::string, int> m_buttons;

};

