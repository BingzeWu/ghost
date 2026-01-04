#pragma once

#include "player.h"

class Enemy : public Actor
{   
    // Enemy 状态枚举
    enum class State{
        NORMAL,
        HURT,
        DIE
    };
    State current_state_ = State::NORMAL;

    SpriteAnim* anim_normal_ = nullptr;
    SpriteAnim* anim_hurt_ = nullptr;
    SpriteAnim* anim_die_ = nullptr;

    SpriteAnim* current_anim_ = nullptr;
    
    Player* target_ = nullptr;

    int score_ = 10;


public:
    virtual void init();
    virtual void update(float dt) override;  

    static Enemy* addEnemyChild(Object* parent, glm::vec2 pos, Player* target); // 添加敌人子对象

    void checkState();
    void changeState(State new_state);
    void aim_target(Player* target); 
    void remove();// 标记为移除

    // getters and setters
    Player* get_target() { return target_; }
    void set_target(Player* target) { target_ = target; }
    void attack();
};