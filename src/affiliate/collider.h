#pragma once

#include "../core/object_affiliate.h"
class Spell; // 前向声明

class Collider : public ObjectAffiliate
{
protected:
    // 友元类
    friend Spell;
    
    enum class Type {
        RECT,
        CIRCLE
    };
    Type type_ = Type::CIRCLE;

public:
    virtual void render() override;
    
    static Collider* addColliderChild(ObjectScreen* parent, glm::vec2 size, Type type = Type::CIRCLE, Anchor anchor = Anchor::CENTER); // 静态工厂方法
    bool isColliding(Collider* other);

    // getters and setters
    Type type() const { return type_; }
    void setType(Type type) { type_ = type; }

};