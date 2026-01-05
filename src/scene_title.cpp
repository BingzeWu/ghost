#include "scene_title.h"
#include "screen/hud_text.h"
#include "scene_main.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    SDL_ShowCursor();
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
    // 创建致谢按钮
    button_credits_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() / 2.0f + glm::vec2(0, 200), 
        "assets/UI/A_Credits1.png", 
        "assets/UI/A_Credits2.png", 
        "assets/UI/A_Credits3.png", 
        2.0f);
    // 创建退出按钮
    button_quit_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() / 2.0f + glm::vec2(200, 200), 
        "assets/UI/A_Quit1.png",   // 正常状态
        "assets/UI/A_Quit2.png",   // 悬停状态
        "assets/UI/A_Quit3.png",   // 按下状态
        2.0f);
    // 加载并创建Credits文本
    auto text = game_.loadTextFile("assets/credits.txt");
    credits_text_ = HUDText::addHUDTextChild(this, text, 
        game_.getScreenSize() / 2.0f, glm::vec2(500, 500), 
        "assets/font/VonwaonBitmap-16px.ttf", 16);
    credits_text_->setBgSizeByText();  // 根据文本内容设置背景大小
    credits_text_->setActive(false);   // 初始时不显示
}

bool SceneTitle::handleEvents(SDL_Event &event)
{
    if (credits_text_->getActive()) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) { 
            credits_text_->setActive(false);  // 点击任意位置关闭Credits
            return true;
        }
    }
    if (Scene::handleEvents(event)) return true;  // 场景处理了事件
    return false;  // 事件未被处理
}

void SceneTitle::update(float dt)
{    
    color_timer_ += dt;
    updateColor();
    if (credits_text_->getActive()) {
        return;  // Credits显示时不更新其他内容
    }
    Scene::update(dt);
    checkButtonStart(); // 检查开始按钮
    checkButtonCredits(); // 检查致谢按钮
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

void SceneTitle::checkButtonCredits()
{
    if (button_credits_->getIsTrigger()){
        credits_text_->setActive(!credits_text_->getActive());  // 切换Credits文本的显示状态
    }
}
