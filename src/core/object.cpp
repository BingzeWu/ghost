#include "object.h"

void Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        if(child->getActive()) {
            child->handleEvents(event);
        }
    }
}

void Object::update(float dt) {
    for (auto& child : object_to_add_) { // 添加安全添加的子对象
        addChild(child);
    }
    object_to_add_.clear();
    for (auto it = children_.begin(); it != children_.end();) { // 使用迭代器以便在循环中安全地移除元素
        auto child = *it;
        if (child->getNeedRemove()){
            it = children_.erase(it);
            child->clean();
            delete child; // 释放内存,防止内存泄漏！
            child = nullptr;  // 避免悬空指针
        } else {
            if(child->getActive()) {
                child->update(dt);
            }
            ++it;
        }
    }
}

void Object::render() {
    for (auto& child : children_) {
        if(child->getActive()) {
            child->render();
        }
    }
}

void Object::clean() {
    for (auto it = children_.begin(); it != children_.end();) {
        auto child = *it;
        if (child->getNeedRemove()){
            it = children_.erase(it);
            child->clean();
            delete child;
            child = nullptr;  // 避免悬空指针
    } 
        else {
            ++it;
            // ... 处理活跃对象
            }
        }
}