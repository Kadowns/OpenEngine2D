#pragma once

#include <vector>

class Renderable;
struct Camera;

class GameRenderer {

public:

    static void setup();
	static void reset();
    static void draw();
    static void add(Renderable* renderer);
    static void remove(Renderable* renderer);

	template<typename T>
	static std::vector<T*> search();

private:


    static Camera* m_camera;

    static void sortLayers();

    static std::vector<Renderable*> m_renderers;

};

template<typename T>
inline std::vector<T*> GameRenderer::search() {
	std::vector<T*> found;
	for (auto& it : m_renderers) {
		auto t = dynamic_cast<T*>(it);
		if (t != nullptr) {
			found.push_back(t);
		}
	}
	return found;
}
