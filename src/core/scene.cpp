#include "scene.h"

void Scene::handleEvents(SDL_Event &event)
{
    Object::handleEvents(event);
    for (auto &child : children_screen_)
    {   if (child->getActive())
        {
            child->handleEvents(event);
        }
    }
    
    for (auto &child : children_world_)
    {   if (child->getActive())
        {
            child->handleEvents(event);
        }
    }
}

void Scene::update(float dt)
{
    Object::update(dt);
    for (auto it = children_world_.begin(); it != children_world_.end();){
        auto child = *it;
        if (child->getNeedRemove()){
            it = children_world_.erase(it);
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
    for (auto it = children_screen_.begin(); it != children_screen_.end(); )
    {   auto &child = *it;
        if (child->getNeedRemove()){
            it = children_screen_.erase(it);
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


void Scene::render()
{
    Object::render();
    for (auto &child : children_world_)
    {   if (child->getActive())
        {
            child->render();
        }
    }
    for (auto &child : children_screen_)
    {   if (child->getActive())
        {
            child->render();
        }
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto &child : children_world_)
    {
        child->clean();
    }
    children_world_.clear();
    for (auto &child : children_screen_)
    {
        child->clean();
    }
    children_screen_.clear();
}


void Scene::setCameraPosition(const glm::vec2 &camera_position)
{
    camera_position_ = camera_position;
    camera_position_ = glm::clamp(camera_position_, glm::vec2(-30), world_size_ - game_.getScreenSize() + glm::vec2(30));
}


void Scene::addChild(Object *child)
{
    switch (child->getType())
    {   
        case ObjectType::OBJECT_WORLD: 
        case ObjectType::ENEMY:
            children_world_.push_back(dynamic_cast<ObjectWorld *>(child));
            break;
        case ObjectType::OBJECT_SCREEN:
            children_screen_.push_back(dynamic_cast<ObjectScreen *>(child));
            break;
        default:
            children_.push_back(child);
            break;
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {   
        case ObjectType::OBJECT_WORLD:
        case ObjectType::ENEMY:
            children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), dynamic_cast<ObjectWorld *>(child)), children_world_.end());
            break;
        case ObjectType::OBJECT_SCREEN:
            children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), dynamic_cast<ObjectScreen *>(child)), children_screen_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
            break;
    }
}