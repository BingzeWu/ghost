#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen
{
protected:
    Sprite* sprite_normal_ = nullptr;  // 正常状态下的精灵
    Sprite* sprite_hover_ = nullptr;   // 悬停状态下的精灵
    Sprite* sprite_press_ = nullptr;   // 按下状态下的精灵

    bool is_hover_ = false;  // 是否处于悬停状态
    bool is_press_ = false;  // 是否处于按下状态
    bool is_trigger_ = false;  // 是否触发了点击事件
public:
    // 创建按钮的静态工厂方法
    static HUDButton* addHUDButtonChild(
        Object* parent, glm::vec2 render_pos, 
        const std::string& file_path1, const std::string& file_path2, 
        const std::string& file_path3, float scale = 1.0f, 
        Anchor anchor = Anchor::CENTER
    );
    
    // 事件处理和更新方法
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    
    // 检查状态的方法
    void checkHover();
    void checkState();
    
    // 获取器和设置器
    Sprite* getSpriteNormal() const { return sprite_normal_; }
    Sprite* getSpriteHover() const { return sprite_hover_; }
    Sprite* getSpritePress() const { return sprite_press_; }
    bool getIsHover() const { return is_hover_; }
    bool getIsPress() const { return is_press_; }
    bool getIsTrigger();   // 只要触发一次，就会重置is_trigger_状态

    void setIsHover(bool is_hover) { is_hover_ = is_hover; }
    void setIsPress(bool is_press) { is_press_ = is_press; }
    void setIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
};


#endif // HUD_BUTTON_H