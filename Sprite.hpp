#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h> // Include SDL header

class Sprite
{
public:
    // Constructors
    Sprite(int x, int y);
    Sprite(int x, int y, int w, int h, SDL_Texture *tex, int totalFrames, int framesPerRow, Uint32 frameDelay, int sp);

    // Method to get the source rectangle for the current frame
    SDL_Texture *getTexture() const;
    SDL_Rect getSourceRect() const;
    SDL_Rect getSourceRectMain() const; // Add this line

    // Methods for movement and jumping
    void moveRight();
    void moveLeft();
    void moveDown();
    void jump();

    // Method to apply damage
    void applyDamage(int damage);

    // Method to set the speed of the sprite
    void setSpeed(float newSpeed);

    // Methods for gravity and position updates
    void updatePosition();
    bool isOffScreen() const;
    void updateAnimation();

    // Method to set a new texture for the sprite
    void setTexture(SDL_Texture *newTexture);

    // Method to check if the cursor is over the sprite
    static bool isCursorOverSprite(int mouseX, int mouseY, const Sprite &sprite);

    // Getter methods
    int getX() const { return xpos; }
    int getY() const { return ypos; }
    int getWidth() const;
    int getHeight() const;

    void applyDamageToGangsterIfNeeded(int mouseX, int mouseY, Sprite &gangsterSprite, bool shooting);
    SDL_Rect getHitbox() const;
    void drawHitbox(SDL_Renderer *renderer) const;

private:
    // Private members
    int xpos;
    int ypos;
    int speed;
    int width;
    int height;
    SDL_Texture *texture;

    int totalFrames;
    int framesPerRow;
    int currentFrame;
    Uint32 lastFrameTime;
    Uint32 frameDelay;

    float velocityY;
    bool isJumping;
    bool isFalling;
    bool dead;

    // Private method to get the source rectangle for the main character's current frame
};

#endif // SPRITE_HPP
