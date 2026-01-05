#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"
#include "screen/hud_button.h"
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = {0.5, 0.5, 0.5, 1};
    float color_timer_ = 0;
    HUDButton* button_start_ = nullptr;    // 开始按钮（预留）
    HUDButton* button_credits_ = nullptr;  // 制作人员按钮（预留）
    HUDButton* button_quit_ = nullptr;     // 退出按钮
public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;
private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();  // 检查退出按钮是否被触发
    void checkButtonStart();
};


#endif // SCENE_TITLE_H