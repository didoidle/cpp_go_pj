#include "DrawGL.h"

DrawGL::DrawGL() {}

DrawGL::~DrawGL(){}

// 바둑판의 크기 맞추기
void DrawGL::glDrawScale() {

	glLoadIdentity();

	glScalef(2.0, 2.0, 0);

	glTranslatef(transX, transY, 0);

	glClearColor(bR, bG, bB, 1.0f);
	
}

void DrawGL::glDrawLine() {
	// 줄의 색상
	glColor3f(0.0f, 0.0f, 0.0f);

	// 줄의 굵기
	glLineWidth(2.0);

	// 가로 세로를 15줄 씩 그리는 반복문
	for (int i = 0; i < 15; i++)
	{
		// 가로
		glBegin(GL_LINES);

		glVertex2f(0.f, (float)i / 15);

		glVertex2f(1.f - 0.065f, (float)i / 15);

		glEnd();

		// 세로
		glBegin(GL_LINES);

		glVertex2f((float)i / 15.f, 0.f);

		glVertex2f((float)i / 15.f, 1.0f - 0.065f);

		glEnd();
	}
}

void DrawGL::glDrawCircle(int color) {

	// 색상 정하기
	if (color == 1) {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);

	}

	// 다각형으로 설정후
	glBegin(GL_POLYGON);

	// 원형으로 만들어주기
	for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f)
		glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);
}

// 바둑판에 돌위치를 찾아서 원모양의 돌을 그린다.
void DrawGL::glDrawStone(float matrix[15][15][3]) {

	for (int y = 0; y < 15; y++)
		for (int x = 0; x < 15; x++)
		{
			if (matrix[y][x][2] != 0) {

				// 바둑돌의 좌표를 찾아주는 부분
				glMatrixMode(GL_MODELVIEW);

				glLoadIdentity(); // 행렬 생산

				glScalef(2.0, 2.0, 0);

				glTranslatef(transX, transY, 0);

				glTranslatef(matrix[y][x][0], matrix[y][x][1], 0);

				glDrawCircle(matrix[y][x][2]);

				glEnd();

				glPopMatrix();

			}
		}
}

