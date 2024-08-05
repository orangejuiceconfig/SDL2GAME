// Utils.cpp
#include "Utils.hpp"
#include <SDL2/SDL_image.h> // Include SDL_image for image loading
#include <iostream>         // Include iostream for std::cerr and std::endl

void toggleFullscreen(SDL_Window *window)
{
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    bool isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen); // Hide cursor in fullscreen, show in windowed mode
}

SDL_Texture *loadNewSpriteSheet(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/MainGuyShoot.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Texture *MainGuy1(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/Soldier_1/Idle.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture *MainGuy2(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/Soldier_1/LeftShot_2.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture *MainGuyLEFTRUN(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/Soldier_1/LeftRun.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Texture *MainGuyRightShot(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/Soldier_1/RightShot_2.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Texture *MainGuyRUN(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("/home/usr/2d game/sprites/Soldier_1/RightRun.png");
    if (!surface)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
