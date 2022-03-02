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

// convert 3 int 0 - 255 -> percentage
float *rgb_to_float(int r, int g, int b){
    float rgb[] = {(float)r/255, (float)g/255, (float)b/255};
    cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;
    return rgb;
}

void add_circle_vertex(float step_deg, float r = 1){
    float i, buf;
    for (int i = 0; i <= 360; i += step_deg) {
        buf = i * M_PI / 180;
        glVertex2f(cos(buf) * r, sin(buf) * r);
        // cout << cos(i) << sin(i) << endl;
    }
}

// using GL_LINE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP
void draw_cassete_tape() {
    glLineWidth(2);
    float *rgb;
    rgb = rgb_to_float(28, 28, 37);
    glColor3f(rgb[0], rgb[1], rgb[2]);
    // body black
    glBegin(GL_QUADS);
        glVertex2d(0., .5);
        glVertex2d(.8, .5);
        glVertex2d(.8, 0.);
        glVertex2d(0., 0.);
    glEnd();

    rgb = rgb_to_float(142, 148, 123);
    glColor3f(rgb[0], rgb[1], rgb[2]);
    // body grey
    glPushMatrix();
        glTranslatef(.01, -.015, 0.);
        glScalef(.97, .95, 1.);
        glBegin(GL_QUADS);
            glVertex2d(0., .5);
            glVertex2d(.8, .5);
            glVertex2d(.8, 0.);
            glVertex2d(0., 0.);
        glEnd();
    glPopMatrix();

    rgb = rgb_to_float(28, 28, 37);
    glColor3f(rgb[0], rgb[1], rgb[2]);
    // detail grip
    glPushMatrix();
        glTranslatef(0., -.007, 0.);
        glBegin(GL_LINE_STRIP);
            glVertex2d(.2, .5);
            glVertex2d(.25, .45);
            glVertex2d(.55, .45);
            glVertex2d(.6, .5);
        glEnd();
    glPopMatrix();

    // detail black
    glPushMatrix();
        glTranslatef(.15, -.15, 0.);
        glScalef(.625, .6, 1.);
        glBegin(GL_QUADS);
            glVertex2d(0., .5);
            glVertex2d(.8, .5);
            glVertex2d(.8, 0.);
            glVertex2d(0., 0.);
        glEnd();
    glPopMatrix();

    rgb = rgb_to_float(164, 166, 184);
    glColor3f(rgb[0], rgb[1], rgb[2]);

    // detail pseudo circle left
    glBegin(GL_TRIANGLE_FAN);
        glPushMatrix();
            // glTranslatef(.25, .25, 0.);
            // glPushMatrix();
                // glScalef(.002, .002, 1);
                add_circle_vertex(45., 0.1);
            // glPopMatrix();
        glPopMatrix();
        // glVertex2f(.25, .25);
        // glVertex2f(.27, .23);
        // glVertex2f(.23, .23);
        // glVertex2f(.23, .27);
        // glVertex2f(.23, .27);
        // glVertex2f(.25, .3);
        // glVertex2f(.25, .2);
        // glVertex2f(.2, .25);
    glEnd();

     // detail pseudo circle right
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(.55, .3);
        glVertex2f(.55, .2);
        glVertex2f(.6, .25);
    glEnd();
}

// left cassete tape
void draw_left_cassete_tape(){
    glPushMatrix();
        glTranslatef(-.7, .3, 0.);
        glRotatef(45, 0., 0., 1);
        glScalef(.315, .3, 1);
        draw_cassete_tape();
    glPopMatrix();
}

// reflected left casset tape 
void draw_right_cassete_tape(){
    glPushMatrix();
        glRotatef(180, 0., 1., 0.);
        draw_left_cassete_tape();
    glPopMatrix();
}

// create bootleg Hotline Miami 2: Wrong number logo
// using GL_LINE_LOOP and GL_LINES
void draw_coldpoint_semarang(){
    float buf;
    // draw pseudo circle
    float* rgb = rgb_to_float(242, 0, 0);
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glLineWidth(10);


    glPushMatrix();
        glTranslatef(0., 0.4, 0.);
        glScalef(.19, .3, .3);

        // Pseudo circle
        glBegin(GL_LINE_LOOP);
            add_circle_vertex(15.);
        glEnd();

        // upper line
        glBegin(GL_LINES);
            buf = 30 * M_PI / 180;
            glVertex2f(cos(buf), sin(buf));
            buf = (30 + 120) * M_PI / 180;
            glVertex2f(cos(buf) -.1, sin(buf));
        glEnd();

        // middle line
        glBegin(GL_LINES);
            buf = 0 * M_PI / 180;
            glVertex2f(cos(buf), sin(buf));
            buf = 180 * M_PI / 180;
            glVertex2f(cos(buf)-.1, sin(buf));
        glEnd();

        // lower line
        glBegin(GL_LINES);
            buf = 210 * M_PI / 180;
            glVertex2f(cos(buf)-0.1, sin(buf));
            buf = (210 + 120) * M_PI / 180;
            glVertex2f(cos(buf), sin(buf));
        glEnd();
    glPopMatrix();
}

// create restart r text, using GL_QUAD_STRIP
void draw_restart_label(){
    glLineWidth(5);
    glColor3f(0., 0., 0.);

    glPushMatrix();
        glTranslatef(0., -0.6, 0);
        // background
        glBegin(GL_QUAD_STRIP);
            glVertex2d(-.3, .1);
            glVertex2d(.3, .1);
            glVertex2d(-.3, -.1);
            glVertex2d(.3, -.1);
        glEnd();

        char ded_string[] = "PRESS R TO RESTART";

        float* rgb = rgb_to_float(246, 147, 238);
        glColor3f(rgb[0], rgb[1], rgb[2]);

        // text with angle
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glPushMatrix();
            glTranslatef(-.28, -.64, 0.);
            glScalef(0.0003, 0.0004, 0.0004);
            glRotatef(3, 0., 0., 1.);

            int len = (int) strlen(ded_string);
            for (int i = 0; i < len; i++) {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ded_string[i]);
            }
        glPopMatrix();
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

// visualize step needed
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
    draw_restart_label();
    draw_coldpoint_semarang();
    draw_left_cassete_tape();
    draw_right_cassete_tape();
    draw_cassete_tape();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Gelud gaming");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
