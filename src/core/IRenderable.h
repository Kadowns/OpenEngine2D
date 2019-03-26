#pragma once

class IRenderable {

protected:

    uint8_t m_layerOrder = 128;

public:

    uint8_t getLayer() const { return m_layerOrder; }
    void setLayer(uint8_t layer) { m_layerOrder = layer; }

    virtual void draw() = 0;

};
