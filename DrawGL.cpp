#include "DrawGL.h"

DrawGL::DrawGL() {}

DrawGL::~DrawGL(){}

// �ٵ����� ũ�� ���߱�
void DrawGL::glDrawScale() {

	glLoadIdentity();

	glScalef(2.0, 2.0, 0);

	glTranslatef(transX, transY, 0);

	glClearColor(bR, bG, bB, 1.0f);
	
}

void DrawGL::glDrawLine() {
	// ���� ����
	glColor3f(0.0f, 0.0f, 0.0f);

	// ���� ����
	glLineWidth(2.0);

	// ���� ���θ� 15�� �� �׸��� �ݺ���
	for (int i = 0; i < 15; i++)
	{
		// ����
		glBegin(GL_LINES);

		glVertex2f(0.f, (float)i / 15);

		glVertex2f(1.f - 0.065f, (float)i / 15);

		glEnd();

		// ����
		glBegin(GL_LINES);

		glVertex2f((float)i / 15.f, 0.f);

		glVertex2f((float)i / 15.f, 1.0f - 0.065f);

		glEnd();
	}
}

void DrawGL::glDrawCircle(int color) {

	// ���� ���ϱ�
	if (color == 1) {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);

	}

	// �ٰ������� ������
	glBegin(GL_POLYGON);

	// �������� ������ֱ�
	for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f)
		glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);
}

// �ٵ��ǿ� ����ġ�� ã�Ƽ� ������� ���� �׸���.
void DrawGL::glDrawStone(float matrix[15][15][3]) {

	for (int y = 0; y < 15; y++)
		for (int x = 0; x < 15; x++)
		{
			if (matrix[y][x][2] != 0) {

				// �ٵϵ��� ��ǥ�� ã���ִ� �κ�
				glMatrixMode(GL_MODELVIEW);

				glLoadIdentity(); // ��� ����

				glScalef(2.0, 2.0, 0);

				glTranslatef(transX, transY, 0);

				glTranslatef(matrix[y][x][0], matrix[y][x][1], 0);

				glDrawCircle(matrix[y][x][2]);

				glEnd();

				glPopMatrix();

			}
		}
}

