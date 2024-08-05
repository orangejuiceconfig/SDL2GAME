#include "Sprite.hpp"
#include "Constants.hpp" // Include the header file where constants are defined

// Constructor to initialize positions
Sprite::Sprite(int x, int y) : xpos(x), ypos(y), speed(1), width(0), height(0),
                               texture(nullptr), totalFrames(0), framesPerRow(0),
                               currentFrame(0), lastFrameTime(0), frameDelay(0),
                               velocityY(0), isJumping(false), isFalling(false) {}

// Constructor to initialize all properties
Sprite::Sprite(int x, int y, int w, int h, SDL_Texture *tex, int totalFrames, int framesPerRow, Uint32 frameDelay, int sp)
    : xpos(x), ypos(y), speed(sp), width(w), height(h),
      texture(tex), totalFrames(totalFrames), framesPerRow(framesPerRow),
      currentFrame(0), lastFrameTime(0), frameDelay(frameDelay),
      velocityY(0), isJumping(false), isFalling(false) {}

// Method to move the sprite to the right
void Sprite::moveRight()
{
    xpos += speed;
}

void Sprite::moveLeft()
{
    xpos -= speed;
}
void Sprite::moveUp()
{
    ypos -= 2;
}

void Sprite::moveDown()
{
    ypos += 2;
}

// Method to make the sprite jump
void Sprite::jump()
{
    if (!isJumping && !isFalling) // Only jump if not already jumping or falling
    {
        velocityY = JUMP_FORCE; // Apply the jump force
        isJumping = true;       // Set jumping state
        isFalling = true;       // Set falling state to true immediately after jumping
    }
}

// Method to update the position of the sprite
void Sprite::updatePosition()
{
    // Apply gravity to the vertical velocity
    if (isFalling)
    {
        velocityY += GRAVITY; // Gravity affects falling
    }

    // Update the y position based on the velocity
    ypos += static_cast<int>(velocityY);

    // Check for ground collision
    if (ypos >= GROUND_LEVEL)
    {
        ypos = GROUND_LEVEL; // Reset y position to ground level
        isJumping = false;   // Reset jumping state
        isFalling = false;   // Reset falling state
        velocityY = 0;       // Reset vertical velocity
    }
}

// Method to check if the sprite is off-screen
bool Sprite::isOffScreen() const
{
    // Assuming screen width is 1280, update as needed
    return xpos > 1280;
}

// Method to update the animation frame
void Sprite::updateAnimation()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastFrameTime + frameDelay)
    {
        currentFrame = (currentFrame + 1) % totalFrames;
        lastFrameTime = currentTime;
    }
}

// Method to get the source rectangle for the current frame
SDL_Rect Sprite::getSourceRect() const
{
    int frameX = (currentFrame % framesPerRow) * width;
    int frameY = (currentFrame / framesPerRow) * height;
    return {frameX, frameY, width, height};
}

// Method to get the source rectangle for the main character's current frame
SDL_Rect Sprite::getSourceRectMain() const
{
    int mainFrameX = (currentFrame % framesPerRow) * width;
    int mainFrameY = (currentFrame / framesPerRow) * height;
    return {mainFrameX, mainFrameY, width, height};
}

// Method to set a new texture for the sprite
void Sprite::setTexture(SDL_Texture *newTexture)
{
    texture = newTexture;
}
SDL_Texture *Sprite::getTexture() const
{
    return texture;
}