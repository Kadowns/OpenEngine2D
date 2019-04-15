#pragma once

#include <vector>

#include "../core/GameObject.h"
#include "../core/Renderable.h"
#include "../core/EventManager.h"

class DebugSquare : public GameObject, public Renderable {

public:

	DebugSquare();
	~DebugSquare();

	void onRendererCreated(Renderable* renderer);
	void onRendererDestroyed(Renderable* renderer);
	void onMouseMove(int x, int y);


private:

	std::vector<Renderable*> m_renderers;
	Event<int, int>::EventListener m_onMouseMoveCallback;
	Event<Renderable*>::EventListener m_onRenderableCreatedCallback;
	Event<Renderable*>::EventListener m_onRenderableDestroyedCallback;

	ofVec2f m_mousePosition;
	ofRectangle m_rect;

	bool intersects(const ofVec2f& mouse, const ofRectangle& rect) const;

	// Inherited via Renderable
	virtual void draw() override;
	virtual ofVec2f position() const override;


	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;

};
