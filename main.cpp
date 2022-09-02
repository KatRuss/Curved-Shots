#include "raylib.h"
#include "math.h"
#include <iostream>
#include <string>

const int screenWidth = 960;
const int screenHeight = 540;


float playerX = 400;
float playerY = 200;
float mouseX = 0;
float mouseY = 0;

float distanceBetweenPoints = 0;
float midX;
float midY;

//Pythagorean Theroum. hypotenuse for two arbitrary points. Used for distance calculation.  
float dist(float ax, float ay, float bx, float by){
    return (sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}


void HandleInput(){
    //Mouse Position
    mouseX = GetMouseX();
    mouseY = GetMouseY();

    //Player Position
    if (IsKeyDown(KEY_W)){playerY-=3;}
    if (IsKeyDown(KEY_S)){playerY+=3;}
    if (IsKeyDown(KEY_A)){playerX-=3;}
    if (IsKeyDown(KEY_D)){playerX+=3;}

}

void DrawAimingCircle(){
    //Distance Get - diameter of circle = hypotenuse created by player and mouse positions
    distanceBetweenPoints = dist(playerX,playerY,mouseX,mouseY);

    //Midpoint
    midX = (playerX + mouseX)/2;
    midY = (playerY + mouseY)/2;

    DrawCircleLines(midX,midY,distanceBetweenPoints/2,GREEN);
}


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Curved Shots Example");

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        HandleInput();
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            //Player
            DrawRectangle(playerX,playerY,10,10,RED);
            //Mouse
            DrawRectangle(mouseX,mouseY,10,10,BLUE);

            DrawLine(playerX,playerY,mouseX,mouseY,PURPLE);

            //Tutorial Text
            DrawText("WASD to Move",10,10,18,BLACK);
            DrawText("Left Mouse to Fire",10,25,18,BLACK);

            DrawAimingCircle();

        EndDrawing();

        std::cout << GetFPS() << std::endl;
    }
    CloseWindow();

    return 0;
}


