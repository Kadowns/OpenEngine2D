#include "GameObject.h"

void GameObject::setId(size_t id) {
    m_id = id;
}

size_t GameObject::getId() const {
    return m_id;
}

bool GameObject::operator==(GameObject& other) const {
	return m_id == other.m_id;
}

bool GameObject::operator<(GameObject & other) const {
	return m_id < other.m_id;
}
