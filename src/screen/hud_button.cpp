#include "hud_button.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, glm::vec2 render_pos, const std::string &file_path1, const std::string &file_path2, const std::string &file_path3, float scale, Anchor anchor)
{
    auto hud_button = new HUDButton();
    hud_button->init();
    hud_button->setRenderPosition(render_pos);
    
    // 创建三种状态的精灵
    hud_button->sprite_normal_ = Sprite::addSpriteChild(hud_button, file_path1, scale, anchor);
    hud_button->sprite_hover_ = Sprite::addSpriteChild(hud_button, file_path2, scale, anchor);
    hud_button->sprite_press_ = Sprite::addSpriteChild(hud_button, file_path3, scale, anchor);
    
    // 初始时只有正常状态的精灵是活跃的
    hud_button->sprite_hover_->setActive(false);
    hud_button->sprite_press_->setActive(false);
    
    if (parent) parent->addChild(hud_button);
    return hud_button;
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (is_hover_){  // 只有当鼠标悬停在按钮上时，才会响应按下事件
                is_press_ = true;
                game_.playSound("assets/sound/UI_button08.wav");  // 播放按下音效
                return true;
            }
        }
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            is_press_ = false;
            if (is_hover_){  // 只有当鼠标悬停在按钮上放开时，才视为触发按钮
                is_trigger_ = true;
                return true;
            }
        }
    }
    return false;
}

void HUDButton::update(float dt)
{
    checkHover(); // 检查鼠标是否悬停
    checkState(); // 根据状态更新精灵显示
}

void HUDButton::checkHover()
{
    bool new_hover_;
    auto pos = render_position_ + sprite_normal_->getOffset();
    auto size = sprite_normal_->getSize();
    
    // 检查鼠标是否在按钮区域内
    if (game_.isMouseInRect(pos, pos + size)){
        new_hover_ = true;
    } else {
        new_hover_ = false;
    }
    
    // 如果悬停状态发生变化，更新状态并播放音效
    if (new_hover_ != is_hover_){
        is_hover_ = new_hover_;
        if (is_hover_ && !is_press_) 
            game_.playSound("assets/sound/UI_button12.wav");  // 播放悬停音效
    }
}

void HUDButton::checkState()
{
    if (!is_press_ && !is_hover_){
        // 正常状态：显示正常精灵
        sprite_normal_->setActive(true);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(false);
    }else if (!is_press_ && is_hover_){
        // 悬停状态：显示悬停精灵
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(true);
        sprite_press_->setActive(false);
    }else {
        // 按下状态：显示按下精灵
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(true);
    }
}

bool HUDButton::getIsTrigger()
{
    if (is_trigger_){
        is_trigger_ = false;  // 读取后自动重置
        is_press_ = false;  // 点击后重置按下状态
        is_hover_ = false;  // 点击后重置悬停状态
        is_trigger_ = false;
        return true;
    }
    return false;
}
