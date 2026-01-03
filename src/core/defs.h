#pragma once

// 启用调试模式
#define DEBUG_MODE 

enum class ObjectType
{
    NONE,
    OBJECT_SCREEN,
    OBJECT_WORLD,
    ENEMY,  // 新增的敌人类型
};

enum class Anchor
{
    NONE,
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};