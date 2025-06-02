#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"



// Block Breaker Game
// I know the code sucks ass and is probably extremely inneficient but its works well and is fast af.
// Theres a lot of missing parts like a victory and reset scree but its good enough for a first project.



int CenterX = WINDOW_WIDTH/2;
int CenterY = WINDOW_HEIGHT/2;

int DosCenterX = WINDOW_WIDTH/2 + 20;
int DosCenterY = WINDOW_HEIGHT/2 + 20;

//find a way to make DirX's a rand between 3 and -3
int DirectionX = 3;
int DirectionY = 3;

int DosDirectionX = -3;
int DosDirectionY = 3;

int Radius = 9;
int DosRadius = 9;

int Life = 3;
int Score = 0;

bool Running = true;
bool Downward = true;
bool DosBall = false;
bool TextRenew = true;
bool Homescreen = true;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;


struct MainPaddle
{
    int x;
    int y;
    int width;
    int height;
} MainPaddle;

struct Block
{
    int x;
    int y;
    int width;
    int height;
} Block1, Block2, Block3, Block4, Block5, Block6, Block7, Block8, Block9, Block10, Block11, Block12, Block13, Block14, Block15, 
Block16;


int InitializeAll()
{
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "error initializing SDL. \n");
        return false;
    }

    window = SDL_CreateWindow
    (
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if(!window)
    {
        fprintf(stderr, "error creating window\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "error creating renderer\n");
        return false;
    }

    if(!IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG))
    {
        fprintf(stderr, "error initializing image\n");
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }



    return true;
}


void Setup()
{
    MainPaddle.x = WINDOW_WIDTH/2;
    MainPaddle.y = WINDOW_HEIGHT - 20;
    MainPaddle.width = 150;
    MainPaddle.height = 15;

    Block1.x = 0 + 5;
    Block1.y = 0 + 5;
    Block1.width = COLUMN_WIDTH;
    Block1.height = BLOCK_THICKNESS;

    Block2.x = COLUMN_WIDTH + 10;
    Block2.y = 0 + 5;
    Block2.width = COLUMN_WIDTH;
    Block2.height = BLOCK_THICKNESS;

    Block3.x = COLUMN_WIDTH * 2 + 15;
    Block3.y = 0 + 5;
    Block3.width = COLUMN_WIDTH;
    Block3.height = BLOCK_THICKNESS;

    Block4.x = COLUMN_WIDTH * 3 + 20;
    Block4.y = 0 + 5;
    Block4.width = COLUMN_WIDTH - 25;
    Block4.height = BLOCK_THICKNESS;

    //row 2
    Block5.x = 0 + 5;
    Block5.y = BLOCK_THICKNESS + 5 + 5;
    Block5.width = COLUMN_WIDTH;
    Block5.height = BLOCK_THICKNESS;

    Block6.x = COLUMN_WIDTH + 10;
    Block6.y =  BLOCK_THICKNESS + 5 + 5;
    Block6.width = COLUMN_WIDTH;
    Block6.height = BLOCK_THICKNESS;

    Block7.x = COLUMN_WIDTH * 2 + 15;
    Block7.y = BLOCK_THICKNESS + 5 + 5;
    Block7.width = COLUMN_WIDTH;
    Block7.height = BLOCK_THICKNESS;

    Block8.x = COLUMN_WIDTH * 3 + 20;
    Block8.y = BLOCK_THICKNESS + 5 + 5;
    Block8.width = COLUMN_WIDTH - 25;
    Block8.height = BLOCK_THICKNESS; 

    //row 3
    Block9.x = 0 + 5;
    Block9.y = BLOCK_THICKNESS * 2 + 15;
    Block9.width = COLUMN_WIDTH;
    Block9.height = BLOCK_THICKNESS;

    Block10.x = COLUMN_WIDTH + 10;
    Block10.y = BLOCK_THICKNESS * 2+ 15;
    Block10.width = COLUMN_WIDTH;
    Block10.height = BLOCK_THICKNESS;

    Block11.x = COLUMN_WIDTH * 2 + 15;
    Block11.y = BLOCK_THICKNESS * 2 + 15;
    Block11.width = COLUMN_WIDTH;
    Block11.height = BLOCK_THICKNESS;

    Block12.x = COLUMN_WIDTH * 3 + 20;
    Block12.y = BLOCK_THICKNESS * 2 + 15;
    Block12.width = COLUMN_WIDTH - 25;
    Block12.height = BLOCK_THICKNESS;

    //row 4
    Block13.x = 5;
    Block13.y = BLOCK_THICKNESS * 3 + 20;
    Block13.width = COLUMN_WIDTH;
    Block13.height = BLOCK_THICKNESS;

    Block14.x = COLUMN_WIDTH + 10;
    Block14.y = BLOCK_THICKNESS * 3 + 20;
    Block14.width = COLUMN_WIDTH;
    Block14.height = BLOCK_THICKNESS;

    Block15.x = COLUMN_WIDTH * 2 + 15;
    Block15.y = BLOCK_THICKNESS * 3 + 20;
    Block15.width = COLUMN_WIDTH;
    Block15.height = BLOCK_THICKNESS;

    Block16.x = COLUMN_WIDTH * 3 + 20;
    Block16.y = BLOCK_THICKNESS * 3 + 20;
    Block16.width = COLUMN_WIDTH - 25;
    Block16.height = BLOCK_THICKNESS;

 
}


void HomescreenTextUno()
{
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "Welcome to Block Breaker,");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {10, WINDOW_HEIGHT/2 - 45, textWidth, textHeight};


    
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void HomescreenTextDos()
{
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "Use the paddle to keep the ball from touching the ground and to break the blocks.");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {10, WINDOW_HEIGHT/2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);

}


void HomescreenTexTres()
{
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "Press letter S To Continue, Esc to Force Gameover and Exit");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {10, WINDOW_HEIGHT/2 + 45, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);

}


void GameOver()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "Game Over, Score: %d", Score);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT/2, textWidth, textHeight};


    
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void Three()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "3");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, textWidth, textHeight};


    
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void Two()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "2");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, textWidth, textHeight};


    
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void One()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 30);
    SDL_Color textColor = {255, 255, 255, 255};

                char textBuffer[300];
        snprintf(textBuffer, sizeof(textBuffer), "1");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, textWidth, textHeight};


    
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void LifeTextRender()
{
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 20);
    SDL_Color textColor = {0, 12, 31, 255};

                char textBuffer[50];
        snprintf(textBuffer, sizeof(textBuffer), "Life: %d", Life);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {10, WINDOW_HEIGHT - 49, textWidth, textHeight};

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void ScoreTextRender()
{
    TTF_Font *font = TTF_OpenFont("C:/Users/KORMIT2000/Desktop/Coding/Pong/Font/Tomorrow-Regular.ttf", 20);
    SDL_Color textColor = {0, 12, 31, 255};

                char textBuffer[50];
        snprintf(textBuffer, sizeof(textBuffer), "Score: %d", Score);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
                int textWidth = 1, textHeight = 1;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {10, WINDOW_HEIGHT - 70, textWidth, textHeight};

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
}


void ProcessInput()
{
    SDL_Event Events;
    SDL_PollEvent(&Events);

    switch(Events.type)
    {
        case SDL_KEYDOWN: 
            switch(Events.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    Running = false;
                    break;
                case SDLK_d:
                    MainPaddle.x += 20;
                    break;
                case SDLK_a:
                    MainPaddle.x -= 20;
                    break;
                case SDLK_s:
                    Homescreen = false;
                    break;
            }
        break;

    }

}


void DosBallUpdate()
{
    srand(time(NULL));

    DosCenterX += DosDirectionX;
    DosCenterY += DosDirectionY;
  
  //collision for paddle
    int PaddleclosestX = (DosCenterX < MainPaddle.x) ? MainPaddle.x :
                    (DosCenterX > MainPaddle.x + MainPaddle.width) ? MainPaddle.x + MainPaddle.width : DosCenterX;

    int PaddleclosestY = (DosCenterY < MainPaddle.y) ? MainPaddle.y :
                   (DosCenterY > MainPaddle.y + MainPaddle.height) ? MainPaddle.y + MainPaddle.height : DosCenterY;
    
    int dxPaddle = DosCenterX - PaddleclosestX;
    int dyPaddle = DosCenterY - PaddleclosestY;

  //collision for every block in the game 
    int Block1closestX = (DosCenterX < Block1.x) ? Block1.x :
                    (DosCenterX > Block1.x + Block1.width) ? Block1.x + Block1.width : DosCenterX;

    int Block1closestY = (DosCenterY < Block1.y) ? Block1.y :
                   (DosCenterY > Block1.y + Block1.height) ? Block1.y + Block1.height : DosCenterY;

    int dxBlock1 = DosCenterX - Block1closestX;
    int dyBlock1 = DosCenterY - Block1closestY;


    int Block2closestX = (DosCenterX < Block2.x) ? Block2.x :
                    (DosCenterX > Block2.x + Block2.width) ? Block2.x + Block2.width : DosCenterX;

    int Block2closestY = (DosCenterY < Block2.y) ? Block2.y :
                   (DosCenterY > Block2.y + Block2.height) ? Block2.y + Block2.height : DosCenterY;

    int dxBlock2 = DosCenterX - Block2closestX;
    int dyBlock2 = DosCenterY - Block2closestY;


    int Block3closestX = (DosCenterX < Block3.x) ? Block3.x :
                    (DosCenterX > Block3.x + Block3.width) ? Block3.x + Block3.width : DosCenterX;

    int Block3closestY = (DosCenterY < Block3.y) ? Block3.y :
                   (DosCenterY > Block3.y + Block3.height) ? Block3.y + Block3.height : DosCenterY;

    int dxBlock3 = DosCenterX - Block3closestX;
    int dyBlock3 = DosCenterY - Block3closestY;


    int Block4closestX = (DosCenterX < Block4.x) ? Block4.x :
                    (DosCenterX > Block4.x + Block4.width) ? Block4.x + Block4.width : DosCenterX;

    int Block4closestY = (DosCenterY < Block4.y) ? Block4.y :
                   (DosCenterY > Block4.y + Block4.height) ? Block4.y + Block4.height : DosCenterY;

    int dxBlock4 = DosCenterX - Block4closestX;
    int dyBlock4 = DosCenterY - Block4closestY;


    int Block5closestX = (DosCenterX < Block5.x) ? Block5.x :
                    (DosCenterX > Block5.x + Block5.width) ? Block5.x + Block5.width : DosCenterX;

    int Block5closestY = (DosCenterY < Block5.y) ? Block5.y :
                   (DosCenterY > Block5.y + Block5.height) ? Block5.y + Block5.height : DosCenterY;

    int dxBlock5 = DosCenterX - Block5closestX;
    int dyBlock5 = DosCenterY - Block5closestY;


    int Block6closestX = (DosCenterX < Block6.x) ? Block6.x :
                    (DosCenterX > Block6.x + Block6.width) ? Block6.x + Block6.width : DosCenterX;

    int Block6closestY = (DosCenterY < Block6.y) ? Block6.y :
                   (DosCenterY > Block6.y + Block6.height) ? Block6.y + Block6.height : DosCenterY;

    int dxBlock6 = DosCenterX - Block6closestX;
    int dyBlock6 = DosCenterY - Block6closestY;


    int Block7closestX = (DosCenterX < Block7.x) ? Block7.x :
                    (DosCenterX > Block7.x + Block7.width) ? Block7.x + Block7.width : DosCenterX;

    int Block7closestY = (DosCenterY < Block7.y) ? Block7.y :
                   (DosCenterY > Block7.y + Block7.height) ? Block7.y + Block7.height : DosCenterY;

    int dxBlock7 = DosCenterX - Block7closestX;
    int dyBlock7 = DosCenterY - Block7closestY;


    int Block8closestX = (DosCenterX < Block8.x) ? Block8.x :
                    (DosCenterX > Block8.x + Block8.width) ? Block8.x + Block8.width : DosCenterX;

    int Block8closestY = (DosCenterY < Block8.y) ? Block8.y :
                   (DosCenterY > Block8.y + Block8.height) ? Block8.y + Block8.height : DosCenterY;

    int dxBlock8 = DosCenterX - Block8closestX;
    int dyBlock8 = DosCenterY - Block8closestY;


    int Block9closestX = (DosCenterX < Block9.x) ? Block9.x :
                    (DosCenterX > Block9.x + Block9.width) ? Block9.x + Block9.width : DosCenterX;

    int Block9closestY = (DosCenterY < Block9.y) ? Block9.y :
                   (DosCenterY > Block9.y + Block9.height) ? Block9.y + Block9.height : DosCenterY;

    int dxBlock9 = DosCenterX - Block9closestX;
    int dyBlock9 = DosCenterY - Block9closestY;


    int Block10closestX = (DosCenterX < Block10.x) ? Block10.x :
                    (DosCenterX > Block10.x + Block10.width) ? Block10.x + Block10.width : DosCenterX;

    int Block10closestY = (DosCenterY < Block10.y) ? Block10.y :
                   (DosCenterY > Block10.y + Block10.height) ? Block10.y + Block10.height : DosCenterY;

    int dxBlock10 = DosCenterX - Block10closestX;
    int dyBlock10 = DosCenterY - Block10closestY;


    int Block11closestX = (DosCenterX < Block11.x) ? Block11.x :
                    (DosCenterX > Block11.x + Block11.width) ? Block11.x + Block11.width : DosCenterX;

    int Block11closestY = (DosCenterY < Block11.y) ? Block11.y :
                   (DosCenterY > Block11.y + Block11.height) ? Block11.y + Block11.height : DosCenterY;

    int dxBlock11 = DosCenterX - Block11closestX;
    int dyBlock11 = DosCenterY - Block11closestY;


    int Block12closestX = (DosCenterX < Block12.x) ? Block12.x :
                    (DosCenterX > Block12.x + Block12.width) ? Block12.x + Block12.width : DosCenterX;

    int Block12closestY = (DosCenterY < Block12.y) ? Block12.y :
                   (DosCenterY > Block12.y + Block12.height) ? Block12.y + Block12.height : DosCenterY;

    int dxBlock12 = DosCenterX - Block12closestX;
    int dyBlock12 = DosCenterY - Block12closestY;


    int Block13closestX = (DosCenterX < Block13.x) ? Block13.x :
                    (DosCenterX > Block13.x + Block13.width) ? Block13.x + Block13.width : DosCenterX;

    int Block13closestY = (DosCenterY < Block13.y) ? Block13.y :
                   (DosCenterY > Block13.y + Block13.height) ? Block13.y + Block13.height : DosCenterY;

    int dxBlock13 = DosCenterX - Block13closestX;
    int dyBlock13 = DosCenterY - Block13closestY;


    int Block14closestX = (DosCenterX < Block14.x) ? Block14.x :
                    (DosCenterX > Block14.x + Block14.width) ? Block14.x + Block14.width : DosCenterX;

    int Block14closestY = (DosCenterY < Block14.y) ? Block14.y :
                   (DosCenterY > Block14.y + Block14.height) ? Block14.y + Block14.height : DosCenterY;

    int dxBlock14 = DosCenterX - Block14closestX;
    int dyBlock14 = DosCenterY - Block14closestY;


    int Block15closestX = (DosCenterX < Block15.x) ? Block15.x :
                    (DosCenterX > Block15.x + Block15.width) ? Block15.x + Block15.width : DosCenterX;

    int Block15closestY = (DosCenterY < Block15.y) ? Block15.y :
                   (DosCenterY > Block15.y + Block15.height) ? Block15.y + Block15.height : DosCenterY;

    int dxBlock15 = DosCenterX - Block15closestX;
    int dyBlock15 = DosCenterY - Block15closestY;


    int Block16closestX = (DosCenterX < Block16.x) ? Block16.x :
                    (DosCenterX > Block16.x + Block15.width) ? Block16.x + Block16.width : DosCenterX;

    int Block16closestY = (DosCenterY < Block16.y) ? Block16.y :
                   (DosCenterY > Block16.y + Block16.height) ? Block16.y + Block16.height : DosCenterY;

    int dxBlock16 = DosCenterX - Block16closestX;
    int dyBlock16 = DosCenterY - Block16closestY;

    // wall collisions
    if((DosCenterX + 9) * (DosCenterX + 9) >= (WINDOW_WIDTH * WINDOW_WIDTH))
    {
        DosDirectionX = -DosDirectionX;  
    }  

    if((DosCenterX - 9) * (DosCenterX - 9) <= (1))
    {
        DosDirectionX = -DosDirectionX;  
    }  

    if((DosCenterY - 9) * (DosCenterY - 9) <= (1))
    {
        DosDirectionY = -DosDirectionY;  
    } 

    if((DosCenterY + 9) * (DosCenterY + 9) >= (WINDOW_HEIGHT * WINDOW_HEIGHT))
    {
        Life -= 1;
        Score -= 100;
        DosCenterY = WINDOW_HEIGHT/2;
        //TextRender();
    } 

    if((dxPaddle * dxPaddle + dyPaddle * dyPaddle) <= (DosRadius * DosRadius))
    {
        DosDirectionY = -DosDirectionY;
        DosDirectionX = (rand() % 7) - 3;
    }   

    if((dxBlock1 * dxBlock1 + dyBlock1 * dyBlock1) <= (DosRadius * DosRadius))
    {
        Block1.x = 1300;  
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }  

    if((dxBlock2 * dxBlock2 + dyBlock2 * dyBlock2) <= (DosRadius * DosRadius))
    {
        Block2.x = 1300;
        DosDirectionY = -DosDirectionY;
        Score += 50;
    } 

    if((dxBlock3 * dxBlock3 + dyBlock3 * dyBlock3) <= (DosRadius * DosRadius))
    {
        Block3.x = 1300;  
        DosDirectionY = -DosDirectionY;
        Score += 50;
    } 

    if((dxBlock4 * dxBlock4 + dyBlock4 * dyBlock4) <= (DosRadius * DosRadius))
    {
        Block4.x = 1300;  
        DosDirectionY = -DosDirectionY;
        Score += 50;
    } 

    if((dxBlock5 * dxBlock5 + dyBlock5 * dyBlock5) <= (DosRadius * DosRadius))
    {
        Block5.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock6 * dxBlock6 + dyBlock6 * dyBlock6) <= (DosRadius * DosRadius))
    {
        Block6.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock7 * dxBlock7 + dyBlock7 * dyBlock7) <= (DosRadius * DosRadius))
    {
        Block7.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock8 * dxBlock8 + dyBlock8 * dyBlock8) <= (DosRadius * DosRadius))
    {
        Block8.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock9 * dxBlock9 + dyBlock9 * dyBlock9) <= (DosRadius * DosRadius))
    {
        Block9.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock10 * dxBlock10 + dyBlock10 * dyBlock10) <= (DosRadius * DosRadius))
    {
        Block10.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock11 * dxBlock11 + dyBlock11 * dyBlock11) <= (DosRadius * DosRadius))
    {
        Block11.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock12 * dxBlock12 + dyBlock12 * dyBlock12) <= (DosRadius * DosRadius))
    {
        Block12.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock13 * dxBlock13 + dyBlock13 * dyBlock13) <= (DosRadius * DosRadius))
    {
        Block13.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock14 * dxBlock14 + dyBlock14 * dyBlock14) <= (DosRadius * DosRadius))
    {
        Block14.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }
    
    if((dxBlock15 * dxBlock15 + dyBlock15 * dyBlock15) <= (DosRadius * DosRadius))
    {
        Block15.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

    if((dxBlock16 * dxBlock16 + dyBlock16 * dyBlock16) <= (DosRadius * DosRadius))
    {
        Block16.x = 1300; 
        DosDirectionY = -DosDirectionY;
        Score += 50;
    }

}


void Update()
{
    srand(time(NULL));

    CenterX += DirectionX;
    CenterY += DirectionY;


    if(Life <= 0)
    {
        Running = false;
    }
  
  //collision for paddle
    int PaddleclosestX = (CenterX < MainPaddle.x) ? MainPaddle.x :
                    (CenterX > MainPaddle.x + MainPaddle.width) ? MainPaddle.x + MainPaddle.width : CenterX;

    int PaddleclosestY = (CenterY < MainPaddle.y) ? MainPaddle.y :
                   (CenterY > MainPaddle.y + MainPaddle.height) ? MainPaddle.y + MainPaddle.height : CenterY;

// dx, dy = distance between the ball and other object
    int dxPaddle = CenterX - PaddleclosestX;
    int dyPaddle = CenterY - PaddleclosestY;

// collision for every block in the game
    int Block1closestX = (CenterX < Block1.x) ? Block1.x :
                    (CenterX > Block1.x + Block1.width) ? Block1.x + Block1.width : CenterX;

    int Block1closestY = (CenterY < Block1.y) ? Block1.y :
                   (CenterY > Block1.y + Block1.height) ? Block1.y + Block1.height : CenterY;

    int dxBlock1 = CenterX - Block1closestX;
    int dyBlock1 = CenterY - Block1closestY;


    int Block2closestX = (CenterX < Block2.x) ? Block2.x :
                    (CenterX > Block2.x + Block2.width) ? Block2.x + Block2.width : CenterX;

    int Block2closestY = (CenterY < Block2.y) ? Block2.y :
                   (CenterY > Block2.y + Block2.height) ? Block2.y + Block2.height : CenterY;

    int dxBlock2 = CenterX - Block2closestX;
    int dyBlock2 = CenterY - Block2closestY;


    int Block3closestX = (CenterX < Block3.x) ? Block3.x :
                    (CenterX > Block3.x + Block3.width) ? Block3.x + Block3.width : CenterX;

    int Block3closestY = (CenterY < Block3.y) ? Block3.y :
                   (CenterY > Block3.y + Block3.height) ? Block3.y + Block3.height : CenterY;

    int dxBlock3 = CenterX - Block3closestX;
    int dyBlock3 = CenterY - Block3closestY;


    int Block4closestX = (CenterX < Block4.x) ? Block4.x :
                    (CenterX > Block4.x + Block4.width) ? Block4.x + Block4.width : CenterX;

    int Block4closestY = (CenterY < Block4.y) ? Block4.y :
                   (CenterY > Block4.y + Block4.height) ? Block4.y + Block4.height : CenterY;

    int dxBlock4 = CenterX - Block4closestX;
    int dyBlock4 = CenterY - Block4closestY;


    int Block5closestX = (CenterX < Block5.x) ? Block5.x :
                    (CenterX > Block5.x + Block5.width) ? Block5.x + Block5.width : CenterX;

    int Block5closestY = (CenterY < Block5.y) ? Block5.y :
                   (CenterY > Block5.y + Block5.height) ? Block5.y + Block5.height : CenterY;

    int dxBlock5 = CenterX - Block5closestX;
    int dyBlock5 = CenterY - Block5closestY;


    int Block6closestX = (CenterX < Block6.x) ? Block6.x :
                    (CenterX > Block6.x + Block6.width) ? Block6.x + Block6.width : CenterX;

    int Block6closestY = (CenterY < Block6.y) ? Block6.y :
                   (CenterY > Block6.y + Block6.height) ? Block6.y + Block6.height : CenterY;

    int dxBlock6 = CenterX - Block6closestX;
    int dyBlock6 = CenterY - Block6closestY;


    int Block7closestX = (CenterX < Block7.x) ? Block7.x :
                    (CenterX > Block7.x + Block7.width) ? Block7.x + Block7.width : CenterX;

    int Block7closestY = (CenterY < Block7.y) ? Block7.y :
                   (CenterY > Block7.y + Block7.height) ? Block7.y + Block7.height : CenterY;

    int dxBlock7 = CenterX - Block7closestX;
    int dyBlock7 = CenterY - Block7closestY;


    int Block8closestX = (CenterX < Block8.x) ? Block8.x :
                    (CenterX > Block8.x + Block8.width) ? Block8.x + Block8.width : CenterX;

    int Block8closestY = (CenterY < Block8.y) ? Block8.y :
                   (CenterY > Block8.y + Block8.height) ? Block8.y + Block8.height : CenterY;

    int dxBlock8 = CenterX - Block8closestX;
    int dyBlock8 = CenterY - Block8closestY;


    int Block9closestX = (CenterX < Block9.x) ? Block9.x :
                    (CenterX > Block9.x + Block9.width) ? Block9.x + Block9.width : CenterX;

    int Block9closestY = (CenterY < Block9.y) ? Block9.y :
                   (CenterY > Block9.y + Block9.height) ? Block9.y + Block9.height : CenterY;

    int dxBlock9 = CenterX - Block9closestX;
    int dyBlock9 = CenterY - Block9closestY;


    int Block10closestX = (CenterX < Block10.x) ? Block10.x :
                    (CenterX > Block10.x + Block10.width) ? Block10.x + Block10.width : CenterX;

    int Block10closestY = (CenterY < Block10.y) ? Block10.y :
                   (CenterY > Block10.y + Block10.height) ? Block10.y + Block10.height : CenterY;

    int dxBlock10 = CenterX - Block10closestX;
    int dyBlock10 = CenterY - Block10closestY;


    int Block11closestX = (CenterX < Block11.x) ? Block11.x :
                    (CenterX > Block11.x + Block11.width) ? Block11.x + Block11.width : CenterX;

    int Block11closestY = (CenterY < Block11.y) ? Block11.y :
                   (CenterY > Block11.y + Block11.height) ? Block11.y + Block11.height : CenterY;

    int dxBlock11 = CenterX - Block11closestX;
    int dyBlock11 = CenterY - Block11closestY;


    int Block12closestX = (CenterX < Block12.x) ? Block12.x :
                    (CenterX > Block12.x + Block12.width) ? Block12.x + Block12.width : CenterX;

    int Block12closestY = (CenterY < Block12.y) ? Block12.y :
                   (CenterY > Block12.y + Block12.height) ? Block12.y + Block12.height : CenterY;

    int dxBlock12 = CenterX - Block12closestX;
    int dyBlock12 = CenterY - Block12closestY;


    int Block13closestX = (CenterX < Block13.x) ? Block13.x :
                    (CenterX > Block13.x + Block13.width) ? Block13.x + Block13.width : CenterX;

    int Block13closestY = (CenterY < Block13.y) ? Block13.y :
                   (CenterY > Block13.y + Block13.height) ? Block13.y + Block13.height : CenterY;

    int dxBlock13 = CenterX - Block13closestX;
    int dyBlock13 = CenterY - Block13closestY;


    int Block14closestX = (CenterX < Block14.x) ? Block14.x :
                    (CenterX > Block14.x + Block14.width) ? Block14.x + Block14.width : CenterX;

    int Block14closestY = (CenterY < Block14.y) ? Block14.y :
                   (CenterY > Block14.y + Block14.height) ? Block14.y + Block14.height : CenterY;

    int dxBlock14 = CenterX - Block14closestX;
    int dyBlock14 = CenterY - Block14closestY;


    int Block15closestX = (CenterX < Block15.x) ? Block15.x :
                    (CenterX > Block15.x + Block15.width) ? Block15.x + Block15.width : CenterX;

    int Block15closestY = (CenterY < Block15.y) ? Block15.y :
                   (CenterY > Block15.y + Block15.height) ? Block15.y + Block15.height : CenterY;

    int dxBlock15 = CenterX - Block15closestX;
    int dyBlock15 = CenterY - Block15closestY;


    int Block16closestX = (CenterX < Block16.x) ? Block16.x :
                    (CenterX > Block16.x + Block15.width) ? Block16.x + Block16.width : CenterX;

    int Block16closestY = (CenterY < Block16.y) ? Block16.y :
                   (CenterY > Block16.y + Block16.height) ? Block16.y + Block16.height : CenterY;

    int dxBlock16 = CenterX - Block16closestX;
    int dyBlock16 = CenterY - Block16closestY;

//Paddle wall collisions
if(MainPaddle.x <= 0)
{
    MainPaddle.x += 50;
}

if(MainPaddle.x + MainPaddle.width >= WINDOW_WIDTH)
{
    MainPaddle.x -= 50;
}

// wall collisions
    if((CenterX + 9) * (CenterX + 9) >= (WINDOW_WIDTH * WINDOW_WIDTH))
    {
        DirectionX = -DirectionX;  
    }  

    if((CenterX - 9) * (CenterX - 9) <= (1))
    {
        DirectionX = -DirectionX;  
    }  

    if((CenterY - 9) * (CenterY - 9) <= (1))
    {
        DirectionY = -DirectionY;  
    } 

    if((CenterY + 9) * (CenterY + 9) >= (WINDOW_HEIGHT * WINDOW_HEIGHT))
    {
        Life -= 1;
        Score -= 100;
        CenterY = WINDOW_HEIGHT/2;
        //TextRender();
    }

//Collision checks and returns

//Return true if the distance is less than or equal to the radius, it means there's a collision
//Needs to be squared cuz not squaring will give us "manhattan taxi cab distance" i.e. deviously overshot, inaccurate distance
//Squaring brings it closer to the actual mathematical formula for euclidian distance.
    if((dxPaddle * dxPaddle + dyPaddle * dyPaddle) <= (Radius * Radius))
    {
        DirectionY = -DirectionY;
        DirectionX = (rand() % 7) - 3;  
    }   

    if((dxBlock1 * dxBlock1 + dyBlock1 * dyBlock1) <= (Radius * Radius))
    {
        Block1.x = 1300;  
        DirectionY = -DirectionY;
        Score += 50;
    }  

    if((dxBlock2 * dxBlock2 + dyBlock2 * dyBlock2) <= (Radius * Radius))
    {
        Block2.x = 1300;
        DirectionY = -DirectionY;
        Score += 50;
    } 

    if((dxBlock3 * dxBlock3 + dyBlock3 * dyBlock3) <= (Radius * Radius))
    {
        Block3.x = 1300;  
        DirectionY = -DirectionY;
        Score += 50;
    } 

    if((dxBlock4 * dxBlock4 + dyBlock4 * dyBlock4) <= (Radius * Radius))
    {
        Block4.x = 1300;  
        DirectionY = -DirectionY;
        Score += 50;
        MainPaddle.width = 50;
        
    } 

    if((dxBlock5 * dxBlock5 + dyBlock5 * dyBlock5) <= (Radius * Radius))
    {
        Block5.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock6 * dxBlock6 + dyBlock6 * dyBlock6) <= (Radius * Radius))
    {
        Block6.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock7 * dxBlock7 + dyBlock7 * dyBlock7) <= (Radius * Radius))
    {
        Block7.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock8 * dxBlock8 + dyBlock8 * dyBlock8) <= (Radius * Radius))
    {
        Block8.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock9 * dxBlock9 + dyBlock9 * dyBlock9) <= (Radius * Radius))
    {
        Block9.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock10 * dxBlock10 + dyBlock10 * dyBlock10) <= (Radius * Radius))
    {
        Block10.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock11 * dxBlock11 + dyBlock11 * dyBlock11) <= (Radius * Radius))
    {
        Block11.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
        DosBall = true;
    }

    if((dxBlock12 * dxBlock12 + dyBlock12 * dyBlock12) <= (Radius * Radius))
    {
        Block12.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock13 * dxBlock13 + dyBlock13 * dyBlock13) <= (Radius * Radius))
    {
        Block13.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock14 * dxBlock14 + dyBlock14 * dyBlock14) <= (Radius * Radius))
    {
        Block14.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }
    
    if((dxBlock15 * dxBlock15 + dyBlock15 * dyBlock15) <= (Radius * Radius))
    {
        Block15.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

    if((dxBlock16 * dxBlock16 + dyBlock16 * dyBlock16) <= (Radius * Radius))
    {
        Block16.x = 1300; 
        DirectionY = -DirectionY;
        Score += 50;
    }

}


void Render(SDL_Texture *ImgTexture, int CenterX, int CenterY, int Radius)
{
 
    SDL_Rect PaddleMain = 
    {
        MainPaddle.x,
        MainPaddle.y,
        MainPaddle.width,
        MainPaddle.height
    };

    SDL_Rect Block_1 =
    {
        Block1.x,
        Block1.y,
        Block1.width,
        Block1.height
    };

    SDL_Rect Block_2 =
    {
        Block2.x,
        Block2.y,
        Block2.width,
        Block2.height
    };

    SDL_Rect Block_3 =
    {
        Block3.x,
        Block3.y,
        Block3.width,
        Block3.height
    };

    SDL_Rect Block_4 = 
    {
        Block4.x,
        Block4.y,
        Block4.width,
        Block4.height
    };

    SDL_Rect Block_5 =
    {
        Block5.x,
        Block5.y,
        Block5.width,
        Block5.height
    };

    SDL_Rect Block_6 = 
    {
        Block6.x,
        Block6.y,
        Block6.width,
        Block6.height
    };

    SDL_Rect Block_7 =
    {
        Block7.x,
        Block7.y,
        Block7.width,
        Block7.height
    };

    SDL_Rect Block_8 = 
    {
        Block8.x,
        Block8.y,
        Block8.width,
        Block8.height
    };

    SDL_Rect Block_9 = 
    {
        Block9.x,
        Block9.y,
        Block9.width,
        Block9.height
    };

    SDL_Rect Block_10 = 
    {
        Block10.x,
        Block10.y,
        Block10.width,
        Block10.height
    };

    SDL_Rect Block_11 = 
    {
        Block11.x,
        Block11.y,
        Block11.width,
        Block11.height
    };

    SDL_Rect Block_12 = 
    {
        Block12.x,
        Block12.y,
        Block12.width,
        Block12.height
    };

    SDL_Rect Block_13 = 
    {
        Block13.x,
        Block13.y,
        Block13.width,
        Block13.height
    };

    SDL_Rect Block_14 = 
    {
        Block14.x,
        Block14.y,
        Block14.width,
        Block14.height
    };

    SDL_Rect Block_15 = 
    {
        Block15.x,
        Block15.y,
        Block15.width,
        Block15.height
    };

    SDL_Rect Block_16 = 
    {
        Block16.x,
        Block16.y,
        Block16.width,
        Block16.height
    };
 
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, ImgTexture, NULL, NULL);
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_SetRenderDrawColor(renderer, 0, 12, 31, 255);


    int x = 0;
    int y = Radius;
    int p = 1 - Radius;

    while (x <= y) {
        // For each y-level, draw horizontal lines between symmetric points
        // Figure This Shi Out
        for (int i = CenterX - x; i <= CenterX + x; i++) {
            SDL_RenderDrawPoint(renderer, i, CenterY + y);
            SDL_RenderDrawPoint(renderer, i, CenterY - y);
        }
        for (int i = CenterX - y; i <= CenterX + y; i++) {
            SDL_RenderDrawPoint(renderer, i, CenterY + x);
            SDL_RenderDrawPoint(renderer, i, CenterY - x);
        }

        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }

    if(DosBall)
    {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    int x = 0;
    int y = Radius;
    int p = 1 - Radius;

    while (x <= y) {
        // For each y-level, draw horizontal lines between symmetric points
        // Figure This Shi Out
        for (int i = DosCenterX - x; i <= DosCenterX + x; i++) {
            SDL_RenderDrawPoint(renderer, i, DosCenterY + y);
            SDL_RenderDrawPoint(renderer, i, DosCenterY - y);
        }
        for (int i = DosCenterX - y; i <= DosCenterX + y; i++) {
            SDL_RenderDrawPoint(renderer, i, DosCenterY + x);
            SDL_RenderDrawPoint(renderer, i, DosCenterY - x);
        }

        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
    }


    SDL_SetRenderDrawColor(renderer, 0, 12, 31, 255);
    SDL_RenderFillRect(renderer, &PaddleMain);

    SDL_SetRenderDrawColor(renderer, 0, 12, 31, 255);
    SDL_RenderFillRect(renderer, &Block_1);
    SDL_RenderFillRect(renderer, &Block_2);
    SDL_RenderFillRect(renderer, &Block_3);
    SDL_RenderFillRect(renderer, &Block_4);
    SDL_RenderFillRect(renderer, &Block_5);
    SDL_RenderFillRect(renderer, &Block_6);
    SDL_RenderFillRect(renderer, &Block_7);
    SDL_RenderFillRect(renderer, &Block_8);
    SDL_RenderFillRect(renderer, &Block_9);
    SDL_RenderFillRect(renderer, &Block_10);
    SDL_RenderFillRect(renderer, &Block_11);
    SDL_RenderFillRect(renderer, &Block_12);
    SDL_RenderFillRect(renderer, &Block_13);
    SDL_RenderFillRect(renderer, &Block_14);
    SDL_RenderFillRect(renderer, &Block_15);
    SDL_RenderFillRect(renderer, &Block_16);

    SDL_RenderPresent(renderer);
}


int WinMain(int argc, char *args[])
{
    Running = InitializeAll();
    Setup();

      SDL_Surface * ImgSurface = IMG_Load("C:/Users/KORMIT2000/Desktop/Coding/Block Breaker/Clouds.png");
    if(!ImgSurface)
    {
        fprintf(stderr, "the imgsurface is buggin\n");
    }

    SDL_Texture * ImgTexture = SDL_CreateTextureFromSurface(renderer, ImgSurface);
    SDL_FreeSurface(ImgSurface);
    if(!ImgTexture)
    {
        fprintf(stderr, "the imgtexture is buggin\n");
    }

    while(Homescreen)
    {
        ProcessInput();
        HomescreenTextUno();
        HomescreenTextDos();
        HomescreenTexTres();
        SDL_Delay(16);
    }

    Three();
    SDL_Delay(1000);
    Two();
    SDL_Delay(1000);
    One();
    SDL_Delay(1000);

    while(Running)
    {
        ProcessInput();
        Update();
        if(DosBall)
        {
            DosBallUpdate();
        }
        Render(ImgTexture, CenterX, CenterY, Radius);
        LifeTextRender();
        ScoreTextRender();
        SDL_Delay(16);
    } 

    GameOver();
    SDL_Delay(2000);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}




