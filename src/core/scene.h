#pragma once
#include "object.h"
#include "object_world.h"
#include "object_screen.h"

#include <glm/glm.hpp>
#include <vector>


class Scene: public Object
{
protected:
    glm::vec2 camera_position_ = glm::vec2(0);
    std::vector<Object*> objects_;
    glm::vec2 world_size_ = glm::vec2(0); // 世界大小
    // 场景对象容器
    std::vector<ObjectWorld*> children_world_;
    std::vector<ObjectScreen*> children_screen_;
    bool is_pause_ = false;  // 暂停状态标志


public:
    Scene() = default; 
    ~Scene() override = default;

    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render();
    virtual void clean() override;

    void pause();   // 暂停场景
    void resume();  // 恢复场景

    // 坐标转换
    glm::vec2 worldToScreen(const glm::vec2 &world_position)
    const{
        return world_position - camera_position_;
    }
    glm::vec2 screenToWorld(const glm::vec2 &screen_position)
    const{
        return screen_position + camera_position_;
    }

    virtual void addChild(Object* child) override;
    virtual void removeChild(Object* child) override;  // 只是把容器中的元素移除容器，并没有delete该对象

    // getters and setters
    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2 &camera_position);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2 &world_size) { world_size_ = world_size; }
    std::vector<ObjectWorld*>& getChildrenWorld() { return children_world_; } // 获取世界对象列表
    std::vector<ObjectScreen*>& getChildrenScreen() { return children_screen_; } // 获取屏幕对象列表


};
