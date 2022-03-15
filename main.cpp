#include <GL/glut.h>
#include <GL/GLU.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "DrawView.h"
#include "DrawGL.h"
#include "OperateGL.h"
#include "RigidCircle.h"
#include "main.h"

using namespace std;

float windowwidth = 800;
float windowheight = 800;
float x_width = windowwidth / 2;
float y_height = windowheight / 2;

bool init = 1, restart = 1;
static float mat[15][15][3];
static char Turn = 0;
static int widthWeight = 1.2;

float origin_point_x = 0.065f;
float origin_potin_y = 0.065f;

float Distance = 0, minDistance = 3.f,
minDistanceX = 0, minDistanceY = 0;
int position_x, position_y;

float scale_x = 2.0;
float scale_y = 2.0;
float transf_x = -0.47;
float transf_y = -0.47;

int direct_x, direct_y;
int circleCount = 0, maxCount = 0;
float radius = 0.03f;

DrawGL gl;
OperateGL os;

void mouseEvent(int pointX, int pointY)
{
    float XX = (float)(pointX - 20) / 800;
    float YY = 0.97f - (float)(pointY) / 800;

    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            Distance = pow(mat[y][x][0] - XX, 2) + pow(mat[y][x][1] - YY, 2);
            if (minDistance > Distance)
            {
                minDistance = Distance;
                minDistanceX = mat[y][x][0];
                minDistanceY = mat[y][x][1];
                position_x = x;
                position_y = y;
            }
        }

    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glColor3f(0.9f, 0.0f, 0.0f);

    glScalef(scale_x, scale_y, 0);

    glTranslatef(transf_x, transf_y, 0);

    glTranslatef(minDistanceX, minDistanceY, 0);

    glutSolidCube(0.02f);

    glPopMatrix(); // ���ϰڴ�.

    minDistance = 3.0f;

    glFlush();

    glClear(GL_COLOR_BUFFER_BIT);

    gl.glDrawScale();
    gl.drawLine();
    gl.glDrawStone(mat);
}

void clickEvent(int A, int B, int px, int py)
{
    if (B == GLUT_DOWN)
        if (mat[position_y][position_x][2] == 0)
        {
            if (Turn == 0) {
                mat[position_y][position_x][2] = 1;
                checkOver(position_x, position_y, mat[position_y][position_x][2]);
                Turn = 1;
            }
            else {
                mat[position_y][position_x][2] = 2;
                checkOver(position_x, position_y, mat[position_y][position_x][2]);
                Turn = 0;
            }
        }
}

void keyboardEvent(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q') exit(0);
    else if (key == 'S' || key == 's') os.resetGame(mat);
}

void display() {

    if (restart) {        
        os.resetGame(mat);
        restart = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    // �⺻ ���콺 �̵��� ���� �Լ�.
    glutPassiveMotionFunc(mouseEvent);

    // �⺻ ���콺 Ŭ���� ���� �Լ�.
    glutMouseFunc(clickEvent);

    // Ű���� �Է½� ���� �Լ�.
    glutKeyboardFunc(keyboardEvent);

    // ȭ���?�׸���.
    gl.glDrawScale();

    gl.drawLine();

    gl.glDrawStone(mat);

    // ȭ�鿡 ����.
    glFlush();
}

void direct(int x, int y)  // �˰��򿡼� �����?x ,y �ӽ� �����Ѵ�.
{
    direct_x = x;
    direct_y = y;
}

void checkOver(int xPos, int yPos, int color)  // Ŭ���� ������ ����ȴ�?
{

    int count[8] = { 0, };
    for (int i = 0; i < 8; i++)
    {
        int x = xPos; int y = yPos;
        while (x >= 0 && y >= 0 && x <= 14 && y <= 14)
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
            x = x + direct_x;
            y = y + direct_y;

            if (x >= 0 && y >= 0 && x <= 14 && y <= 14) {
                if (mat[y][x][2] == color)
                {
                    count[i]++;
                    //std::cout << count[0] + count[4] << std::endl;
                    //std::cout << count[1] + count[5] << std::endl;
                    //std::cout << count[2] + count[6] << std::endl;
                    //std::cout << count[3] + count[7] << std::endl;
                    //std::cout << "\n" << std::endl;
                }
                else
                    break;
            }
            else
                break;

        }
        if ((count[0] + count[4]) == 4) {            
            gameOverAnim();
            break;
        }
        else if ((count[1] + count[5]) == 4) {            
            gameOverAnim();
            break;
        }
        else if ((count[2] + count[6]) == 4) {            
            gameOverAnim();
            break;
        }
        else if ((count[3] + count[7]) == 4) {           
            gameOverAnim();
            break;
        }
        else
            continue;
    }
}

void gameOverAnim() {

    gl.glDrawStone(mat);

    glFlush();

    Sleep(3000);

    glClear(GL_COLOR_BUFFER_BIT);

    RigidCircle* CC = new RigidCircle[255];

    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            if (mat[y][x][2] != 0) {

                CC[circleCount] = RigidCircle(mat[y][x][0], mat[y][x][1],
                    mat[position_y][position_x][0], mat[position_y][position_x][1],
                    radius, mat[y][x][2], 0.1);

                circleCount++;
                maxCount = circleCount;
            }
        }
    circleCount = 0;

    for (int i = 0; i < 100; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        gl.glDrawScale();
        gl.drawLine();

        while (circleCount < maxCount)
        {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glScalef(scale_x, scale_y, 0);
            glTranslatef(transf_x, transf_y, 0);            
            glTranslatef(CC[circleCount].x, CC[circleCount].y, 0);

            
            DrawView draw;
            draw.drawCircle(CC[circleCount].clr);
            

            glEnd();
            glPopMatrix();

            CC[circleCount].update();
            circleCount++;
            Sleep(1);

        }

        glFlush();
        circleCount = 0;
    }

    //game_over = 1;
    restart = 1;

    delete[] CC;
}

int main(int argc, char** argv)
{
    // �ʱ�ȭ�� ���� 
    if (init) {        
        os.initGame(argc, argv, mat);
        init = 0;
    }

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
// ==================================================================================================== //