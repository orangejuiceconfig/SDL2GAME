#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // Include SDL_image for image loading
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SPRITE_WIDTH 140
#define SPRITE_HEIGHT 200 // Rounded height of each frame
#define FRAME_RATE 60 // Desired frame rate

bool running;

// Number of frames in the animation
const int TOTAL_FRAMES = 6;

// Frames per row in the spritesheet
const int FRAMES_PER_ROW = 6;

// Delay between frames in milliseconds
const int FRAME_DELAY = 150;

int main(int argc, const char *argv[])
{
    running = true;

    // Initialize SDL and SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_image with PNG support
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Load the spritesheet image
    SDL_Surface *spriteSheetSurface = IMG_Load("or-removebg-preview.png");
    if (spriteSheetSurface == NULL)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *spriteSheetTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
    SDL_FreeSurface(spriteSheetSurface); // Free the surface as we no longer need it
    if (spriteSheetTexture == NULL)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initial position of the stickman
    SDL_Rect dstRect = {SCREEN_WIDTH / 2 - SPRITE_WIDTH / 2, SCREEN_HEIGHT / 2 - SPRITE_HEIGHT / 2, SPRITE_WIDTH, SPRITE_HEIGHT};

    // Animation variables
    int currentFrame = 0;
    Uint32 lastFrameTime = 0; // To track time between frame updates

    // Calculate the frame duration based on the desired frame rate
    Uint32 frameDuration = 1000 / FRAME_RATE; 

    // Main game loop
    while (running)
    {
        Uint32 frameStartTime = SDL_GetTicks(); // Track the start time of the frame

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Get the current time
        Uint32 currentTime = SDL_GetTicks();

        // Update frame if enough time has passed
        if (currentTime > lastFrameTime + FRAME_DELAY)
        {
            currentFrame++;
            if (currentFrame >= TOTAL_FRAMES)
            {
                currentFrame = 0; // Loop back to the first frame
            }
            lastFrameTime = currentTime; // Reset last frame time
        }

        // Calculate the source rectangle for the current frame
        int frameX = (currentFrame % FRAMES_PER_ROW) * SPRITE_WIDTH;
        int frameY = (currentFrame / FRAMES_PER_ROW) * SPRITE_HEIGHT;

        SDL_Rect srcRect = {frameX, frameY, SPRITE_WIDTH, SPRITE_HEIGHT};

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        // Render the current frame of the sprite
        SDL_RenderCopy(renderer, spriteSheetTexture, &srcRect, &dstRect);

        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // Calculate the time taken for the current frame
        Uint32 frameEndTime = SDL_GetTicks();
        Uint32 frameTime = frameEndTime - frameStartTime;

        // Delay to maintain frame rate
        if (frameTime < frameDuration)
        {
            SDL_Delay(frameDuration - frameTime);
        }
    }

    // Clean up resources
    SDL_DestroyTexture(spriteSheetTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
