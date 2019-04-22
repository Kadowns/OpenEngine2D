#pragma once

#include "../core/GameObject.h"
#include "../core/Renderable.h"
#include "../core/QuadTree.h"

class Collider;

class QuadTreeController : public GameObject, public Renderable {

public:

    QuadTreeController();
    virtual ~QuadTreeController();

private:

    void drawQuadTree(QuadTree<Collider>* qt);

    // Inherited via Renderable
    virtual ofVec2f position() const override;
    virtual void draw() override;

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;
};

