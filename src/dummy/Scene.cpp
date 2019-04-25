#include "Scene.h"

#include "Ship.h"
#include "Asteroid.h"
#include "AsteroidManager.h"
#include "CameraController.h"
#include "StarBackground.h"
#include "DebugSquare.h"
#include "QuadTreeController.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::onLoadScene() {
    add(new Ship(0, ofVec2f(400, 400), TEAM_RED));
    //add(new Ship(1, ofVec2f(600, 500), TEAM_BLUE));
    add(new CameraController());
    add(new StarBackground(200));
    add(new DebugSquare());
    add(new AsteroidManager(2));
    add(new QuadTreeController());
}
