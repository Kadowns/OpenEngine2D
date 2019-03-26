#pragma once

class Timer {

public:
	static void update();

	static float time();
	static float deltaTime();


private:
	static float m_deltaTime;
	static float m_time;
};
