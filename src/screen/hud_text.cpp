#include "hud_text.h"
#

HUDText *HUDText::addHUDTextChild(Object *parent, const std::string &text, glm::vec2 render_pos, glm::vec2 size, const std::string &font_path, int font_size, const std::string &bg_path, Anchor anchor)
{
    auto hud_text = new HUDText();
    hud_text->init();
    hud_text->setRenderPosition(render_pos);

    // 创建背景精灵
    hud_text->setSpriteBg(Sprite::addSpriteChild(hud_text, bg_path, 1, anchor));
    hud_text->setSize(size);

    // 创建文本标签
    hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text, text, font_path, font_size, anchor));

    // 将 HUDText 添加为父对象的子对象
    if (parent) {
        parent->addChild(hud_text);
    }
    return hud_text;
}

void HUDText::setBgSizeByText(float margin)
{
    if (text_label_) {
        glm::vec2 text_size = text_label_->getSize();
        setSize(glm::vec2(text_size.x + margin, text_size.y + margin));
    }
}

void HUDText::setSize(const glm::vec2 &size)
{
    size_ = size;
    sprite_bg_->setSize(size);
}

void HUDText::setBackgroud(const std::string &file_path)
{
    if (sprite_bg_) sprite_bg_->setTexture(file_path);
    else sprite_bg_ = Sprite::addSpriteChild(this, file_path, 1, Anchor::CENTER);
}
