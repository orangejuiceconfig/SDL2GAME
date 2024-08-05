#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Zombie sprite details

#define ZOMBIE_SPEED 1
#define ZOMBIE_SCALE 1.5
#define ZOMBIE_WIDTH 121  // Width of each frame
#define ZOMBIE_HEIGHT 119 // Height of each frame

// MainGuy sprite details
#define MAIN_GUY_WIDTH 128 
#define MAIN_GUY_HEIGHT 128
#define MAIN_GUY_SPEED 4
#define MAIN_GUY_SCALE 2

#define ZOMBIE_SKIN "/home/usr/2d game/sprites/Zombie/ZombieWalk.png" //"/home/usr/2d game/sprites/ZombieWalkDryRed.png"
#define BACKGROUND1 "/home/usr/2d game/sprites/BackgroundPixel.bmp"
#define FRAME_RATE 60

// Gravity and Jump constants
const float GRAVITY = 0.5f;     // Gravity applied to the main guy
const float JUMP_FORCE = -12.0f; // Initial velocity when jumping
const int GROUND_LEVEL = 400;   // Y position representing the ground level

// Path to the zombie spritesheet
extern bool running;

// Number of frames in the zombie walk spritesheet
const int TOTAL_FRAMES_ZOMBIE = 8;
const int FRAMES_PER_ROW_ZOMBIE_WALK = 8;

// Number of frames in the mainguy shoot spritesheet
const int TOTAL_FRAMES_MAIN_GUY = 7;
const int FRAMES_PER_ROW_MAIN_GUY = 7;

// Delay between frames in milliseconds
const int FRAME_DELAY = 100;

#endif // CONSTANTS_HPP
