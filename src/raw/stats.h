#pragma once

#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor* parent_ = nullptr;
    float health_ = 100.0f;
    float max_health_ = 100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float damage_ = 40.0f;
    float mana_regen_ = 10.0f;

    float invincible_time_ = 1.5f;      // 受伤后，无敌时间有多长
    float invincible_timer_ = 0.0f;     // 无敌计时器
    bool is_alive_ = true;
    bool is_invincible_ = false;

public:
    static Stats* addStatsChild(Actor* parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
    virtual void update(float dt) override;

    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void regenMana(float dt);
    void takeDamage(float damage);

    // getters and setters
    float getHealth() const { return health_; }
    float getMaxHealth() const { return max_health_; }
    float getMana() const { return mana_; }
    float getMaxMana() const { return max_mana_; }
    float getDamage() const { return damage_; }
    float getManaRegen() const { return mana_regen_; }
    bool getIsAlive() const { return is_alive_; }
    bool getInvincible() const { return is_invincible_; }

};