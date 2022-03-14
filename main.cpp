#include <GL/glut.h>
#include <GL/GLU.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "main.h"

using namespace std;

float windowwidth = 800;
float windowheight = 800;
float x_width = windowwidth / 2;
float y_height = windowheight / 2;

float brownR = (float)152/255;
float brownG = (float)102/255;
float brownB = (float)52/255;

bool init = 1, restart = 1, game_over = 0;
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

float radius = 0.03f;

int direct_x, direct_y;

int circleCount = 0, maxCount = 0;

void draw_line() 
{

    glClearColor(brownR, brownG, brownB, 1.0f);
    glLoadIdentity();
    glScalef(scale_x, scale_y, 0);
    glTranslatef(transf_x, transf_y, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(2.0);

    for (int i = 0; i < 15; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(0.f, (float)i / 15);
        //glVertex2f(1.f - origin_point_x  , (float)i/15);
        glVertex2f(1.f - origin_point_x, (float)i / 15);
        glEnd();
    }

    for (int i = 0; i < 15; i++)
    {
        glBegin(GL_LINES);
        glVertex2f((float)i / 15.f, 0.f);
        //glVertex2f((float)i / 15.f, 1.0f - origin_potin_y);
        glVertex2f((float)i / 15.f, 1.0f - origin_potin_y);
        glEnd();
    }

    //glFlush();
}
void draw_circle()
{
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            if(mat[y][x][2] != 0)
                if (mat[y][x][2] == 1)
                {
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glScalef(scale_x, scale_y, 0);
                    glTranslatef(transf_x, transf_y, 0);
                    glTranslatef(mat[y][x][0], mat[y][x][1], 0);
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glBegin(GL_POLYGON);
                    for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f) {
                        glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);

                    }
                    glEnd();
                    glPopMatrix();
                }
                else
                {   
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glScalef(scale_x, scale_y, 0);
                    glTranslatef(transf_x, transf_y, 0);
                    glTranslatef(mat[y][x][0], mat[y][x][1], 0);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glBegin(GL_POLYGON);
                    for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f) {
                        glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);

                    }
                    glEnd();
                    glPopMatrix();
                }
        }
}
void initialization(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_STENCIL);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowwidth, windowheight);
    glutCreateWindow("OpenGL");
    glClearColor(brownR, brownG, brownB, 1.0f);
    draw_line();
    
    //gluOrtho2D(-0.09f, 1.f, -0.09f, 1.f);

    for (int y = 1; y <= 15; y++)
        for (int x = 0; x < 15; x++)
        {
            mat[y-1][x][0] = ((float)x / 15 );
            mat[y-1][x][1] = 1.f - ((float)y / 15 );
        }

    init = 0;
    glFlush();
}
void game_initialization()
{
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            mat[y][x][2] = 0;
        }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
    draw_line();
    restart = 0;
    maxCount = 0;
}

void mouse_move(int pointX, int pointY)
{
        
        //std::cout << pointX << " " << pointY << "\n" << std::endl;
        float XX = (float)(pointX-20) / 800;
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
        glTranslatef(minDistanceX, minDistanceY,0);
        glutSolidCube(0.02f);
        /*glColor3f(0.9f, 0.0f, 0.0f);
        glPointSize(10.0);
        
        glBegin(GL_POINTS);
        glVertex2f(minDistanceX, minDistanceY);
        glEnd();*/
        glPopMatrix();
        
        minDistance = 3.0f;


        
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);
        draw_line();
        draw_circle();
}
void click(int A, int B, int px, int py)
{
    
    if (B == GLUT_DOWN)
        if (mat[position_y][position_x][2] == 0)
        {
            /*for (int y = 0; y < 15; y++) {
                for (int x = 0; x < 15; x++)
                {
                    std::cout << mat[y][x][2] << ", " << std::endl;
                }
                printf("\n");
            }*/
            
            if (Turn == 0) {
                mat[position_y][position_x][2] = 1;
                check_over(position_x, position_y, mat[position_y][position_x][2]);
                Turn = 1;
            }
            else {
                mat[position_y][position_x][2] = 2;
                check_over(position_x, position_y, mat[position_y][position_x][2]);
                Turn = 0;
            }
        }
    
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 's':
    case 'S':
    {
        game_initialization();
        break;
    }
    default:
        break;
    }
}

void direct(int x , int y )
{
    direct_x =  x;
    direct_y =  y;
}

void check_over(int xPos, int yPos, int color)
{

    int count[8] = { 0, };
    for (int i = 0; i < 8; i++)
    {
        int x = xPos; int y = yPos;
        while (x >= 0 && y >= 0 && x <=14 && y <= 14)
        {
            
            switch (i)
            {
            case 0:
                direct(-1, -1);
                break;
            case 1:
                direct(0,-1);
                break;
            case 2:
                direct(1,-1);
                break;
            case 3:
                direct(1,0);
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
            x = x + direct_x; y = y + direct_y;
            if (x >= 0 && y >= 0 && x <= 14 && y <= 14) {
                if (mat[y][x][2] == color)
                {
                    count[i]++;
                    std::cout << count[0] + count[4] << std::endl;
                    std::cout << count[1] + count[5] << std::endl;
                    std::cout << count[2] + count[6] << std::endl;
                    std::cout << count[3] + count[7] << std::endl;
                    std::cout << "\n" << std::endl;
                    
                }
                else 
                    break;
            }
            else 
                break;

        }
        if ((count[0] + count[4]) == 4) {
            //game_over = 1;
            over();
            break;
        }
        else if ((count[1] + count[5]) == 4) {
            //game_over = 1;
            over();
            break;
        }
        else if ((count[2] + count[6]) == 4) {
            //game_over = 1;
            over();
            break;
        }
        else if ((count[3] + count[7]) == 4) {
            //game_over = 1;
            over();
            break;
        }
        else
            continue;
    }
}
void over() {
    draw_circle();
    glFlush();
    Sleep(2000);
    glClear(GL_COLOR_BUFFER_BIT);
    

    //glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
    //printf("¤±¤¤¤·¤©");
    ////glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1.f, 0.f, 0.f);
    //glRasterPos2f(0.f, 0.f);
    //glRasterPos2f(100, 100); //define position on the screen
    //const char *string = "Text";

    //while (*string) {
    //    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
    //}

    rigidCircle *CC = new rigidCircle[255];
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            if (mat[y][x][2] != 0) {
                CC[circleCount] = rigidCircle(mat[y][x][0], mat[y][x][1],
                    mat[position_y][position_x][0], mat[position_y][position_x][1], 
                    radius, mat[y][x][2], 0.1);
                
                circleCount++;
                maxCount = circleCount;
            }
        }
    circleCount = 0;
    for (int i = 0; i < 70; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_line();
        while (circleCount < maxCount)
        {
            

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glScalef(scale_x, scale_y, 0);
            glTranslatef(transf_x, transf_y, 0);
            glTranslatef(CC[circleCount].x, CC[circleCount].y, 0);
            glColor3f(CC[circleCount].R, CC[circleCount].G, CC[circleCount].B);
            glBegin(GL_POLYGON);
            for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f) {
                glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);

            }

            glEnd();
            glPopMatrix();
            CC[circleCount].update();
            circleCount++;
            Sleep(1);
            
        }
        glFlush();
        circleCount = 0;
    }
    
    //ÆùÆ®
       /* GLUT_BITMAP_8_BY_13
        GLUT_BITMAP_9_BY_15
        GLUT_BITMAP_TIMES_ROMAN_10
        GLUT_BITMAP_TIMES_ROMAN_24
        GLUT_BITMAP_HELVETICA_10
        GLUT_BITMAP_HELVETICA_12
        GLUT_BITMAP_HELVETICA_18*/
    cout << " qqqqqqqqqqq";
    //game_over = 1;
    restart = 1;

    delete[] CC;
}
void display() {

    
    if (restart)
        game_initialization();
    //glViewport(0, 0, 800, 800);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(click);
    glutKeyboardFunc(keyboard);

    

    draw_line();

    draw_circle();
    if (restart)
        game_initialization();
    if (game_over) {
        Sleep(1000);
        printf("³¡\n");
        exit(0);
    }
    glFlush();
}



int main(int argc, char** argv)

{
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_HIDE);
    //if (init)
    initialization(argc, argv);
    
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;

}