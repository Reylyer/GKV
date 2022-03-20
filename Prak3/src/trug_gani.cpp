#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

float
    x = 0.,
    y = 1.75,
    z = 15.,
    lx = 0.,
    ly = 0.,
    lz = -1.,
    x_step = 0,
    y_step = 0,
    m_sens = 0.1,
    ratio,
    h,
    w;
    

int mposx = 0,
    mposy = 0,
    pitch = 90,
    yaw = 0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



double Normal3dv(double *v) {
   return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void reshape (int w1, int h1) {
    if (h1 == 0) {
        h1 = 1;
    }
    w = w1;
    h = h1;
    ratio = 1. * (w / h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0., 1., 0.
    );
}

void orientRot() {
    
    float radPitch = pitch*M_PI/180.;
    float radYaw = yaw*M_PI/180.;

    lx = -sin(radPitch)*sin(radYaw);
    ly = cos(radPitch);
    lz = sin(radPitch)*cos(radYaw);

    glLoadIdentity();
    gluLookAt(x, y, z,
        x + lx, y + ly, z + lz,
        0., 1., 0.
    );
}

void orientMove(float maju_mundur, float kanan_kiri) {
    x = x + maju_mundur * lx - kanan_kiri * lz;
    z = z + maju_mundur * lz + kanan_kiri * lx;
}

void fpvControl(int x1, int y1){
    int dx = x1 - mposx;
    int dy = y1 - mposy;
    mposx = w/2;
    mposy = h/2;
    glutWarpPointer(w / 2, h / 2);
    yaw += (float)1*dx*m_sens;
    pitch += (float)1*dy*m_sens;
    if (pitch >= 179) {
        pitch = 179;
    }
    else if (pitch < 1) {
        pitch = 1;
    }
}

void renderCube(float w, float l, float h) {
    float zVerts[4][3] = {
        {w, h, 0},
        {-w, h, 0},
        {-w, -h, 0},
        {w, -h, 0}
    };
    float xVerts[4][3] = {
        {l, h, 0},
        {-l, h, 0},
        {-l, -h, 0},
        {l, -h, 0}
    };
    float yVerts[4][3] = {
        {w, l, 0},
        {-w, l, 0},
        {-w, -l, 0},
        {w, -l, 0}
    };
    float zRot[6] = {0, -90, -180, 90, -90, 90};
    float zRotAxis[6][3] = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    glPushMatrix();
        glTranslatef(0, h, 0);
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
                glRotatef(180-(i*180), 1, 0, 0);
                glTranslatef(0, 0, l);
                glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);
                    for (auto v: zVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        };
        for (int i = -1; i < 2; i += 2) {
            glPushMatrix();
                glRotatef(i*90, 0, 1., 0.);
                glTranslatef(0, 0, w);
                glBegin(GL_QUADS);
                    for (auto v: xVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        }
        for (int i = -1; i < 2; i += 2) {
            glPushMatrix();
                glRotatef(i*90, 1, 0, 0.);
                glTranslatef(0, 0, h);
                glBegin(GL_QUADS);
                    for (auto v: yVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void renderCircle(int step = 1, float r = 1){
    float rad;
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i < 360; i+=step){
            rad = i * M_PI / 180.;
            glVertex3d(cos(rad)*r, sin(rad)*r, 0);
        }
    glEnd();
}

void renderCylinder(float radius, float height) {
    float 
        x = 0.0,
        y = 0.0,
        angle = 0.0,
        angle_stepsize = 0.1;
    glPushMatrix();
        glTranslatef(-height/2, radius, 0);
        glRotatef(90, 0, 1, 0);
        glBegin(GL_QUAD_STRIP);
            angle = 0.0;
            while(angle < 2*M_PI) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                glVertex3f(x, y , 0.0);
                glNormal3f(cos(angle),sin(angle),0);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
        glEnd();

        glPushMatrix();
            glBegin(GL_POLYGON);
            angle = 0.0;
                while( angle < 2*M_PI ) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glNormal3f(0, 0, 1);
                    glVertex3f(x, y , height);
                    angle = angle + angle_stepsize;
                }
                glNormal3f(0, 0, 1);
                glVertex3f(radius, 0.0, height);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -height);
            glBegin(GL_POLYGON);
            angle = 0.0;
                while (angle < 2*M_PI) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glNormal3f(0, 0, -1);
                    glVertex3f(x, y , height);
                    angle = angle + angle_stepsize;
                }
                glNormal3f(0, 0, -1);
                glVertex3f(radius, 0.0, height);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void renderTruck() {
    glPushMatrix();
        glColor3ub(16, 16, 16);
        glTranslatef(0, 1.3, -3);
        renderCube(0.2, 0.1, 0.1);
    glPopMatrix();

    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
            glTranslatef(i*2, 0, 0);
            glPushMatrix();
                glColor3ub(16, 16, 16);
                glTranslatef(0, 0, 6.45);
                renderCylinder(1, 0.5);
                glTranslatef(0, 0, (-6.25*2)-1);
                renderCylinder(1, 0.5);
                glTranslatef(0, 0, 2.2);
                renderCylinder(1, 0.5);
            glPopMatrix();
        glPopMatrix();
    }

    glPushMatrix();
        glTranslatef(0, 1, 0);
        glPushMatrix();
            glColor3ub(16, 16, 16);
            renderCube(2.15, 9.2, 0.1);
            glTranslatef(0, 0.0, -9.1);

            glTranslatef(0, 0.2, 6.25);
            renderCube(2, 6.25, 0.1);
            glTranslatef(0, 0, -6.25);

            glPushMatrix();
                glTranslatef(0, 0.2, 0);
                //container2
                glColor3ub(225, 25, 25);
                glTranslatef(0, 0, 3);
                renderCube(1.8, 3, 2.5);
                glTranslatef(0, 0, 3);
                glTranslatef(0, 0, 0.2);

                //container1
                glColor3ub(225, 25, 25);
                glTranslatef(0, 0, 3);
                renderCube(1.8, 3, 2.5);
                glTranslatef(0, 0, 3);
                glTranslatef(0, 0, 0.2);

                //separator
                glColor3ub(16, 16, 16);
                glTranslatef(0.0, 0.0, 0.05);
                renderCube(2.0, 0.05, 2.4);
                glTranslatef(0.0, 0.0, 0.05);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0, 6.25*2+0.1);
                //truckhead
                glColor3ub(255, 59, 1);
                glTranslatef(0.0, 0.0, 1.0);
                renderCube(2.0, 1.0, 2.0);
                glTranslatef(0.0, 0.0, 1.0);

                //trucknose
                glTranslatef(0, 0.0, 1.8);
                renderCube(2.0, 1.8, 1.2);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void renderTruckDeco() {
    //side panel
    for (int i = -1; i <= 1; i += 2) {
        //side panel 1
        glPushMatrix();
            glColor3ub(172, 172, 172);
            glTranslatef(i*2, 3.65, 5.15);
            renderCube(0.01, 0.2, 0.4);
        glPopMatrix();

        //side panel 2
        glPushMatrix();
            glColor3ub(172, 172, 172);
            glTranslatef(i*2, 3.65, 4.3);
            renderCube(0.01, 0.55, 0.6);
        glPopMatrix();
        
        //side door
        glPushMatrix();
            glColor3ub(114, 26, 24);
            glTranslatef(i*2, 1.5, 4.55);
            renderCube(0.01, 0.8, 1);
        glPopMatrix();

        // door handle
        glPushMatrix();
            glColor3ub(0, 0, 0);
            glTranslatef(i*2, 2.7, 4.1);
            renderCube(0.05, 0.2, 0.05);
        glPopMatrix();

        // door handle frame
        glPushMatrix();
            glColor3ub(128, 128, 128);
            glTranslatef(i*2, 2.65, 4.1);
            renderCube(0.02, 0.15, 0.1);
        glPopMatrix();
    }

    //front panel
    glPushMatrix();
        glColor3ub(172, 172, 172);
        glTranslatef(0, 3.7, 5.5);
        renderCube(1.8, 0.01, 0.6);
    glPopMatrix();

    //vent
    for (float i = 0; i <= 0.5; i += 0.1) {
        glPushMatrix();
            glColor3ub(0, 0, 0);
            glTranslatef(0, 1.5+(2*i), 9.1);
            renderCube(0.6+(i/2), 0.01, 0.05);
        glPopMatrix();
    }

    //headlamp
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
            glColor3ub(255, 255, 0);
            glTranslatef(i*1.4, 1.5, 9.1);
            renderCube(0.4, 0.01, 0.2);
        glPopMatrix();
    }
}

void grid() {
    double i;
    const float Z_MIN = -100, Z_MAX = 100;
    const float X_MIN = -100, X_MAX = 100;
    const float gap = 1.;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
        glNormal3f(0, 0, -1);
        for (i = Z_MIN; i < Z_MAX; i += gap) {
            glVertex3f(i, 0, Z_MIN);
            glVertex3f(i, 0, Z_MAX);
        }
        for (i = X_MIN; i < X_MAX; i += gap) {
            glVertex3f(X_MIN, 0, i);
            glVertex3f(X_MAX, 0, i);
        }
    glEnd();
}

void ground() {
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3f(-100, 0, -100);
        glVertex3f(100, 0, -100);
        glVertex3f(100, 0, 100);
        glVertex3f(-100, 0, 100);
    glEnd();
}

void display() {
    orientMove(x_step, y_step);
    orientRot();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        grid();
        ground();
    glPopMatrix();

    glPushMatrix();
        renderTruck();
        renderTruckDeco();
    glPopMatrix();

    glutSwapBuffers();
}

static void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'w':
            x_step += .05;
            break;
        case 'a':
            y_step -= .05;
            break;
        case 's':
            x_step -= .05;
            break;
        case 'd':
            y_step += .05;
            break;
    }
}

static void keyRelease(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 's':
            x_step = 0;
            break;
        case 'a':
        case 'd':
            y_step = 0;
            break;
    }
}

void initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0.2, 0.5, 0.8);
    glShadeModel(GL_FLAT);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("truggsssss");
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutPassiveMotionFunc(fpvControl);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();
    return 0;
} 