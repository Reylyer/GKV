#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string.h>
#define M_PI 3.14159265358979323846

#define onii using
#define chan namespace
#define daisuki std

onii chan daisuki;

// using GL_QUADS to create background
void create_background() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3ub(246, 147, 238);
        glVertex2d(-1.0, 1.0);
        glVertex2d(1.0, 1.0);
        glColor3ub(79, 246, 203);
        glVertex2d(1.0, -1.0);
        glVertex2d(-1.0, -1.0);
    glEnd();
}

void create_grid(float step=0.2) {
	glColor4f(0.16, 0.67, 0.792, 0.5);

    for(float x = -1; x <= 1; x +=step){
        glBegin(GL_LINES);
            glVertex2f(x, -1);
            glVertex2d(x, 1);
        glEnd();
    }
    for(float y = -1; y <= 1; y +=step){
        glBegin(GL_LINES);
            glVertex2f(-1, y);
            glVertex2d(1, y);
        glEnd();
    }

    glLineWidth(4);

    glBegin(GL_LINES);
        glVertex2f(0, -1);
        glVertex2d(0, 1);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-1, 0);
        glVertex2d(1, 0);
    glEnd();
}

void resize_wtf(){
    glPushMatrix();
        glTranslatef(-1., 1., 0.);
        glPushMatrix();
            glScalef(0.007, 0.007, 1);
            // wtf_img();
        glPopMatrix();
    glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
    create_background();
    // create_grid(0.1);
    resize_wtf();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(720, 720);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Gelud gaming");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
