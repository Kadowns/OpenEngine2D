#include "GameObject.h"

void GameObject::setId(size_t id) {
    m_id = id;
}

size_t GameObject::getId() const {
    return m_id;
}
