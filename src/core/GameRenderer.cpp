#include "GameRenderer.h"
#include <algorithm>

#include "IRenderable.h"
#include "Camera.h"

std::vector<IRenderable*> GameRenderer::m_renderers;
std::vector<IRenderable*> GameRenderer::m_overlay;
Camera* GameRenderer::m_camera;

void GameRenderer::setup() {
    m_camera = new Camera(ofVec2f(300, 500), 0, 1, 1024, 768);
}

void GameRenderer::draw() {	

    for (auto& it : m_overlay) {
        it->draw();
    }
    m_camera->bind();
    for (auto& it : m_renderers) {
        it->draw();
    }
    m_camera->unbind();
}

void GameRenderer::add(IRenderable* renderer, bool overlay) {
    if (overlay) {
        m_overlay.push_back(renderer);
    }
    else {
        m_renderers.push_back(renderer);
    }    
    sortLayers();
}

void GameRenderer::remove(IRenderable* renderer, bool overlay) {
    if (overlay) {
        m_overlay.erase(std::remove(m_overlay.begin(), m_overlay.end(), renderer));
    }
    else {
        m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), renderer));
    }
    sortLayers();
}

void GameRenderer::sortLayers() {
    std::sort(m_renderers.begin(), m_renderers.end(), [](const IRenderable* r1, const IRenderable* r2) {
        return r1->getLayer() > r2->getLayer();
    });
}
