#include "GameRenderer.h"

#include <algorithm>

#include "EventManager.h"
#include "Renderable.h"
#include "Camera.h"

std::vector<Renderable*> GameRenderer::m_renderers;
Camera* GameRenderer::m_camera;

void GameRenderer::setup() {
    m_camera = new Camera(ofVec2f(300, 500), 0, 1, 1024, 768);
}

void GameRenderer::reset() {
	delete m_camera;
	setup();
}

void GameRenderer::draw() {	

    m_camera->bind();
    for (auto& it : m_renderers) {
        it->draw();
    }
    m_camera->unbind();
}

void GameRenderer::add(Renderable* renderer) {
	m_renderers.push_back(renderer);
	sortLayers();
	EventManager::onRenderableCreated(renderer);
}

void GameRenderer::remove(Renderable* renderer) {
	m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), renderer));
	sortLayers();
	EventManager::onRenderableDestroyed(renderer);
}

void GameRenderer::sortLayers() {
    std::sort(m_renderers.begin(), m_renderers.end(), [](const Renderable* r1, const Renderable* r2) {
        return r1->getLayer() > r2->getLayer();
    });
}
