#pragma once
#include "Transform2D.h"
#include "GameManager.h"

class GameObject {
private:
    friend class GameManager;
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

