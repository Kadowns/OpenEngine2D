#pragma once

#include <array>

#include "Renderable.h"
#include "GameObject.h"

template<typename T>
class QuadTree {

public:

    struct Point {

        Point(const ofVec2f& position, T* data) {
            this->position = position;
            this->data = data;
        }

        ofVec2f position;
        T* data;
    };

    QuadTree(const ofRectangle& boundary, uint8_t capacity) : m_boundary(boundary), m_capacity(capacity) {

    }

    ~QuadTree() {
        clear();
    }

    bool insert(const Point& point);

    void clear();

    void query(const ofRectangle& rect, std::vector<Point>& vec);

    ofRectangle& getBoundary();
    float getWidth();
    float getHeight();
    ofVec2f getPosition();

    bool isSubdivided();
    std::array<QuadTree<T>*, 4>& getSubdividions();

private:

    ofRectangle m_boundary;
    uint8_t m_capacity;
    bool m_subdivided = false;
    std::vector<Point> m_points;
    std::array<QuadTree<T>*, 4> m_subdivisions;

    void subdivide();

};


template<typename T>
inline bool QuadTree<T>::insert(const Point& point) {
    if (!m_boundary.inside(point.position)) {
        return false;
    }

    if (m_points.size() < m_capacity) {
        m_points.push_back(std::move(point));
    }
    else {

        if (!m_subdivided) {
            subdivide();
        }
        for (auto& it : m_subdivisions) {
            if (it->insert(point)) break;
        }
    }
    return true;
}

template<typename T>
inline void QuadTree<T>::query(const ofRectangle& rect, std::vector<Point>& vec) {
    if (!m_boundary.intersects(rect)) {
        return;
    }

    for (auto& p : m_points) {
        if (rect.inside(p.position)) {
            vec.push_back(p);
        }
    }

    if (m_subdivided) {
        for (auto& qt : m_subdivisions) {
            qt->query(rect, vec);
        }
    }
}

template<typename T>
inline ofRectangle& QuadTree<T>::getBoundary() {
    return m_boundary;
}

template<typename T>
inline float QuadTree<T>::getWidth() {
    return m_boundary.width;
}

template<typename T>
inline float QuadTree<T>::getHeight() {
    return m_boundary.height;
}

template<typename T>
inline ofVec2f QuadTree<T>::getPosition() {
    return m_boundary.position;
}

template<typename T>
inline bool QuadTree<T>::isSubdivided() {
    return m_subdivided;
}

template<typename T>
inline std::array<QuadTree<T>*, 4>& QuadTree<T>::getSubdividions() {
    return m_subdivisions;
}

template<typename T>
inline void QuadTree<T>::clear() {
    m_points.clear();
    if (m_subdivided) {
        for (auto& it : m_subdivisions) {
            delete it;
        }
    }
    m_subdivided = false;
}

template<typename T>
inline void QuadTree<T>::subdivide() {
    m_subdivisions[0] = new QuadTree<T>(
        ofRectangle(
            m_boundary.x,
            m_boundary.y,
            m_boundary.width / 2,
            m_boundary.height / 2
        ),
        m_capacity
        );
    m_subdivisions[1] = new QuadTree<T>(
        ofRectangle(
            m_boundary.x,
            m_boundary.y + m_boundary.height / 2,
            m_boundary.width / 2,
            m_boundary.height / 2
        ),
        m_capacity
        );
    m_subdivisions[2] = new QuadTree<T>(
        ofRectangle(
            m_boundary.x + m_boundary.width / 2,
            m_boundary.y,
            m_boundary.width / 2,
            m_boundary.height / 2
        ),
        m_capacity
        );
    m_subdivisions[3] = new QuadTree<T>(
        ofRectangle(
            m_boundary.x + m_boundary.width / 2,
            m_boundary.y + m_boundary.height / 2,
            m_boundary.width / 2,
            m_boundary.height / 2
        ),
        m_capacity
        );
    m_subdivided = true;
}