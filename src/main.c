#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct player {
    float x;
    float y;
    float width;
    float height;
} player;

struct pong_ball {
    float x;
    float y;
    float width;
    float height;
} pong_ball;

struct robot {
    float x;
    float y;
    float width;
    float height;
    int direction;
} robot;


int initialize_window(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL. \n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
        );
    if(!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    game_is_running = FALSE;
                    break;
                case SDLK_UP:
                    player.y -= 10;
                    break;
                case SDLK_DOWN:
                    player.y += 10;
                    break;
                case SDLK_LEFT:
                    player.x -= 10;
                    break;
                case SDLK_RIGHT:
                    player.x += 10;
                    break;
            }
            break;
    }
}

void setup() {
    player.x = 10;
    player.y = 10;
    player.width = 15;
    player.height = 30;

    pong_ball.x = 400;
    pong_ball.y = 500;
    pong_ball.width = 25;
    pong_ball.height = 25;

    robot.x = WINDOW_WIDTH - 20;
    robot.y = 30;
    robot.width = 15;
    robot.height = 30;
    robot.direction = 1;
}

void update() {

    //inefficent way
    //while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
 
    last_frame_time = SDL_GetTicks();
    player.x += 0.1 * delta_time;
    player.y += 0.1 * delta_time;
    
    if (robot.y <= 0) {
        robot.direction = 1;  // Moving down
    } else if (robot.y >= WINDOW_HEIGHT - robot.height) {
        robot.direction = -1; // Moving up
    }

    if (robot.direction == 1) {
        robot.y += 70 * delta_time;  // Move down
    } else {
        robot.y -= 70 * delta_time;   // Move up
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player1 = {
        (int)player.x, 
        (int)player.y, 
        (int)player.width, 
        (int)player.height
    };
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &player1);

    SDL_Rect pong_ball_movement =  {
        (int)pong_ball.x, 
        (int)pong_ball.y, 
        (int)pong_ball.width, 
        (int)pong_ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_RenderFillRect(renderer, &pong_ball_movement);

    SDL_Rect bot_movment = {
        (int)robot.x, 
        (int)robot.y, 
        (int)robot.width, 
        (int)robot.height
    };
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &bot_movment);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main() {
    
    game_is_running = initialize_window();

    setup();

    while(game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}