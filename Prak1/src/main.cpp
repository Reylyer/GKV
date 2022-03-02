#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

static float zrotaxis = 0;

static void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_POLYGON);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glRotated(zrotaxis, 1, 1, 1);
        glBegin(GL_POLYGON);
            glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
            glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
            glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
        glEnd();
    glPopMatrix();

    glColor3f(1, 1, 1);
    glRasterPos2f(-0.95, -0.95);
    int len, i;
    char string[256];
    sprintf(string, "zrotaxis = %.2f", zrotaxis);
    len = strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
    }
    glutSwapBuffers();

    if (zrotaxis > 360.0) {
        zrotaxis = 0;
    } else {
        zrotaxis += 0.5;
    }
}

static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 : 
        case 'q':
            exit(0);
            break;
        case '+':
            zrotaxis += 0.1;
            break;
        case '-':
            zrotaxis -= 0.1;
            break;
    }

    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(400, 300);
    glutCreateWindow("the most unoptimized tri in the world");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMainLoop();
}