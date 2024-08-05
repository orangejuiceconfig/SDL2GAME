#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h> // Include SDL header

class Sprite
{
public:
    // Constructor to initialize positions
    Sprite(int x, int y);

    // Constructor to initialize all properties
    Sprite(int x, int y, int w, int h, SDL_Texture *tex, int totalFrames, int framesPerRow, Uint32 frameDelay, int sp);

    // Method to get the source rectangle for the current frame
    SDL_Texture *getTexture() const;
    SDL_Rect getSourceRect() const;

    // Method to move the sprite
    void moveRight();
    void moveLeft();
    void moveDown();
    void moveUp();
    void jump();

    // gravity
    void updatePosition();
    // Method to check if the sprite is off-screen
    bool isOffScreen() const;

    // Method to update the animation frame
    void updateAnimation();

    // Method to set a new texture for the sprite
    void setTexture(SDL_Texture *newTexture);

    int xpos = 0;         // X position of the sprite
    int ypos = 0;         // Y position of the sprite
    int speed = 1;        // Speed of movement in pixels per frame
    int width;            // Width of the sprite
    int height;           // Height of the sprite
    SDL_Texture *texture; // Texture associated with the sprite

    // Animation variables
    int totalFrames;
    int framesPerRow;
    int currentFrame;
    Uint32 lastFrameTime;
    Uint32 frameDelay;

    // Jumping and gravity variables
    float velocityY; // Current vertical velocity
    bool isJumping;  // Flag to check if the sprite is jumping
    bool isFalling;  // Flag to check if the sprite is falling

private:
    SDL_Rect getSourceRectMain() const; // Kept private, it's not necessary to have it public
};

#endif // SPRITE_HPP
