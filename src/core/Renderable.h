#pragma once
#include "ofVec2f.h"

class Renderable {

protected:

    uint8_t m_layerOrder = 128;

public:

    uint8_t getLayer() const { return m_layerOrder; }
    void setLayer(uint8_t layer) { m_layerOrder = layer; }

	virtual ofVec2f position() const = 0;
    virtual void draw() = 0;

};
