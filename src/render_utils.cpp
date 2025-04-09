#include "render_utils.h"

#include <SDL3_image/SDL_image.h>

RenderUtils &RenderUtils::getInstance()
{
    static RenderUtils instance; // Thread-safe in C++11 and later
    return instance;
}

bool RenderUtils::init(SDL_Renderer *renderer)
{
    RenderUtils &instance = getInstance();

    if (renderer == nullptr)
    {
        SDL_Log("Renderer is null");
        return false;
    }
    if (instance.renderer != nullptr)
    {
        SDL_Log("Renderer already initialized");
        return false;
    }
    instance.renderer = renderer;

    if (!TTF_Init())
    {
        SDL_Log("TTF initialization failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

void RenderUtils::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void RenderUtils::renderPresent()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *RenderUtils::initTexture(const std::string path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == nullptr)
    {
        SDL_Log("Unable to load texture: %s", SDL_GetError());
        return nullptr;
    }

    // Set the scaling mode for the texture
    if (!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST))
    {
        SDL_Log("Failed to set texture scale mode: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

TTF_Font *RenderUtils::initFont(const std::string path, int fontSize)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr)
    {
        SDL_Log("Failed to load font %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }
    return font;
}

SDL_Texture *RenderUtils::initTextTexture(TTF_Font *font, const std::string text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
    if (surface == nullptr)
    {
        SDL_Log("Failed to render text: %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void RenderUtils::setRenderColor(const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void RenderUtils::renderCircle(int cx, int cy, int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderPoint(renderer, cx + x, cy - y);
        SDL_RenderPoint(renderer, cx + x, cy + y);
        SDL_RenderPoint(renderer, cx - x, cy - y);
        SDL_RenderPoint(renderer, cx - x, cy + y);
        SDL_RenderPoint(renderer, cx + y, cy - x);
        SDL_RenderPoint(renderer, cx + y, cy + x);
        SDL_RenderPoint(renderer, cx - y, cy - x);
        SDL_RenderPoint(renderer, cx - y, cy + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void RenderUtils::renderFilledCircle(int cx, int cy, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void RenderUtils::renderRect(SDL_FRect &rect)
{
    SDL_RenderRect(renderer, &rect);
}

void RenderUtils::renderFilledRect(SDL_FRect &rect)
{
    SDL_RenderFillRect(renderer, &rect);
}

void RenderUtils::renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect)
{
    SDL_RenderTexture(renderer, texture, srcRect, dstRect);
}

void RenderUtils::renderTextureFliped(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect)
{
    SDL_RenderTextureRotated(renderer, texture, srcRect, dstRect, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
}

RenderUtils::~RenderUtils()
{
    renderer = nullptr;
    TTF_Quit();
}
