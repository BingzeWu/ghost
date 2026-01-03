#pragma once

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Player : public Actor
{
protected:
    SpriteAnim* sprite_idle_ = nullptr;
    SpriteAnim* sprite_move_ = nullptr;
    bool is_moving_ = false;
    Effect* effect_ = nullptr;
    WeaponThunder* weapon_thunder_ = nullptr;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    void syncCamera();

private:
    void checkState();
    void changeState(bool is_moving);
    void checkIsDead();
    
};