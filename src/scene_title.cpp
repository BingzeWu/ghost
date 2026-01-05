#include "scene_title.h"
#include "screen/hud_text.h"
#include "scene_main.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    auto size = glm::vec2(game_.getScreenSize().x/2.0f, game_.getScreenSize().y/3.0f);
    HUDText::addHUDTextChild(this, "幽 灵 逃 生", game_.getScreenSize() / 2.0f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    auto score_text = "最高分: " + std::to_string(game_.getHighScore());
    HUDText::addHUDTextChild(this, score_text, game_.getScreenSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);
    // 创建开始按钮
    button_start_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() / 2.0f + glm::vec2(-200, 200), 
        "assets/UI/A_Start1.png",   // 正常状态
        "assets/UI/A_Start2.png",   // 悬停状态
        "assets/UI/A_Start3.png",   // 按下状态
        2.0f);                     // 缩放倍数
    // 创建退出按钮
    button_quit_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() / 2.0f + glm::vec2(200, 200), 
        "assets/UI/A_Quit1.png",   // 正常状态
        "assets/UI/A_Quit2.png",   // 悬停状态
        "assets/UI/A_Quit3.png",   // 按下状态
        2.0f);         
}

void SceneTitle::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
}

void SceneTitle::update(float dt)
{
    Scene::update(dt);
    color_timer_ += dt;
    updateColor();
    checkButtonStart(); // 检查开始按钮
    checkButtonQuit();  // 检查退出按钮
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::renderBackground()
{
    game_.drawBoundary(glm::vec2(30.0f), game_.getScreenSize() - glm::vec2(30.0f), 10.0f, boundary_color_);
}
void SceneTitle::updateColor()
{
    boundary_color_.r = 0.5f + 0.5f * sinf(color_timer_ * 1.2f);
    boundary_color_.g = 0.5f + 0.5f * sinf(color_timer_ * 1.1f);
    boundary_color_.b = 0.5f + 0.5f * sinf(color_timer_ * 1.0f);
}

void SceneTitle::checkButtonQuit()
{
    if (button_quit_->getIsTrigger()){
        game_.quit();  // 如果退出按钮被触发，退出游戏
    }
}

void SceneTitle::checkButtonStart()
{
    if (button_start_->getIsTrigger()){
        game_.safeChangeScene(new SceneMain());  // 切换到主游戏场景
    }
}
