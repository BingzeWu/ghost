#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::takeDamage(float damage)
{
    if (!stats_) return;
    stats_->takeDamage(damage);
}

void Actor::update(float dt)
{   
    ObjectWorld::update(dt);
    updateHealthBar();
}

bool Actor::isAlive() const
{
    if (!stats_) return true;
    return stats_->getIsAlive();
}

void Actor::updateHealthBar()
{
    if (!stats_ || !health_bar_) return;
    health_bar_->setPercentage(stats_->getHealth() / stats_->getMaxHealth()); // 更新生命条百分比
}

void Actor::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}