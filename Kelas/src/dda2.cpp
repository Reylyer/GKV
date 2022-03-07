#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>

const int lengthX = 30,lengthY = 30;
int curCoor[4] = {0,0,10,6};


void dda(int x1, int y1, int x2, int y2){
    int step;
    float x = x1;
    float y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xplus = (float) dx/step;
    float yplus = (float) dy/step;

    glColor4f(1, 1, 1, 0.5);
    glPointSize(5);
    glBegin(GL_POINTS);
        for(int i = 0; i < step; i++){
            glVertex2d(round(x), round(y));
            x += xplus; y += yplus;
        }
    glEnd();
}

void createGrid(float step=0.2) {
    int lineWid = 1;
    glColor3f(0, 0, 1);
    glLineWidth(lineWid);
    for(float x = -lengthX; x <= lengthX; x +=step){
        lineWid = round(x)==0.0 ? 2 : 1;
        glLineWidth(lineWid);
        glBegin(GL_LINES);
            glVertex2f(x, -lengthX);
            glVertex2d(x, lengthX);
        glEnd();
    }
    for(float y = -lengthY; y <= lengthY; y +=step){
        lineWid = round(y)==0.0 ? 2 : 1;
        glLineWidth(lineWid);
        glBegin(GL_LINES);
            glVertex2f(-lengthY, y);
            glVertex2d(lengthY, y);
        glEnd();
    }
}

void handleMovePoint(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glRotatef(20, 0, 0, 1);
        createGrid(1);
        dda(curCoor[0], curCoor[1], curCoor[2], curCoor[3]);
    glPopMatrix();
    glFlush();
}

void keyboardFunc(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP :
				curCoor[3]+=1;
                handleMovePoint();
                break;
		case GLUT_KEY_DOWN :
				curCoor[3]-=1;
                handleMovePoint();
                break;
		case GLUT_KEY_RIGHT :
				curCoor[2]+=1;
                handleMovePoint();
                break;
        case GLUT_KEY_LEFT :
                curCoor[2]-=1;
                handleMovePoint();
                break;
	}
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glRotatef(20, 0, 0, 1);
        createGrid(1);
        dda(curCoor[0], curCoor[1], curCoor[2], curCoor[3]);
    glPopMatrix();
    glFlush();
}
void init (void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-lengthX, lengthX, -lengthY, lengthY);
    glutSpecialFunc(keyboardFunc);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Algoritma DDA");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}