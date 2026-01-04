#include "enemy.h"
#include "raw/stats.h"
#include "affiliate/affiliate_bar.h"


void Enemy::init()
{
    Actor::init();
    anim_normal_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    anim_die_->setLoop(false);

    current_anim_ = anim_normal_;
    collider_ = Collider::addColliderChild(this, current_anim_->getSize());
    stats_ = Stats::addStatsChild(this);

    // 生命条挂载
    auto size = anim_normal_->getSize();
    health_bar_ = AffiliateBar::addAffiliateBarChild(this, glm::vec2(size.x - 10, 10), Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(0, size.y/2.0f - 5.0f));

    setType(ObjectType::ENEMY); 
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (target_->getActive()) {
        aim_target(target_);
        move(dt);
        attack();
    }
    checkState();
    remove(); 
}

Enemy *Enemy::addEnemyChild(Object *parent, glm::vec2 pos, Player *target)
{
    Enemy* enemy = new Enemy();
    enemy->init();
    enemy->setPosition(pos);
    enemy->set_target(target);
    if (parent) {
        parent->addChild(enemy);
    }
    return enemy;
}

void Enemy::checkState()
{ 
    State new_state; 
    if (stats_->getHealth() <= 0) new_state = State::DIE;
    else if (stats_->getInvincible()) new_state = State::HURT;
    else new_state = State::NORMAL;

    if (new_state != current_state_) changeState(new_state);
}

void Enemy::changeState(State new_state)
{
    if (new_state == current_state_) return;
    current_anim_->setActive(false);
    switch (new_state) {
    case State::NORMAL:
        current_anim_ = anim_normal_;
        current_anim_->setActive(true);
        break;
    case State::HURT:
        current_anim_ = anim_hurt_;
        current_anim_->setActive(true);
        break;
    case State::DIE:
        current_anim_ = anim_die_;
        current_anim_->setActive(true);
        game_.addScore(score_);  // 敌人死亡时增加得分
        break;
    }
    current_state_ = new_state;
}

void Enemy::aim_target(Player *target)
{
    if (target == nullptr) return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::remove() // 如果死亡动画播放完毕，则标记为移除
{
    if (anim_die_->getFinish()) {
        setNeedRemove(true);
    }
}

void Enemy::attack()
{
    if (!collider_ || target_->getCollider() == nullptr) return;
    if (collider_->isColliding(target_->getCollider())) {
        // 检测到碰撞，进行攻击
        if (stats_ && target_->getStats()) {
            target_->takeDamage(stats_->getDamage());
        }
    }
}
