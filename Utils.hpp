// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>

SDL_Texture* loadNewSpriteSheet(SDL_Renderer* renderer);
SDL_Texture* MainGuy1(SDL_Renderer* renderer);
SDL_Texture* MainGuy2(SDL_Renderer* renderer);
SDL_Texture* MainGuyRUN(SDL_Renderer* renderer);
SDL_Texture* MainGuyLEFTRUN(SDL_Renderer* renderer);
SDL_Texture* MainGuyRightShot(SDL_Renderer* renderer);

bool loadTextures(SDL_Renderer* renderer, SDL_Texture*& spriteSheetTexture, SDL_Texture*& backgroundTexture);

void toggleFullscreen(SDL_Window* window);

#endif // UTILS_HPP
