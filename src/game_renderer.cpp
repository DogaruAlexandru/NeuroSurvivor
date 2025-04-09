#include "game_renderer.h"
#include "render_utils.h"
#include "camera.h"

GameRenderer::GameRenderer(Game &game)
    : game(game),
      playerRenderer(game.getPlayer())
{
    float baseUnit = Camera::getInstance().getBaseUnit();
    healthBarWidth = baseUnit * HEALTH_BAR_WIDTH_SCALE;
    float healthBarHeight = baseUnit * HEALTH_BAR_HEIGHT_SCALE;
    float healthBarPosX = baseUnit * HEALTH_BAR_POS_X_SCALE;
    float healthBarPosY = baseUnit * HEALTH_BAR_POS_Y_SCALE;
    healthBarRect = {healthBarPosX, healthBarPosY, healthBarWidth, healthBarHeight};
    healthRect = {healthBarPosX, healthBarPosY, getHealthWidth(game.getPlayer()), healthBarHeight};

    int fontSize = baseUnit / 10; // Adjust the divisor to control the font size scaling
    TTF_Font *font = RenderUtils::getInstance().initFont("assets/fonts/Garamond_BE_Medium.otf", fontSize);
    textTexture = RenderUtils::getInstance().initTextTexture(font, "You Died!", WHITE);
    TTF_CloseFont(font);

    endGameRect = {
        (Camera::getInstance().getScreenWidth() - textTexture->w) * 0.5f,
        (Camera::getInstance().getScreenHeight() - textTexture->h) * 0.75f,
        static_cast<float>(textTexture->w),
        static_cast<float>(textTexture->h)};
}

float GameRenderer::getHealthWidth(const Entity &player)
{
    return healthBarWidth * (player.getHealth() / player.getMaxHealth());
}

GameRenderer::~GameRenderer()
{
    SDL_DestroyTexture(textTexture);
}

void GameRenderer::render(double alpha, double timeSinceLastRender)
{
    RenderUtils::getInstance().clearScreen();

    int screenCenterX = Camera::getInstance().getScreenCenterX();
    int screenCenterY = Camera::getInstance().getScreenCenterY();
    int worldCenterX = Camera::getInstance().getWorldCenterX();
    int worldCenterY = Camera::getInstance().getWorldCenterY();

    // Draw the player (sprite)
    playerRenderer.render(timeSinceLastRender);

    // Draw the enemies (blue)
    std::vector<Enemy> enemies = game.getEnemies();
    RenderUtils::getInstance().setRenderColor(BLUE);
    for (auto &enemy : enemies)
    {
        int screenX = screenCenterX + (enemy.getPrevX() + alpha * (enemy.getX() - enemy.getPrevX()) - worldCenterX);
        int screenY = screenCenterY + (enemy.getPrevY() + alpha * (enemy.getY() - enemy.getPrevY()) - worldCenterY);

        RenderUtils::getInstance().renderFilledCircle(screenX, screenY, enemy.getRadius());
    }

    // Draw the projectiles (red)
    std::deque<Projectile> projectiles = game.getProjectiles();
    RenderUtils::getInstance().setRenderColor(RED);
    for (auto &projectile : projectiles)
    {
        int screenX = screenCenterX + (projectile.getPrevX() + alpha * (projectile.getX() - projectile.getPrevX()) - worldCenterX);
        int screenY = screenCenterY + (projectile.getPrevY() + alpha * (projectile.getY() - projectile.getPrevY()) - worldCenterY);
        RenderUtils::getInstance().renderFilledCircle(screenX, screenY, projectile.getRadius());
    }

    if (!game.getPlayer().isAlive())
    {
        RenderUtils::getInstance().renderTexture(textTexture, nullptr, &endGameRect);
    }

    RenderUtils::getInstance().setRenderColor(WHITE);
    RenderUtils::getInstance().renderFilledRect(healthBarRect);

    healthRect.w = getHealthWidth(game.getPlayer());
    RenderUtils::getInstance().setRenderColor(RED);
    RenderUtils::getInstance().renderFilledRect(healthRect);

    RenderUtils::getInstance().renderPresent();
}
