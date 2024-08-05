#include "SDLManager.hpp"
#include "Constants.hpp"

bool initSDL(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

bool loadTextures(SDL_Renderer *renderer, SDL_Texture *&spriteSheetTexture, SDL_Texture *&backgroundTexture)
{
    SDL_Surface *spriteSheetSurface = IMG_Load(GANGSTER_SKIN);
    if (spriteSheetSurface == nullptr)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return false;
    }

    spriteSheetTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
    SDL_FreeSurface(spriteSheetSurface); // Free the surface as we no longer need it
    if (spriteSheetTexture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load the background image
    SDL_Surface *backgroundSurface = SDL_LoadBMP(BACKGROUND1);
    if (backgroundSurface == nullptr)
    {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(spriteSheetTexture);
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface); // Free the surface as we no longer need it
    if (backgroundTexture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(spriteSheetTexture);
        return false;
    }

    return true;
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *spriteSheetTexture, SDL_Texture *backgroundTexture, SDL_Texture *MG1SpriteSheetTexture, SDL_Texture *MG2SpriteSheetTexture, SDL_Texture *MGRUNSpriteSheetTexture, SDL_Texture *LEFTMGRUNSpriteSheetTexture, SDL_Texture *LEFTMGSHOOTSpriteSheetTexture)
{
    if (LEFTMGSHOOTSpriteSheetTexture)
    {
        SDL_DestroyTexture(LEFTMGSHOOTSpriteSheetTexture);
    }
    if (LEFTMGRUNSpriteSheetTexture)
    {
        SDL_DestroyTexture(LEFTMGRUNSpriteSheetTexture);
    }
    if (MGRUNSpriteSheetTexture)
    {
        SDL_DestroyTexture(MGRUNSpriteSheetTexture);
    }
    if (MG2SpriteSheetTexture)
    {
        SDL_DestroyTexture(MG2SpriteSheetTexture);
    }
    if (MG1SpriteSheetTexture)
    {
        SDL_DestroyTexture(MG1SpriteSheetTexture);
    }
    if (spriteSheetTexture)
    {
        SDL_DestroyTexture(spriteSheetTexture);
    }
    if (backgroundTexture)
    {
        SDL_DestroyTexture(backgroundTexture);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
