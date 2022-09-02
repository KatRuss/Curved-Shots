#include "raylib.h"
#include "math.h"
#include <iostream>
const int screenWidth = 960;
const int screenHeight = 540;


float playerX = 400;
float playerY = 200;

float playerAngle;

float mouseX = 0;
float mouseY = 0;

float mouseAngle;

float distanceBetweenPoints = 0;
float midX;
float midY;

bool showTriangle = false;
bool showCircle = false;
bool showOrbit = false;
bool flipDirection = false;


float curveX;
float curveY;
float angle = 0;

//Pythagorean Theroum. hypotenuse for two arbitrary points. Used for distance calculation.  
float dist(float ax, float ay, float bx, float by){
    return (sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}

//Use Sin and Cosine to calculate the location of the shot
void CircleMovement(){
    
    if (flipDirection){angle += 0.01;}
    else              {angle -= 0.01;}
    


    if (angle == mouseAngle)
    {
        showOrbit = false;
    } else {
        if (angle > 2*PI){angle -= 2*PI;}
        if (angle < 0){angle += 2*PI;}
        //Find x,y of shot given its current angle
        curveX = ((distanceBetweenPoints/2)*cos(angle))+midX;
        curveY = ((distanceBetweenPoints/2)*sin(angle))+midY;
        DrawRectangle(curveX,curveY,10,10,DARKGRAY);
    }
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

    //Debug Drawing
    if (IsKeyPressed(KEY_F)){showTriangle = !showTriangle; showCircle = !showCircle;}
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){showOrbit = !showOrbit; angle = playerAngle;}
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){flipDirection = !flipDirection;}
    
}

void CalculateAimingCircle(){
    //Distance Get - diameter of circle = hypotenuse created by player and mouse positions
    distanceBetweenPoints = dist(playerX,playerY,mouseX,mouseY);
    //Midpoint
    midX = (playerX + mouseX)/2;
    midY = (playerY + mouseY)/2;

    //Player Point in Circle
    playerAngle = atan2(playerY-midY,playerX-midX);
    mouseAngle = atan2(mouseY-midY,mouseX-midX);



}

void DrawAimingCircle(){
    //Draw
    DrawCircleLines(midX,midY,distanceBetweenPoints/2,GREEN);
}

void DrawDebugTriangle(){
    //Horz Line
    DrawLine(playerX,playerY,mouseX,playerY,BLACK);
    //Vert Line
    DrawLine(mouseX,mouseY,mouseX,playerY,BLACK);

}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Curved Shots Example");

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        HandleInput();
        CalculateAimingCircle();
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            //Player
            DrawRectangle(playerX,playerY,10,10,RED);
            //Mouse
            DrawRectangle(mouseX,mouseY,10,10,BLUE);

            //Example Triangle
            if (showTriangle){DrawDebugTriangle();}
            
            //Circle
            if (showCircle){DrawLine(playerX,playerY,mouseX,mouseY,PURPLE); DrawAimingCircle();}

            if (showOrbit)
            {
                CircleMovement();
            }
            

            //Tutorial Text
            DrawText("WASD to Move",10,10,18,BLACK);
            DrawText("Left Mouse to Fire",10,25,18,BLACK);
            DrawText("Right Mouse to Flip Direction",10,40,18,BLACK);
            DrawText("F for debug circle",10,55,18,BLACK);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}


