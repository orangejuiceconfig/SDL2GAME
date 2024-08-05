#include "Sprite.hpp"
#include "Constants.hpp"
#include <iostream>

// Constructor to initialize positions
Sprite::Sprite(int x, int y)
    : xpos(x), ypos(y), speed(1), width(0), height(0),
      texture(nullptr), totalFrames(0), framesPerRow(0),
      currentFrame(0), lastFrameTime(0), frameDelay(0),
      velocityY(0), isJumping(false), isFalling(false), dead(false) {}

// Constructor to initialize all properties
Sprite::Sprite(int x, int y, int w, int h, SDL_Texture *tex, int totalFrames, int framesPerRow, Uint32 frameDelay, int sp)
    : xpos(x), ypos(y), speed(sp), width(w), height(h),
      texture(tex), totalFrames(totalFrames), framesPerRow(framesPerRow),
      currentFrame(0), lastFrameTime(0), frameDelay(frameDelay),
      velocityY(0), isJumping(false), isFalling(false), dead(false) {}

// Method implementations
void Sprite::moveRight() { xpos += speed; }
void Sprite::moveLeft() { xpos -= speed; }
void Sprite::moveDown() { ypos += 2; }

void Sprite::setSpeed(float newSpeed) { speed = newSpeed; }

void Sprite::jump()
{
    if (!isJumping && !isFalling)
    {
        velocityY = JUMP_FORCE;
        isJumping = true;
        isFalling = true;
    }
}

void Sprite::applyDamageToGangsterIfNeeded(int mouseX, int mouseY, Sprite &gangster, bool shooting)
{
    if (shooting)
    {
        SDL_Rect gangsterHitbox = gangster.getHitbox(); // Use hitbox dimensions
        if (mouseX >= gangsterHitbox.x &&
            mouseX <= (gangsterHitbox.x + gangsterHitbox.w) &&
            mouseY >= gangsterHitbox.y &&
            mouseY <= (gangsterHitbox.y + gangsterHitbox.h))
        {
            // Apply damage to gangster
            std::cout << "Hit detected!\n";
        }
    }
}

void Sprite::updatePosition()
{
    if (isFalling)
    {
        velocityY += GRAVITY;
    }
    ypos += static_cast<int>(velocityY);

    if (ypos >= GROUND_LEVEL)
    {
        ypos = GROUND_LEVEL;
        isJumping = false;
        isFalling = false;
        velocityY = 0;
    }
}

bool Sprite::isOffScreen() const { return xpos > 1280; }

void Sprite::updateAnimation()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastFrameTime + frameDelay)
    {
        currentFrame = (currentFrame + 1) % totalFrames;
        lastFrameTime = currentTime;
    }
}

SDL_Rect Sprite::getSourceRect() const
{
    int frameX = (currentFrame % framesPerRow) * width;
    int frameY = (currentFrame / framesPerRow) * height;
    return {frameX, frameY, width, height};
}

SDL_Rect Sprite::getSourceRectMain() const
{
    int mainFrameX = (currentFrame % framesPerRow) * width;
    int mainFrameY = (currentFrame / framesPerRow) * height;
    return {mainFrameX, mainFrameY, width, height};
}

void Sprite::setTexture(SDL_Texture *newTexture) { texture = newTexture; }

SDL_Texture *Sprite::getTexture() const { return texture; }

int Sprite::getWidth() const { return width; }
int Sprite::getHeight() const { return height; }

bool Sprite::isCursorOverSprite(int mouseX, int mouseY, const Sprite &sprite)
{
    SDL_Rect spriteRect = {sprite.xpos, sprite.ypos, sprite.getWidth(), sprite.getHeight()};
    return (mouseX >= spriteRect.x &&
            mouseX <= (spriteRect.x + spriteRect.w) &&
            mouseY >= spriteRect.y &&
            mouseY <= (spriteRect.y + spriteRect.h));
}

void Sprite::applyDamage(int damage)
{
    if (damage > GANGSTER_HEALTH)
    {
        std::cout << "Gangster dead!" << std::endl;
    }
}

SDL_Rect Sprite::getHitbox() const
{
    SDL_Rect hitbox = {xpos, ypos, width, height};

    // Increase the width and height of the hitbox
    int hitboxMargin = 10;    // Adjust the margin as needed
    int verticalOffset = 119; // Adjust the offset as needed
    int horizontalOffset = 95; // Adjust the offset as needed
    hitbox.x -= hitboxMargin;
    hitbox.y -= hitboxMargin;
    hitbox.w -= 5 * hitboxMargin;
    hitbox.h += 2 * hitboxMargin;
    hitbox.y += verticalOffset;
    hitbox.x += horizontalOffset;

    return hitbox;
}
void Sprite::drawHitbox(SDL_Renderer *renderer) const
{
    SDL_Rect hitbox = getHitbox();

    // Set the draw color (red for the hitbox)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color with full opacity

    // Draw the rectangle (hitbox)
    SDL_RenderDrawRect(renderer, &hitbox);
}
