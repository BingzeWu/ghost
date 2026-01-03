#pragma once

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_  = glm::vec2(0, 0);// 世界位置
    Collider* collider_ = nullptr;

public:
    virtual void init() override {type_ = ObjectType::OBJECT_WORLD;}
    virtual void update(float dt) override;
    virtual void takeDamage(float damage) {return; }  // 默认实现为空

    
    // getters and setters
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position) override;
    Collider* getCollider() { return collider_; }
    void setCollider(Collider* collider) { collider_ = collider; }
};