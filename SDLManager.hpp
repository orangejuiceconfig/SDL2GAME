#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
bool loadTextures(SDL_Renderer* renderer, SDL_Texture*& spriteSheetTexture, SDL_Texture*& backgroundTexture);
void cleanup(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* spriteSheetTexture, SDL_Texture* backgroundTexture, SDL_Texture* MG1SpriteSheetTexture, SDL_Texture* MG2SpriteSheetTexture, SDL_Texture* MGRUNSpriteSheetTexture, SDL_Texture* LEFTMGRUNSpriteSheetTexture, SDL_Texture* LEFTMGSHOOTSpriteSheetTexture);

#endif