#pragma once
#include "../core/object_affiliate.h"

struct Texture
{
    SDL_Texture *texture = nullptr;
    SDL_FRect src_rect = {0, 0, 0, 0};
    float angle = 0;
    bool is_flip = false; // 是否水平翻转
    Texture() = default;
    Texture(const std::string& file_path); 
};

class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;
    bool is_finish_ = false; // 精灵动画是否播放完毕

public:
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);// 工厂方法，简化精灵的创建过程
    
    virtual void render() override;
    

    // getters and setters
    Texture getTexture() const { return texture_; }
    virtual void setTexture(const Texture &texture);
    bool getFinish() const { return is_finish_; }
    void setFinish(bool is_finish) { is_finish_ = is_finish; }
    void setFlip(bool is_flip) { texture_.is_flip = is_flip; }
    void setAngle(float angle) { texture_.angle = angle; }
    bool getFlip() const { return texture_.is_flip; }
    float getAngle() const { return texture_.angle; }

};