#pragma once

#include <vector>

class IRenderable;
struct Camera;

class GameRenderer {

public:

    static void setup();
    static void draw();
    static void add(IRenderable* renderer);
    static void remove(IRenderable* renderer);

private:


    static Camera* m_camera;

    static void sortLayers();

    static std::vector<IRenderable*> m_renderers;

};
