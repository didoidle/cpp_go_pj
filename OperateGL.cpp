#include "OperateGL.h"

void OperateGL::initGame(int argc, char** argv, float matrix[15][15][3])
{
    // 창을 띄운다.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_STENCIL);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL");    
    dg.glDrawScale();
    dg.glDrawLine();

    // 바둑판의 좌표들을 입력해준다.x, y
    for (int y = 1; y <= 15; y++){
        for (int x = 0; x < 15; x++)
        {
            matrix[y - 1][x][0] = ((float)x / 15);
            matrix[y - 1][x][1] = 1.f - ((float)y / 15);
        }
    }
    // 준비되면 화면을 띄운다.
    glFlush();
}

void OperateGL::resetGame(float matrix[15][15][3])
{
    // 바둑판의 바둑좌표에 상태를 초기화 해준다.
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            matrix[y][x][2] = 0;
        }

}
