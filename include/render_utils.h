#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class RenderUtils
{
public:
    static RenderUtils &getInstance();
    static bool init(SDL_Renderer *renderer);

    void clearScreen();
    void renderPresent();
    SDL_Texture *initTexture(const std::string path);
    TTF_Font *initFont(const std::string path, int fontSize);
    SDL_Texture *initTextTexture(TTF_Font *font, const std::string text, SDL_Color color);
    void setRenderColor(const SDL_Color &color);
    void renderCircle(int cx, int cy, int radius);
    void renderFilledCircle(int cx, int cy, int radius);
    void renderRect(SDL_FRect &rect);
    void renderFilledRect(SDL_FRect &rect);
    void renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect);
    void renderTextureFliped(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect);

private:
    RenderUtils() = default;
    ~RenderUtils();
    RenderUtils(const RenderUtils &) = delete;
    RenderUtils &operator=(const RenderUtils &) = delete;

    SDL_Renderer *renderer = nullptr;
};