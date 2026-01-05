#include "scene_main.h"
#include "scene_title.h"
#include "player.h"
#include "enemy.h"
#include "spawner.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"

void SceneMain::init()
{
    // 初始化场景中的对象和资源
    
    Scene::init();
    SDL_HideCursor(); // 隐藏系统默认光标
    game_.playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = glm::vec2(1600.0f, 1200.0f);
    camera_position_ = world_size_ / 2.0f - game_.getScreenSize() / 2.0f;
    
    // 创建并初始化玩家对象
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f); // 将玩家放置在世界中心
    addChild(player_);

    // 创建并初始化生成器对象
    //spawner_ = new Spawner();
    //spawner_->init();
    //spawner_->setTarget(player_);
    //addChild(spawner_);

    // 测试用只生成一个敌人
    auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPosition(), game_.getCurrentScene()->getCameraPosition() + game_.getScreenSize());
    Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, player_);
    Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
    game_.playSound("assets/sound/silly-ghost-sound-242342.mp3");  // 播放敌人生成音效

    // 创建并初始化鼠标UI对象
    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, Anchor::CENTER);
    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreenSize().x - 120.f, 30.f), glm::vec2(200, 50));
    
    // 添加控制按钮
    button_pause_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() - glm::vec2(230.f, 30.f),
        "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() - glm::vec2(140.f, 30.f), 
        "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this, 
        game_.getScreenSize() - glm::vec2(50.f, 30.f), 
        "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    SDL_Log("SceneMain initialized.");

}

bool SceneMain::handleEvents(SDL_Event& event)
{
    if (Scene::handleEvents(event)) return true;  // 场景处理了事件
    return false;  // 事件未被处理
}

void SceneMain::renderBackground()
{

    // 计算缩放后的坐标...
    auto start = -camera_position_ * camera_zoom_;
    auto end = (world_size_ - camera_position_) * camera_zoom_;
    
    // 渲染背景网格和边界
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, {1.0, 1.0, 1.0, 1.0});
}


void SceneMain::updateCamera(float dt)
{   
    // 更新摄像机
    camera_position_ -= glm::vec2(100.0f, 100.0f) * dt; // 简单地让摄像机向右下移动


    // 边界检查
    camera_position_.x = std::clamp(camera_position_.x, 0.0f, world_size_.x - game_.getScreenSize().x);
    camera_position_.y = std::clamp(camera_position_.y, 0.0f, world_size_.y - game_.getScreenSize().y);
}

void SceneMain::updateScore()
{
    if (hud_text_score_) {
        hud_text_score_->getTextLabel()->setText("Score: " + std::to_string(game_.getScore()));
    }
}

void SceneMain::checkButtonPause()
{
    if (!button_pause_->getIsTrigger()) return;
    if (is_pause_) resume();  // 如果当前是暂停状态，则恢复
    else pause();            // 否则暂停
}

void SceneMain::checkButtonRestart()
{
    if (!button_restart_->getIsTrigger()) return;
    auto scene = new SceneMain();
    game_.safeChangeScene(scene);  // 使用安全切换方法创建新场景
}

void SceneMain::checkButtonBack()
{
    if (!button_back_->getIsTrigger()) return;
    auto scene = new SceneTitle();
    game_.safeChangeScene(scene);  // 切换回标题场景
}

void SceneMain::update(float dt)
{   
    Scene::update(dt);  // 调用父类的update，它会自动处理所有子对象
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
}



void SceneMain::render()
{   
    renderBackground();
    Scene::render();  // 调用父类的render，它会自动处理所有子对象
}

void SceneMain::clean()
{
    Scene::clean();
}
