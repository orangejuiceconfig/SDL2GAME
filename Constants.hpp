#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// GANGSTER sprite details

#define GANGSTER_SPEED 1
#define GANGSTER_SCALE 2
#define GANGSTER_WIDTH 128  // Width of each frame
#define GANGSTER_HEIGHT 128 // Height of each frame
#define GANGSTER_HEALTH 9 // Height of each frame

// MainGuy sprite details
#define MAIN_GUY_WIDTH 128 
#define MAIN_GUY_HEIGHT 128
#define MAIN_GUY_SPEED 4
#define MAIN_GUY_SCALE 2

#define GANGSTER_SKIN "/home/usr/2d game/sprites/Gangsters_2/Walk.png" 
#define BACKGROUND1 "/home/usr/2d game/sprites/BackgroundPixel.bmp"
#define FRAME_RATE 60

// Gravity and Jump constants
const float GRAVITY = 0.5f;     // Gravity applied to the main guy
const float JUMP_FORCE = -12.0f; // Initial velocity when jumping
const int GROUND_LEVEL = 400;   // Y position representing the ground level

const float NORMAL_SPEED = 5.0f;
const float SPRINT_SPEED = 8.0f;
// Path to the GANGSTER spritesheet
extern bool running;

// Number of frames in the GANGSTER walk spritesheet
const int TOTAL_FRAMES_GANGSTER = 10;
const int FRAMES_PER_ROW_GANGSTER_WALK = 10;

// Number of frames in the mainguy shoot spritesheet
const int TOTAL_FRAMES_MAIN_GUY = 7;
const int FRAMES_PER_ROW_MAIN_GUY = 7;

// Delay between frames in milliseconds
const int FRAME_DELAY = 100;
const Uint32 SHOOTING_DELAY = 625; // Delay in milliseconds

#endif // CONSTANTS_HPP
