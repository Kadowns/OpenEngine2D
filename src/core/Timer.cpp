#include "Timer.h"
#include "ofMain.h"

float Timer::m_deltaTime;
float Timer::m_time;

void Timer::update() {
	m_deltaTime = ofGetLastFrameTime();
	m_time += m_deltaTime;
}

float Timer::time() {
	return m_time;
}

float Timer::deltaTime() {
	return m_deltaTime;
}
