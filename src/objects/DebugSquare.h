#pragma once

#include <vector>

#include "../core/IRenderable.h"

class DebugSquare : public IRenderable {
public:
	DebugSquare();

private:

	std::vector<IRenderable*> m_renderers;
	// Inherited via IRenderable
	virtual void draw() override;

};
