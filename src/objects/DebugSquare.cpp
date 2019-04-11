#include "DebugSquare.h"

#include "ofGraphics.h"

#include "../core/Camera.h"
#include "../core/GameRenderer.h"

DebugSquare::DebugSquare() {

	m_layerOrder = 0;
	GameRenderer::add(this);

	m_renderers = GameRenderer::search<IRenderable>();

	//callback de criação
	m_onRenderableCreatedCallback = [this](IRenderable* renderer) {
		this->onRendererCreated(renderer);
	};
	EventManager::onRendarableCreated += &m_onRenderableCreatedCallback;


	//callback de destruição
	m_onRenderableDestroyedCallback = [this](IRenderable* renderer) {
		this->onRendererDestroyed(renderer);
	};
	EventManager::onRendarableDestroyed += &m_onRenderableDestroyedCallback;

	m_onMouseMoveCallback = [this](int x, int y) {
		this->onMouseMove(x, y);
	};
	EventManager::onMouseMove += &m_onMouseMoveCallback;
}

DebugSquare::~DebugSquare() {
	EventManager::onRendarableCreated -= &m_onRenderableCreatedCallback;
	EventManager::onRendarableDestroyed -= &m_onRenderableDestroyedCallback;
	EventManager::onMouseMove -= &m_onMouseMoveCallback;
	GameRenderer::remove(this);
}

void DebugSquare::onRendererCreated(IRenderable* renderer) {
	m_renderers.push_back(renderer);
}

void DebugSquare::onRendererDestroyed(IRenderable* renderer) {
	m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), renderer));
}

void DebugSquare::onMouseMove(int x, int y) {
	m_mousePosition.set(Camera::mainCamera().screenToWorld(ofVec2f(x, y)));
}

void DebugSquare::setup() {
	
}

void DebugSquare::update(float dt) {

}

bool DebugSquare::intersects(const ofVec2f& mouse, const ofRectangle& rect) const {
	if (rect.getBottom() < mouse.y || rect.getTop() > mouse.y) {
		return false;
	}
	if (rect.getRight() < mouse.x || rect.getLeft() > mouse.x) {
		return false;
	}
	return true;
}

void DebugSquare::draw() {
	for (auto& it : m_renderers) {
		m_rect.setFromCenter(it->position(), 50, 50);
		if (intersects(m_mousePosition, m_rect)) {
			ofDrawRectangle(m_rect);
		}
	}
}

ofVec2f DebugSquare::position() const {
	return ofVec2f();
}


