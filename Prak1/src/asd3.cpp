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

unsigned int r = 30, g = 230, b = 200;
int increment = 3;


// rainbow gaming
void set_and_increment_color(){
    if(b > 250 || b < 200){
        // g+= 5;
        increment = -increment;
    }
    glColor3ub(r, g, b);
    b += increment;
}

// using GL_TRIANGLE_STRIP to draw letter S (capital)
void draw_S(){
    float vert_arrS[][2] = {
        {8, 9}, {6, 7}, {3, 9}, {1, 7}, {-4, 9}, // head
        {-2, 7}, {-8, 5}, {-4, 5}, // neck
        {-2, 0}, {2, 0}, // body
        {3, -4}, {7, -4}, {1, -6}, // knee
        {3, -8}, {0, -6}, {-2, -8}, {-4, -6}, {-6, -8}, {-8, -6}, {-10, -8} // tail
    };
    glPushMatrix();
        glTranslatef(-.79, 0., 0.);
        glPushMatrix();
            glScalef(.02, .02, 1);
            glBegin(GL_TRIANGLE_STRIP);
                for(auto p: vert_arrS){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

// using GL_LINE_LOOP to draw H (capital)
void draw_H(){
    float vert_arr_H[][2] = {
        // right side
        {3, -1}, {3, -9}, {5, -9}, // lower
        {5, 9}, {3, 9}, {3, 1},  // upper
        // left side
        {-3, 1}, {-3, 9}, {-5, 9}, // upper
        {-5, -9}, {-3, -9}, {-3, -1} //lower
    };
    glLineWidth(8);

    glPushMatrix();
        glTranslatef(-.48, 0.005, 0.);
        glPushMatrix();
            glScalef(.019, .019, 1);
            glBegin(GL_LINE_LOOP);
                for(auto p: vert_arr_H){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}


// using GL_TRIANGLE_FAN to draw A (capital)  // arch gaming baby
void draw_A(){
    float vert_arr_A[][2] = {
        {0, 0}, // core
        {-5, -9}, {-7, -9}, // left side // {-2, -2},
        {0, 9}, // top point
        {7, -9}, {5, -9}, //right side // {2, -2} 
    };
    glPushMatrix();
        glTranslatef(-.2, 0.005, 0.);
        glPushMatrix();
            glScalef(.019, .019, 1);
            glBegin(GL_TRIANGLE_FAN);
                for(auto p: vert_arr_A){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

// using GL_LINE_STRIP to draw R
void draw_R(){
    float vert_arr_R[][2] = {
        {-5, -9}, {-5, 9}, // vertical left
        {5, 9}, {5, 0}, //vertical right
        {-5, 0}, // knee
        // leg
        {-5, -2}, {-1, -2},
                  {-1, -5}, {2, -5},
                           {2, -7}, {5, -7},
                                    {5, -9}
    };
    glLineWidth(15);
    glPushMatrix();
        glTranslatef(.075, 0.005, 0.);
        glPushMatrix();
            glScalef(.019, .019, 1);
            glBegin(GL_LINE_STRIP);
                for(auto p: vert_arr_R){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

// using GL_QUADS and GL_TRIANGLE_FAN to draw i
void draw_i(){
    float vert_arriBlock[][2] = {
        {-1, 3}, {1, 3},
        {1, -10}, {-1, -10}, 
    };
    glPushMatrix();
        glTranslatef(.28, 0.02, 0.);
        glPushMatrix();
            
            glScalef(.019, .019, 1);
            glBegin(GL_QUADS);
                for(auto p: vert_arriBlock){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();

            glPushMatrix();
                glTranslatef(0, 7, 0);
                glBegin(GL_TRIANGLE_FAN);
                    for(int i = 0; i <= 360; i+= 60){
                        set_and_increment_color();  
                        glVertex2f(cos((i * M_PI / 180))*1.2, sin((i * M_PI / 180))*1.2);
                    }
                glEnd();
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}

// using GL_TRIANGLE_FAN AGAIN to draw Y
void draw_Y(){
    float vert_arr_Y[][2] = {
        {0, 1}, // core
        {0, 3}, // neck
        {6, 8.7}, {7, 7}, // right hand
        {1, 1}, // right armpit
        {1, -9}, {-1, -9}, // leg
        {-1, 1}, // left armpit
        {-7, 7}, {-6, 8.7}, // left hand
        {0, 3}, // neck end loop
    };
    glPushMatrix();
        glTranslatef(.5, 0.005, 0.);
        glPushMatrix();
            glScalef(.019, .019, 1);
            glBegin(GL_TRIANGLE_FAN);
                for(auto p: vert_arr_Y){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

// using GL_QUAD_STRIP to draw L
void draw_L(){
    float vert_arrL[][2] = {
        {-5, 9}, {-3, 9}, // edge top
        {-5, 0}, {-3, 0}, // middle
        {-5, -9}, {-3, -7}, // corner 
        {0, -9}, {0, -7}, // middle bottom
        {5, -9}, {5, -7} 
    };
    glPushMatrix();
        glTranslatef(.8, 0.005, 0.);
        glPushMatrix();
            glScalef(.019, .019, 1);
            glBegin(GL_QUAD_STRIP);
                for(auto p: vert_arrL){
                    set_and_increment_color();
                    glVertex2f(p[0], p[1]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

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

// visualize grid strechness
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

    // create_background(); // black background more fit
    // create_grid(0.1);
	glColor4f(0.16, 0.67, 0.792, 0.5);
    draw_S();
    draw_H();
    draw_A();
    draw_R();
    draw_i();
    draw_Y();
    draw_L();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 1280);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Tugas 2 - Shariyl");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
