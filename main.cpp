#include "Constants.hpp"
#include "Sprite.hpp"
#include "Utils.hpp"
#include "SDLManager.hpp"
#include <vector>

bool showHitboxes = true;
bool sprinting = false;
bool lookingLeft = true;
bool movingDown = false;
bool movingUp = false;
bool movingLeft = false;
bool movingRight = false;
bool jump = false;
bool running;
bool shooting = false;
Uint32 shootingEndTime = 0;

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
        cleanup(window, renderer, spriteSheetTexture, backgroundTexture, MG1SpriteSheetTexture, MG2SpriteSheetTexture, MGRUNSpriteSheetTexture, LEFTMGRUNSpriteSheetTexture, LEFTMGSHOOTSpriteSheetTexture);
        return 1;
    }

    // Create the main sprite with MG1SpriteSheetTexture
    Sprite mainSprite(980, 450, MAIN_GUY_WIDTH, MAIN_GUY_HEIGHT, MG1SpriteSheetTexture, TOTAL_FRAMES_MAIN_GUY, FRAMES_PER_ROW_MAIN_GUY, FRAME_DELAY, MAIN_GUY_SPEED);
    Sprite gangsterSprite(50, 450, GANGSTER_WIDTH, GANGSTER_HEIGHT, spriteSheetTexture, TOTAL_FRAMES_GANGSTER, FRAMES_PER_ROW_GANGSTER_WALK, FRAME_DELAY, GANGSTER_SPEED);
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
                case SDLK_a:
                    movingLeft = true;
                    lookingLeft = true;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    movingRight = true;
                    lookingLeft = false;
                    break;
                case SDLK_UP:
                case SDLK_w:
                case SDLK_SPACE:
                    jump = true;
                    mainSprite.jump(); // Make the mainSprite jump
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    movingDown = true;
                    break;
                case SDLK_F11:
                    toggleFullscreen(window);
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LSHIFT:
                    sprinting = true;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                case SDLK_a:
                    movingLeft = false;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    movingRight = false;
                    break;
                case SDLK_UP:
                case SDLK_w:
                case SDLK_SPACE:
                    jump = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    movingDown = false;
                    break;
                case SDLK_LSHIFT:
                    sprinting = false;
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                shooting = true;
                shootingEndTime = SDL_GetTicks() + SHOOTING_DELAY; // Set the end time for shooting
            }
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Update sprite texture based on state
        if (shooting)
        {
            mainSprite.setTexture(MG2SpriteSheetTexture); // Switch to the shooting texture
            mainSprite.applyDamageToGangsterIfNeeded(mouseX, mouseY, gangsterSprite, shooting);
        }
        else if (movingRight || movingLeft || movingDown)
        {
            mainSprite.setTexture(movingRight ? MGRUNSpriteSheetTexture : LEFTMGRUNSpriteSheetTexture);
        }
        else
        {
            mainSprite.setTexture(MG1SpriteSheetTexture); // Switch back to idle texture
        }

        if (SDL_GetTicks() > shootingEndTime && shooting)
        {
            shooting = false;                             // End the shooting state
            mainSprite.setTexture(MG1SpriteSheetTexture); // Switch back to idle texture
        }

        // Handle movement and texture switching
        if (movingRight && !movingLeft)
        {
            mainSprite.setSpeed(sprinting ? SPRINT_SPEED : NORMAL_SPEED);
            mainSprite.moveRight();
        }
        else if (movingLeft && !movingRight)
        {
            mainSprite.setSpeed(sprinting ? SPRINT_SPEED : NORMAL_SPEED);
            mainSprite.moveLeft();
        }
        else if (movingDown)
        {
            mainSprite.moveDown();
        }

        // Update the main sprite's position and animation
        mainSprite.updatePosition();      // Update position based on gravity and jumping
        mainSprite.updateAnimation();     // Update animation frame
        gangsterSprite.updatePosition();  // Update position based on gravity and jumping
        gangsterSprite.updateAnimation(); // Update animation frame

        // Clear the screen with a color
        SDL_RenderClear(renderer);

        // Render the background image
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Drawing the main sprite
        SDL_Rect dstRect = {mainSprite.getX(), mainSprite.getY(),
                            static_cast<int>(MAIN_GUY_WIDTH * MAIN_GUY_SCALE),
                            static_cast<int>(MAIN_GUY_HEIGHT * MAIN_GUY_SCALE)};
        SDL_Rect srcRect = mainSprite.getSourceRect(); // Store the source rectangle
        SDL_RenderCopy(renderer, mainSprite.getTexture(), &srcRect, &dstRect);

        // Drawing the gangster sprite
        SDL_Rect dstRect1 = {gangsterSprite.getX(), gangsterSprite.getY(),
                             static_cast<int>(GANGSTER_WIDTH * GANGSTER_SCALE),
                             static_cast<int>(GANGSTER_HEIGHT * GANGSTER_SCALE)};
        SDL_Rect srcRect1 = gangsterSprite.getSourceRect(); // Store the source rectangle
        SDL_RenderCopy(renderer, gangsterSprite.getTexture(), &srcRect1, &dstRect1);
        if (showHitboxes)
        {
            mainSprite.drawHitbox(renderer);
            gangsterSprite.drawHitbox(renderer);
        }
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
    cleanup(window, renderer, spriteSheetTexture, backgroundTexture, MG1SpriteSheetTexture, MG2SpriteSheetTexture, MGRUNSpriteSheetTexture, LEFTMGRUNSpriteSheetTexture, LEFTMGSHOOTSpriteSheetTexture);

    return 0;
}
