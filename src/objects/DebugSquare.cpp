#include "DebugSquare.h"

#include "../core/GameRenderer.h"

DebugSquare::DebugSquare() {
	m_renderers = GameRenderer::search<IRenderable>();
}

void DebugSquare::draw() {
	
}
