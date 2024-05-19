#include "game.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

Game::Game() {
    this->init(false);
}

Game::~Game() {}

void Game::init(bool fullscreen) {
    int retVal = std::numeric_limits<int>::min();
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (0 == SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(GameConstants::title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GameConstants::width,
            GameConstants::height,
            SDL_WINDOW_SHOWN);
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        {
            SDL_Surface *tmpSurface = IMG_Load("../resources/spritesheets/at-rest-facing-right-x720-y512-per-frame.png");
            cowRestTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);

            tmpSurface = IMG_Load("../resources/cowspritesheetx=720pxY=512px.png");
            cowMovingTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);
        }
    } else {
        std::cerr << SDL_GetError() << std::endl;
        isGameRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isGameRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {

}

void Game::render() {
    SDL_RenderClear(renderer);
    //here we add stuff for rendering
    SDL_RenderCopy(renderer, cowRestTexture, nullptr, nullptr);
    //end
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::gameRunning() {
    return isGameRunning;
}