#include "spawner.h"
#include "core/scene.h"
#include "world/effect.h"
#include "enemy.h"

void Spawner::update(float dt)
{
    if (!target_ || !target_->getActive()) return;
    timer_ += dt;
    if (timer_ >= interval_) {
        timer_ = 0;
        for (int i = 0; i < num_; ++i) {
            // 这里添加生成敌人的逻辑
            auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPosition(), game_.getCurrentScene()->getCameraPosition() + game_.getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}