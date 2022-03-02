#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define X_LEN 20
#define Y_LEN 20

void dda(int x1, int y1, int x2, int y2){
    int step;
    float x = x1;
    float y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xplus = (float) dx/step;
    float yplus = (float) dy/step;

    glPointSize(12);
    glBegin(GL_POINTS);
        for(int i = 0; i < step; i++){
            glVertex2d(round(x), round(y));
            x += xplus; y += yplus;
        }
    glEnd();
}


void create_grid(float step=0.2) {
	glColor3f(0.16 * 0.3, 0.67 * 0.3, 0.792 * 0.3);

    for(float x = -X_LEN; x <= X_LEN; x +=step){
        glBegin(GL_LINES);
            glVertex2f(x, -X_LEN);
            glVertex2d(x, X_LEN);
        glEnd();
    }
    for(float y = -Y_LEN; y <= Y_LEN; y +=step){
        glBegin(GL_LINES);
            glVertex2f(-Y_LEN, y);
            glVertex2d(Y_LEN, y);
        glEnd();
    }

    glLineWidth(2);

    glBegin(GL_LINES);
        glVertex2f(0, -Y_LEN);
        glVertex2f(0, Y_LEN);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-X_LEN, 0);
        glVertex2f(X_LEN, 0);
    glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
    create_grid(1.);
    glColor4f(0.16, 0.67, 0.792, 0.5);
    dda(1, 1, 10, 7);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(480, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Menggambar Garis Dengan Algoritma DDA");
    gluOrtho2D(-X_LEN, X_LEN, -Y_LEN, Y_LEN);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
