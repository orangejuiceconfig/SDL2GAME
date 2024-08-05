#include "Constants.hpp"
#include "Sprite.hpp"
#include "Utils.hpp"
#include "SDLManager.hpp"
#include <vector>

bool lookingLeft = true;
bool movingDown = false;
bool movingUp = false;
bool movingLeft = false;
bool movingRight = false;
bool jump = false;
bool running;
bool shooting = false;
Uint32 shootingEndTime = 0;
const Uint32 SHOOTING_DELAY = 525; // Delay in milliseconds (adjust as needed)

int main(int argc, const char *argv[])
{
    running = true;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // Initialize SDL and create window and renderer
    if (!initSDL(window, renderer))
    {
        std::cerr << "Failed to initialize SDL.\n";
        return 1;
    }

    SDL_Texture *spriteSheetTexture = nullptr;
    SDL_Texture *backgroundTexture = nullptr;
    SDL_Texture *MG1SpriteSheetTexture = nullptr;
    SDL_Texture *MG2SpriteSheetTexture = nullptr;
    SDL_Texture *MGRUNSpriteSheetTexture = nullptr;
    SDL_Texture *LEFTMGRUNSpriteSheetTexture = nullptr;
    SDL_Texture *LEFTMGSHOOTSpriteSheetTexture = nullptr;

    // Load textures
    if (!loadTextures(renderer, spriteSheetTexture, backgroundTexture) ||
        !(MG1SpriteSheetTexture = MainGuy1(renderer)) ||
        !(MG2SpriteSheetTexture = MainGuy2(renderer)) ||
        !(LEFTMGRUNSpriteSheetTexture = MainGuyLEFTRUN(renderer)) ||
        !(LEFTMGSHOOTSpriteSheetTexture = MainGuyRightShot(renderer)) ||
        !(MGRUNSpriteSheetTexture = MainGuyRUN(renderer)))
    {
        std::cerr << "Error loading textures.\n";
        cleanup(window, renderer, spriteSheetTexture, backgroundTexture, MG1SpriteSheetTexture, MG2SpriteSheetTexture, MGRUNSpriteSheetTexture, LEFTMGRUNSpriteSheetTexture, LEFTMGSHOOTSpriteSheetTexture); // Corrected variable name
        return 1;
    }

    // Create the main sprite with MG1SpriteSheetTexture
    Sprite mainSprite(980, 500, MAIN_GUY_WIDTH, MAIN_GUY_HEIGHT, MG1SpriteSheetTexture, TOTAL_FRAMES_MAIN_GUY, FRAMES_PER_ROW_MAIN_GUY, FRAME_DELAY, MAIN_GUY_SPEED);

    // Create multiple zombies with different positions
    std::vector<Sprite> zombies = {
        Sprite(50, 450, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, spriteSheetTexture, TOTAL_FRAMES_ZOMBIE, FRAMES_PER_ROW_ZOMBIE_WALK, FRAME_DELAY, ZOMBIE_SPEED),
        Sprite(250, 440, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, spriteSheetTexture, TOTAL_FRAMES_ZOMBIE, FRAMES_PER_ROW_ZOMBIE_WALK, FRAME_DELAY, ZOMBIE_SPEED),
        Sprite(450, 460, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, spriteSheetTexture, TOTAL_FRAMES_ZOMBIE, FRAMES_PER_ROW_ZOMBIE_WALK, FRAME_DELAY, ZOMBIE_SPEED)};

    // Animation variables

    // Calculate the frame duration based on the desired frame rate
    Uint32 frameDuration = (FRAME_RATE > 0) ? 1000 / FRAME_RATE : 16; // Fallback to a default value

    // Main game loop
    while (running)
    {
        Uint32 frameStartTime = SDL_GetTicks(); // Track the start time of the frame

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    movingLeft = true;
                    lookingLeft = true;
                    break;
                case SDLK_RIGHT:
                    movingRight = true;
                    lookingLeft = false;
                    break;
                case SDLK_UP:
                    movingUp = true;
                    break;
                case SDLK_DOWN:
                    movingDown = true;
                    break;
                case SDLK_SPACE:
                    jump = true;
                    mainSprite.jump(); // Make the mainSprite jump
                    break;
                case SDLK_F11:
                    toggleFullscreen(window);
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP) // Handle key release
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    movingLeft = false;
                    break;
                case SDLK_RIGHT:
                    movingRight = false;
                    break;
                case SDLK_UP:
                    movingUp = false;
                    break;
                case SDLK_DOWN:
                    movingDown = false;
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                shooting = true;
                shootingEndTime = SDL_GetTicks() + SHOOTING_DELAY; // Set the end time for shooting
            }
        }

        // Switch the main sprite's texture based on the state
        if (shooting && lookingLeft)
        {
            mainSprite.setTexture(MG2SpriteSheetTexture); // Switch to the shooting texture
        }
        else
        {
            mainSprite.setTexture(MG2SpriteSheetTexture);
        }

        if (SDL_GetTicks() > shootingEndTime)
        {
            shooting = false;                             // End the shooting state
            mainSprite.setTexture(MG1SpriteSheetTexture); // Switch back to idle texture
        }

        // Handle movement and texture switching
        if (movingRight && !movingLeft)
        {
            mainSprite.setTexture(MGRUNSpriteSheetTexture);
            mainSprite.moveRight(); // Move the mainSprite to the right
        }
        else if (movingLeft && !movingRight)
        {
            mainSprite.setTexture(LEFTMGRUNSpriteSheetTexture);
            mainSprite.moveLeft(); // Move the mainSprite to the left
        }
        else if (movingUp && !movingDown)
        {
            mainSprite.moveUp(); // Move the mainSprite up
        }
        else if (movingDown && !movingUp)
        {
            mainSprite.moveDown(); // Move the mainSprite down
        }
        else
        {
            mainSprite.setTexture(MG1SpriteSheetTexture); // Switch back to idle texture
        }

        // Update the main sprite's position and animation
        mainSprite.updatePosition();  // Update position based on gravity and jumping
        mainSprite.updateAnimation(); // Update animation frame

        // Clear the screen with a color
        SDL_RenderClear(renderer);

        // Render the background image
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Move zombies and remove if off-screen
        for (auto it = zombies.begin(); it != zombies.end();)
        {
            it->moveRight(); // Move the zombie to the right

            if (it->isOffScreen())
            {
                std::cout << "A zombie has left the screen and been removed!\n";
                it = zombies.erase(it); // Remove the zombie and update the iterator
            }
            else
            {
                int scaledWidth = static_cast<int>(ZOMBIE_WIDTH * ZOMBIE_SCALE);
                int scaledHeight = static_cast<int>(ZOMBIE_HEIGHT * ZOMBIE_SCALE);

                SDL_Rect dstRect = {it->xpos, it->ypos, scaledWidth, scaledHeight};
                SDL_Rect srcRect = it->getSourceRect(); // Use getSourceRect for zombies
                SDL_RenderCopy(renderer, spriteSheetTexture, &srcRect, &dstRect);
                ++it; // Move to the next zombie
            }
        }

        // Update animation frames for zombies
        for (auto &zombie : zombies)
        {
            zombie.updateAnimation();
        }

        // Calculate the scaled width and height for the main sprite
        int scaledWidth = static_cast<int>(MAIN_GUY_WIDTH * MAIN_GUY_SCALE);
        int scaledHeight = static_cast<int>(MAIN_GUY_HEIGHT * MAIN_GUY_SCALE);

        // Render the main sprite with scaling
        SDL_Rect dstRect = {mainSprite.xpos, mainSprite.ypos, scaledWidth, scaledHeight};
        SDL_Rect srcRect = mainSprite.getSourceRect();
        SDL_RenderCopy(renderer, mainSprite.getTexture(), &srcRect, &dstRect);

        // Present the updated renderer
        SDL_RenderPresent(renderer);

        // Cap the frame rate
        Uint32 frameEndTime = SDL_GetTicks();
        Uint32 frameElapsedTime = frameEndTime - frameStartTime;

        if (frameElapsedTime < frameDuration)
        {
            SDL_Delay(frameDuration - frameElapsedTime);
        }
    }

    // Clean up resources and quit SDL
    cleanup(window, renderer, spriteSheetTexture, backgroundTexture, MG1SpriteSheetTexture, MG2SpriteSheetTexture, MGRUNSpriteSheetTexture, LEFTMGRUNSpriteSheetTexture, LEFTMGSHOOTSpriteSheetTexture); // Ensure all textures are cleaned up

    return 0;
}
