#pragma once
#include "Transform2D.h"
#include "ScenePlayer.h"

class GameObject {
private:
    friend class ScenePlayer;
    void setId(size_t id);
    size_t m_id;

public:
	
    Transform2D transform;

    size_t getId() const;

	bool operator==(GameObject& other) const;
	bool operator<(GameObject& other) const;

	virtual void setup() = 0;
	virtual void update(float dt) = 0;

    virtual ~GameObject() = default;
};

