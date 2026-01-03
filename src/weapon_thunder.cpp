#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"

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

void WeaponThunder::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (canAttack()) {
                auto pos = game_.getMousePosition() + game_.getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr, "assets/effect/Thunderstrike w blur.png", pos, 40.0f, 3.0f, Anchor::CENTER);
                attack(pos, spell);
            }
        }
    }
}
