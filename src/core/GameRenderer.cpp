#include "GameRenderer.h"

#include <algorithm>

#include "EventManager.h"
#include "IRenderable.h"
#include "Camera.h"

std::vector<IRenderable*> GameRenderer::m_renderers;
Camera* GameRenderer::m_camera;

void GameRenderer::setup() {
    m_camera = new Camera(ofVec2f(300, 500), 0, 1, 1024, 768);
}

void GameRenderer::draw() {	

    m_camera->bind();
    for (auto& it : m_renderers) {
        it->draw();
    }
    m_camera->unbind();
}

void GameRenderer::add(IRenderable* renderer) {
	m_renderers.push_back(renderer);
	sortLayers();
	EventManager::onRendarableCreated(renderer);
}

void GameRenderer::remove(IRenderable* renderer) {
	m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), renderer));
	sortLayers();
	EventManager::onRendarableDestroyed(renderer);
}

void GameRenderer::sortLayers() {
    std::sort(m_renderers.begin(), m_renderers.end(), [](const IRenderable* r1, const IRenderable* r2) {
        return r1->getLayer() > r2->getLayer();
    });
}
