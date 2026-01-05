#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"

void WeaponThunder::init()
{
    Weapon::init();
    auto scene = game_.getCurrentScene();
    auto pos = glm::vec2(game_.getScreenSize().x - 300, 30);
    hud_skill_ = HUDSkill::addHUDSkillChild(scene, "assets/UI/Electric-Icon.png", pos, 0.14f, Anchor::CENTER);
}

void WeaponThunder::update(float dt)
{
    Weapon::update(dt);
    if (hud_skill_) hud_skill_->setPercentage(cool_down_timer_ / cool_down_);   // 应该是0～1的值
}

WeaponThunder *WeaponThunder::addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost)
{
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(cool_down);
    weapon->setManaCost(mana_cost);
    parent->addChild(weapon);
    return weapon;
}

bool WeaponThunder::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) { // 鼠标按下事件
        if (event.button.button == SDL_BUTTON_LEFT) { // 左键
            if (canAttack()) {
                game_.playSound("assets/sound/big-thunder.mp3");
                auto pos = game_.getMousePosition() + game_.getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr, "assets/effect/Thunderstrike w blur.png", pos, 40.0f, 3.0f, Anchor::CENTER);
                attack(pos, spell);
                return true;  // 技能施放事件被处理
            }
        }
    }
    return false;  // 其他事件未被处理
}
