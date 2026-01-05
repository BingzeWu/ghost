#pragma once
#include "game.h"
#include "defs.h"

class Object 
{
protected:
    Game& game_ = Game::GetInstance();
    ObjectType type_ = ObjectType::NONE;
    std::vector<Object*> children_; // 子对象列表
    std::vector<Object*> object_to_add_;
    bool is_active_ = true;// 对象是否激活
    bool need_remove_ = false; // 标记对象是否需要被移除
    

public:
    Object() = default;
    virtual ~Object() = default; // Object 类不需要特殊的构造和析构逻辑

    virtual void init() {}
    virtual void update(float dt);
    virtual bool handleEvents(SDL_Event& event);
    virtual void render();
    virtual void clean();

    // 子对象管理
    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void safeAddChild(Object* child) {
        object_to_add_.push_back(child);
    }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }

    // 对象是否激活
    void setActive(bool active) { is_active_ = active; }
    bool getActive() const { return is_active_; }

    // getters and setters
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    bool getNeedRemove() const { return need_remove_; }
    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }

};
