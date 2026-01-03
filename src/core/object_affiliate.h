#pragma once

#include "object_screen.h"

class ObjectAffiliate : public Object 
{
protected:
    ObjectScreen *parent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点的偏移
    glm::vec2 size_ = glm::vec2(0, 0); // 大小
    Anchor anchor_ = Anchor::CENTER; // 默认使用中心点作为锚点

public:
    void setOffsetByAnchor(Anchor anchor);// 根据锚点设置偏移

    // getters and setters
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2 &size);
    void setScale(float scale); // 注意：此函数每次调用都会对当前大小进行倍乘，不适于每帧调用
    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }
};