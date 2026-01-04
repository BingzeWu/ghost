# 标题
cmake_minimum_required(VERSION 3.5.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})


# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm CONFIG REQUIRED)



# 添加可执行文件
add_executable(${TARGET} 
                src/main.cpp 
                src/scene_main.cpp 
                src/scene_title.cpp 
                src/player.cpp 
                src/enemy.cpp 
                src/spawner.cpp 
                src/weapon_thunder.cpp 
                src/core/actor.cpp 
                src/core/game.cpp 
                src/core/object.cpp 
                src/core/object_world.cpp 
                src/core/scene.cpp 
                src/core/asset_store.cpp 
                src/core/object_affiliate.cpp 
                src/affiliate/sprite.cpp 
                src/affiliate/sprite_anim.cpp 
                src/affiliate/collider.cpp 
                src/affiliate/affiliate_bar.cpp 
                src/affiliate/text_label.cpp 
                src/raw/stats.cpp  
                src/raw/weapon.cpp 
                src/world/effect.cpp 
                src/world/spell.cpp 
                src/screen/ui_mouse.cpp 
                src/screen/hud_stats.cpp 
                src/screen/hud_skill.cpp
                src/screen/hud_text.cpp 
)

# 链接库
target_link_libraries(${TARGET} 
                        SDL3::SDL3 
                        SDL3_image::SDL3_image 
                        SDL3_ttf::SDL3_ttf 
                        SDL3_mixer::SDL3_mixer 
                        glm::glm)   