// #include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define onii using
#define chan namespace
#define daisuki std

onii chan daisuki;

// convert 3 int 0 - 255 -> percentage
float *rgb_to_float(int r, int g, int b){
    float rgb[] = {(float)r/255, (float)g/255, (float)b/255};
    cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;
    return rgb;
}

void create_pyramid(){
    float kiri = -.8;
    float kanan = abs(kiri);
    float sisi = .1;
    glLineWidth(2);
    float y_impostor = -1;
    for(float y = y_impostor; y <= 0; y += sisi/2){
        for(float x = y; x <= abs(y); x += sisi){
	        glColor4f(0.16, 0.67, 0.792, 0.5);
            glRectf(x, y_impostor, x + sisi, y_impostor + sisi);
            glColor3f(0., 0., 0.);
            
            glBegin(GL_LINE_LOOP);
                glVertex2f(x, y_impostor);
                glVertex2f(x + sisi, y_impostor);    
                glVertex2f(x + sisi, y_impostor + sisi);
                glVertex2f(x, y_impostor + sisi);
            glEnd();
        }
        y_impostor+=sisi;
    }
}

void display_pyramid(){
    glPushMatrix();
        glScalef(.7, .7, 0);
        create_pyramid();
    glPopMatrix();
}

// using GL_QUADS to create background
void create_background() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        float* rgb1 = rgb_to_float(246, 147, 238);
        glColor3f(rgb1[0], rgb1[1], rgb1[2]);

        glVertex2d(-1.0, 1.0);
        glVertex2d(1.0, 1.0);
    
        float* rgb2 = rgb_to_float(79, 246, 203);
        glColor3f(rgb2[0], rgb2[1], rgb2[2]);

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

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
    create_background();
    // create_grid(0.1);
    display_pyramid();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(720, 720);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Tugas 3 - Piramida");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
