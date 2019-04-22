#pragma once

#include "../core/ScenePlayer.h"


class Scene : public ScenePlayer {

public:
    Scene();
    virtual ~Scene();

private:
    // Inherited via ScenePlayer
    virtual void onLoadScene() override;
};
