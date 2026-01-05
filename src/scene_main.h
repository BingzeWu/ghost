#pragma once
#include <algorithm>
#include "core/scene.h"
#include "screen/ui_mouse.h"

 // 前向声明
class Spawner;
class Player;
class HUDStats;
class HUDText;
class HUDButton;

class SceneMain : public Scene
{
    Player* player_ = nullptr; // 玩家对象
    Spawner* spawner_ = nullptr; // 敌人生成器
    UIMouse* ui_mouse_ = nullptr; // 鼠标UI对象
    HUDStats* hud_stats_ = nullptr; // 统计信息HUD
    HUDText* hud_text_score_ = nullptr; // 分数显示HUD
    HUDButton* button_pause_ = nullptr;
    HUDButton* button_restart_ = nullptr;
    HUDButton* button_back_ = nullptr;

public:
    SceneMain() = default;
    ~SceneMain() override = default;

    virtual void init() override;  
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateCamera(float dt);
    float camera_zoom_ = 1.0f; // 相机缩放因子
    void updateScore();
    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();

};