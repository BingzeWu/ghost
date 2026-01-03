#pragma once
#include <algorithm>
#include "core/scene.h"
#include "screen/ui_mouse.h"

class Spawner;
class Player; // 前向声明

class SceneMain : public Scene
{
    Player* player_ = nullptr; // 玩家对象
    Spawner* spawner_ = nullptr; // 敌人生成器
    UIMouse* ui_mouse_ = nullptr; // 鼠标UI对象

public:
    SceneMain() = default;
    ~SceneMain() override = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateCamera(float dt);
    float camera_zoom_ = 1.0f; // 相机缩放因子

};