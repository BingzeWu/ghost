#include "game.h"
#include "../scene_main.h"
#include "../scene_title.h"
#include "../affiliate/sprite.h"

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    // SDL3 initialization
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        return;
    }

    // SDL3_Mixer  initialization
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init Error: %s", SDL_GetError());
        return;
    }
    if (!Mix_OpenAudio(0, nullptr)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s", SDL_GetError());
    }
    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);

    // SDL3_TTF initialization
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s", SDL_GetError());
        return;
    }

    // Create window and renderer
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
        return;
    }

    // 初始化文本引擎
    ttf_engine_ = TTF_CreateRendererTextEngine(renderer_);

    // Additional initialization code can go here
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Initialize AssetStore
    asset_store_ = new AssetStore(renderer_);

    // Calculate frame delay based on FPS(ns)
    frame_delay_ = 1000000000 / FPS_;
    
    // Initialize the main scene
    //current_scene_ = new SceneMain(); // 默认进入主场景
    current_scene_ = new SceneTitle();
    SDL_Log("Game initialized with screen size (%d, %d)", width, height);
    current_scene_->init();
}

void Game::run()
{
    while (is_running_)
    {   
        auto start = SDL_GetTicksNS();
        handleEvents();
        update(dt_);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_) {
            SDL_DelayNS((frame_delay_ - elapsed));
            dt_ = static_cast<float>(frame_delay_) / 1.0e9;
        } else {
            dt_ = static_cast<float>(elapsed) / 1.0e9;
        }
        //SDL_Log("FPS: %f", 1.0f / dt_);
    }
    
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            current_scene_->handleEvents(event);
        }
    }
}

void Game::update(float dt)
{   
    mouse_buttons_ = SDL_GetMouseState(&mouse_position_.x, &mouse_position_.y);
    current_scene_->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    current_scene_->render();
    SDL_RenderPresent(renderer_);
}

void Game::renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask)
{
    SDL_FRect src_rect = {
        texture.src_rect.x,
        texture.src_rect.y + texture.src_rect.h * (1 - mask.y), // 从底部开始截取,符合技能栏冷却效果
        texture.src_rect.w * mask.x,
        texture.src_rect.h * mask.y
    };
    SDL_FRect dst_rect = {
        position.x,
        position.y + size.y * (1 - mask.y), // 从底部开始渲染
        size.x * mask.x,
        size.y * mask.y
    };
    SDL_RenderTextureRotated(renderer_, texture.texture, &src_rect, &dst_rect, texture.angle, nullptr, texture.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}


void Game::clean()
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
        current_scene_ = nullptr;
    }
    if (asset_store_)
    {
        asset_store_->clean();
        delete asset_store_;
        asset_store_ = nullptr;
    } 
    // 释放文本引擎
    if (ttf_engine_){
        TTF_DestroyRendererTextEngine(ttf_engine_);
    }
    // 释放渲染器和窗口
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

}

TTF_Text *Game::createTTF_Text(const std::string &text, const std::string &font_path, int font_size)
{
    auto font = asset_store_->getFont(font_path, font_size);
    return TTF_CreateText(ttf_engine_, font, text.c_str(), 0);
}

void Game::setScore(int score)
{
    score_ = score; 
    if (score_ > high_score_) {
        high_score_ = score_;
    }
}

void Game::addScore(int score)
{
    setScore(score_ + score);
}

void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width) {
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width) {
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 重置为默认颜色
}

void Game::drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor fcolor) // 绘制边框，利用同心矩形法
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < boundary_width; i++) {
        //SDL_FRect(x, y w, h)
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            (bottom_right.x - top_left.x) + 2 * i,
            (bottom_right.y - top_left.y) + 2 * i
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 重置为默认颜色
}

void Game::renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha)
{
    auto texture = asset_store_->getImage("assets/UI/circle.png");
    SDL_FRect dst_rect = {
        position.x, position.y, size.x, size.y
    };
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, NULL, &dst_rect);
}

bool Game::isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &botton_right)
{
    if (mouse_position_.x >= top_left.x && mouse_position_.x <= botton_right.x && 
        mouse_position_.y >= top_left.y && mouse_position_.y <= botton_right.y){
        return true;
    }
    return false;
}

void Game::renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    SDL_FRect boundary_rect = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    SDL_FRect fill_rect = {
        position.x,
        position.y,
        size.x * percent,
        size.y
    };
    SDL_RenderRect(renderer_, &boundary_rect);
    SDL_RenderFillRect(renderer_, &fill_rect);
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1); // 重置为默认颜色
}