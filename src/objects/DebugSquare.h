#pragma once

#include <vector>

#include "../core/GameObject.h"
#include "../core/IRenderable.h"
#include "../core/EventManager.h"

class DebugSquare : public GameObject, public IRenderable {

public:

	DebugSquare();
	~DebugSquare();

	void onRendererCreated(IRenderable* renderer);
	void onRendererDestroyed(IRenderable* renderer);
	void onMouseMove(int x, int y);


private:

	std::vector<IRenderable*> m_renderers;
	Event<int, int>::EventListener m_onMouseMoveCallback;
	Event<IRenderable*>::EventListener m_onRenderableCreatedCallback;
	Event<IRenderable*>::EventListener m_onRenderableDestroyedCallback;

	ofVec2f m_mousePosition;
	ofRectangle m_rect;

	bool intersects(const ofVec2f& mouse, const ofRectangle& rect) const;

	// Inherited via IRenderable
	virtual void draw() override;
	virtual ofVec2f position() const override;


	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;

};
