#ifndef HUD_SKILL_H
#define HUD_SKILL_H

#include "../core/object_screen.h"

class Sprite;
class HUDSkill : public ObjectScreen
{
protected:
    Sprite* icon_ = nullptr;
    float percentage_ = 1.0f;
public:
    static HUDSkill* addHUDSkillChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
    // setters and getters
    float getPercentage() const { return percentage_; }
    void setPercentage(float percentage);
    Sprite* getIcon() const { return icon_; }
    void setIcon(Sprite* icon) { icon_ = icon; }
};


#endif // HUD_SKILL_H