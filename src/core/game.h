#pragma once
#include <string>
#include <random>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include "asset_store.h"

struct Texture;
class Scene; // 前向声明

class Game 
{
private:
    glm::vec2 screen_size_ = glm::vec2(0);
    bool is_running_ = true;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    // FPS tracking
    Uint64 FPS_ = 60;
    Uint64 frame_delay_ = 0;
    float dt_ = 0.0f;

    //资源管理器
    AssetStore* asset_store_ = nullptr;

    // mouse UI state
    glm::vec2 mouse_position_ = glm::vec2(0);
    SDL_MouseButtonFlags mouse_buttons_ = 0;

    // 文本引擎和相关标签
    TTF_TextEngine* ttf_engine_ = nullptr;
    int score_ = 0;
    int high_score_ = 0;

    // Private constructor for singleton pattern
    Game(){}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    std::mt19937 gen_ = std::mt19937(std::random_device{}()); // 随机数生成器

public:
    // Accessor for singleton instance
    static Game& GetInstance() 
    {
        static Game instance;
        return instance;
    }
    
    Scene* current_scene_ = nullptr;
    
    void init(std::string title, int width, int height);
    void run();
    void handleEvents();
    void update(float dt);
    void render();
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask = glm::vec2(1.0f)); // 渲染纹理
    void clean();
    void quit() { is_running_ = false; }

    //文字相关函数
    TTF_Text* createTTF_Text(const std::string& text, const std::string& font_path, int font_size = 16);
    
    // 得分函数
    void setScore(int score);
    int getScore() const { return score_; }
    void setHighScore(int high_score) { high_score_ = high_score; }
    int getHighScore() const { return high_score_; }
    void addScore(int score);

    //音频函数
    void playMusic(const std::string& music_path, bool loop = true) { Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0); } //-1代表无限循环
    void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0); }
    void stopMusic() { Mix_HaltMusic(); }
    void stopSound() { Mix_HaltChannel(-1); }       // 停止所有音效
    void pauseMusic() { Mix_PauseMusic(); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void resumeSound() { Mix_Resume(-1); }

    // 工具函数
    bool isMouseInRect(const glm::vec2& top_left, const glm::vec2& botton_right);

    
    // 随机数生成函数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); } // 生成[min, max]范围内的随机浮点数
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); } // 生成[min, max]范围内的随机整数
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); } // 生成[min, max]范围内的随机二维向量
    glm::ivec2 randomIVec2(const glm::ivec2& min, const glm::ivec2& max) { return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); } // 生成[min, max]范围内的随机二维整数向量
    
    // UI 渲染函数
    void renderHBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color); // 渲染水平进度条
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor); // 绘制网格
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor fcolor); // 绘制边界
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha); // 渲染填充圆

    // getters and setters
    glm::vec2 getScreenSize() const { return screen_size_; } // 获取屏幕尺寸
    Scene* getCurrentScene() const { return current_scene_; } // 获取当前场景
    AssetStore* getAssetStore() const { return asset_store_; } // 获取资源管理器
    SDL_Renderer* getRenderer() const { return renderer_; } // 获取渲染器
    glm::vec2 getMousePosition() const { return mouse_position_; }
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_buttons_; }

    
};

