#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"
#include "screen/hud_button.h"
class HUDText;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = {0.5, 0.5, 0.5, 1};
    float color_timer_ = 0;
    HUDButton* button_start_ = nullptr;    // 开始按钮
    HUDButton* button_credits_ = nullptr;  // 致谢按钮
    HUDButton* button_quit_ = nullptr;     // 退出按钮
    HUDText* credits_text_ = nullptr;  // Credits文本HUD
public:
    void init() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;
private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();  // 检查退出按钮是否被触发
    void checkButtonStart();
    void checkButtonCredits();
};


#endif // SCENE_TITLE_H