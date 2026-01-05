#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite.h"
#include "affiliate/sprite_anim.h"
#include "raw/stats.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;
    sprite_idle_ =SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize()/ 1.5f); // 添加碰撞体，作为组件在玩家对象中管理
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/1764.png", glm::vec2(0), 2.0f); // 预加载死亡特效,但不激活
    effect_->setActive(false);
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f, 40.0f);
}

bool Player::handleEvents(SDL_Event& event)
{
    if (Actor::handleEvents(event)) return true;
    return false;
}

void Player::update(float dt)
{
    Actor::update(dt);  // 调用父类的update
    keyboardControl();
    velocity_ *= 0.9f; // 简单的阻力效果
    checkState();
    move(dt);
    syncCamera();
    checkIsDead();
}

void Player::render()
{
    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::takeDamage(float damage)
{    
    if (!stats_ || stats_->getInvincible()) return;
    Actor::takeDamage(damage);
    game_.playSound("assets/sound/hit-flesh-02-266309.mp3");  // 播放受伤音效
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W]){
        velocity_.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S]){
        velocity_.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A]){
        velocity_.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D]){
        velocity_.x = max_speed_;
    }
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
}

void Player::checkState() //检查玩家的移动状态，并根据移动方向设置精灵的翻转
{
    if (velocity_.x < 0){
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }else{
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }
    
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_){
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}
void Player::changeState(bool is_moving)
{
    if (is_moving){
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
        
    }else{
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsDead()
{
    if (!stats_->getIsAlive()){
        effect_->setActive(true);// 激活死亡特效
        effect_->setPosition(getPosition());
        setActive(false);
        game_.playSound("assets/sound/female-scream-02-89290.mp3");  // 播放死亡音效
    }
}
