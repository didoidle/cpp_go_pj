#include <GL/glut.h>
#include <GL/GLU.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "DrawGL.h"
#include "OperateGL.h"
#include "RigidCircle.h"

using namespace std;

bool init = true, restart = true;
float mat[15][15][3];
int turn = 0;
int pX, pY;
int directX, directY;

DrawGL dg; OperateGL og; 

void direct(int x, int y)
{
    directX = x;
    directY = y;
}

void gameOverEvent() {

    int circleCount = 0, maxCount = 0;

    dg.glDrawStone(mat);

    glFlush();

    Sleep(3000);

    glClear(GL_COLOR_BUFFER_BIT);

    RigidCircle* CC = new RigidCircle[255];

    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            if (mat[y][x][2] != 0) {

                CC[circleCount] = RigidCircle(mat[y][x][0], mat[y][x][1],
                    mat[pY][pX][0], mat[pY][pX][1],
                    0.03f, mat[y][x][2], 0.1);

                circleCount++;
                maxCount = circleCount;
            }
        }
    circleCount = 0;

    for (int i = 0; i < 100; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        dg.glDrawScale();
        dg.glDrawLine();

        while (circleCount < maxCount)
        {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glScalef(2.0, 2.0, 0);
            glTranslatef(-0.47, -0.47, 0);
            glTranslatef(CC[circleCount].x, CC[circleCount].y, 0);

            dg.glDrawCircle(CC[circleCount].clr);

            glEnd();
            glPopMatrix();

            CC[circleCount].update();
            circleCount++;
            Sleep(1);
        }

        glFlush();
        circleCount = 0;
    }
    restart = 1;

    delete[] CC;
}

void checkOver(int xPos, int yPos, int color)
{ 

    int count[8] = { 0, }; 

    for (int i = 0; i < 8; i++)
    {
        int x = xPos;
        int y = yPos;

        while (0 <= x && x <= 14 && 0 <= y && y <= 14)
        {

            switch (i)
            {
            case 0:
                direct(-1, -1); 
                break;
            case 1:
                direct(0, -1); 
                break;
            case 2:
                direct(1, -1);
                break;
            case 3:
                direct(1, 0);
                break;
            case 4:
                direct(1, 1);
                break;
            case 5:
                direct(0, 1);
                break;
            case 6:
                direct(-1, 1);
                break;
            case 7:
                direct(-1, 0);
                break;
            default:
                break;
            }

            x = x + directX;
            y = y + directY;

            if (x >= 0 && y >= 0 && x <= 14 && y <= 14) {

                if (mat[y][x][2] == color)
                {
                    count[i]++;
                }
                else
                    break;
            }
            else
                break;

        }

        if ((count[0] + count[4]) == 4) {
            gameOverEvent();
            cout << (color == 1 ? "BLACK WIN" : "WHITE WIN") << endl;
            break;
        }
        else if ((count[1] + count[5]) == 4) {
            gameOverEvent();
            cout << (color == 1 ? "BLACK WIN" : "WHITE WIN") << endl;
            break;
        }
        else if ((count[2] + count[6]) == 4) {
            gameOverEvent();
            cout << (color == 1 ? "BLACK WIN" : "WHITE WIN") << endl;
            break;
        }
        else if ((count[3] + count[7]) == 4) {
            gameOverEvent();
            cout << (color == 1 ? "BLACK WIN" : "WHITE WIN") << endl;
            break;
        }
        else
            continue;
    }
}

void mouseEvent(int pointX, int pointY)
{
    float mouseD = 0, minDistance = 3.f, minDistanceX = 0, minDistanceY = 0;
    float XX = (float)(pointX - 20) / 800;
    float YY = 0.97f - (float)(pointY) / 800;

    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            mouseD = pow(mat[y][x][0] - XX, 2) + pow(mat[y][x][1] - YY, 2);
            if (minDistance > mouseD)
            {
                minDistance = mouseD;

                minDistanceX = mat[y][x][0];

                minDistanceY = mat[y][x][1];

                pX = x;
                pY = y;
            }    
        }


    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 1.0f);

    glScalef(2.0, 2.0, 0);

    glTranslatef(-0.47, -0.47, 0);

    glTranslatef(minDistanceX, minDistanceY, 0);

    glutSolidCube(0.02f);

    glPopMatrix();
    
    glFlush();

    minDistance = 3.0f;

    glClear(GL_COLOR_BUFFER_BIT);
    dg.glDrawScale();
    dg.glDrawLine();
    dg.glDrawStone(mat);

}

void clickEvent(int A, int B, int px, int py)
{
    if (B == GLUT_DOWN)

        if (mat[pY][pX][2] == 0)
        {
            if (turn == 0) {
                mat[pY][pX][2] = 1;
                checkOver(pX, pY, 1); 
                turn = 1;
            }
            else {
                mat[pY][pX][2] = 2;
                checkOver(pX, pY, 2); 
                turn = 0;
            }
        }
}

void keyboardEvent(unsigned char key, int x, int y )
{
    if (key == 'q' || key == 'Q') exit(0);
    else if (key == 'S' || key == 's') { 
        og.resetGame(mat); 
        if (turn) { turn = 0; }
    }
}

void display() {

    if (restart) {        
        og.resetGame(mat);
        restart = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    
    glutPassiveMotionFunc(mouseEvent);
    
    glutMouseFunc(clickEvent);
    
    glutKeyboardFunc(keyboardEvent);
    
    dg.glDrawScale(); 

    dg.glDrawLine();

    dg.glDrawStone(mat);
    
    glFlush(); 

}

void noShowConsole()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

int main(int argc, char** argv)
{
    noShowConsole();
    
    if (init) {        
        og.initGame(argc, argv, mat);
        init = false;
    } 

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;  
}