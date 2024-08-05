// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include "Sprite.hpp" // Ensure this include is here

#include <SDL2/SDL.h>


SDL_Texture* loadNewSpriteSheet(SDL_Renderer* renderer);
SDL_Texture* MainGuy1(SDL_Renderer* renderer);
SDL_Texture* MainGuy2(SDL_Renderer* renderer);
SDL_Texture* MainGuyRUN(SDL_Renderer* renderer);
SDL_Texture* MainGuyLEFTRUN(SDL_Renderer* renderer);
SDL_Texture* MainGuyRightShot(SDL_Renderer* renderer);

bool loadTextures(SDL_Renderer* renderer, SDL_Texture*& spriteSheetTexture, SDL_Texture*& backgroundTexture);
void toggleFullscreen(SDL_Window* window);
bool isCursorOverSprite(int mouseX, int mouseY, const Sprite &sprite);

#endif // UTILS_HPP
