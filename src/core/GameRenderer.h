#pragma once

#include <vector>

class IRenderable;
struct Camera;

class GameRenderer {

public:

    static void setup();
    static void draw();
    static void add(IRenderable* renderer, bool overlay = false);
    static void remove(IRenderable* renderer, bool overlay = false);

	template<typename T>
	static std::vector<T*> search();

private:


    static Camera* m_camera;

    static void sortLayers();

    static std::vector<IRenderable*> m_renderers, m_overlay;

};

template<typename T>
inline std::vector<T*> GameRenderer::search() {
	std::vector<T*> found;
	for (auto& it : m_renderers) {
		auto isT = dynamic_cast<T*>(it);
		if (isT) {
			found.push_back(isT);
		}
	}
	return found;
}
