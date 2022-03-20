#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <chrono>

#define M_PI 3.14159265358979323846
using namespace std;
using namespace std::chrono;

const int   WIN_SIZE[] = {640, 480};
const float SENSITIVITY = 1.;
const float MAX_VEL_RUNNING = 0.2;
const float MAX_VEL_WALKING = 0.1;

const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 1.0f };
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 0.3f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 0.3f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 0.2f };
const GLfloat high_shininess[] = { 20.0f };

bool running = false;
int yaw   = 0, 
    pitch = 90;
// n step from camera before commiting movement
float x_step = 0, 
      z_step = 0; 
float x = 0., y = 1.75, z = 15.; // posisi awal kamera
float vx = 0., vy = 0., vz = 0.;
float dMove = 0, h, w;
int bitmapHeight = 12;

int mposx = 0, mposy = 0;

// https://stackoverflow.com/a/1568687/14052716 with modif
void orientCamera() {
    float buff_pitch = pitch*M_PI/180.;
    float buff_yaw = yaw*M_PI/180.;

    vx = -sin(buff_pitch)*sin(buff_yaw);
    vy = cos(buff_pitch);
    vz = sin(buff_pitch)*cos(buff_yaw);

    glLoadIdentity();
    gluLookAt(x, y, z,
        x + vx, y + vy, z + vz,
        0., 1., 0.);
}

void movePlayer(float maju_mundur, float kanan_kiri) {
    if(running){
        maju_mundur = abs(maju_mundur) < MAX_VEL_RUNNING ? maju_mundur : maju_mundur > 0 ? MAX_VEL_RUNNING: -MAX_VEL_RUNNING;
        kanan_kiri = abs(kanan_kiri) < MAX_VEL_RUNNING ? kanan_kiri : kanan_kiri > 0 ? MAX_VEL_RUNNING : -MAX_VEL_RUNNING;
    } else{
        maju_mundur = abs(maju_mundur) < MAX_VEL_WALKING ? maju_mundur : maju_mundur > 0 ? MAX_VEL_WALKING: -MAX_VEL_WALKING;
        kanan_kiri = abs(kanan_kiri) < MAX_VEL_WALKING ? kanan_kiri : kanan_kiri > 0 ? MAX_VEL_WALKING : -MAX_VEL_WALKING;
    }
    x = x + maju_mundur * vx - kanan_kiri * vz;
    z = z + maju_mundur * vz + kanan_kiri * vx;
}

void fpsGaming(int x1, int y1){
    int dx = x1 - mposx;
    int dy = y1 - mposy;
    mposx = w/2;
    mposy = h/2;
    glutWarpPointer(w / 2, h / 2);
    yaw += (int)(SENSITIVITY*dx);
    pitch += (int)(SENSITIVITY*dy);
    if(pitch>=179) pitch =179;
    else if(pitch<1) pitch=1;
}
void Grid() {
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50,
        Z_MAX = 50;
    const float X_MIN = -50,
        X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
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

void display() {
    auto start = high_resolution_clock::now();
    movePlayer(x_step, z_step);
    orientCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << fixed;
    setprecision(5);
    cout << "yaw "    << setw(4) << yaw << " ";
    cout << "pitch " << setw(4) << pitch;
    cout << " | ";
    cout << setw(12) << vx << " ";
    cout << setw(12) << vy << " ";
    cout << setw(12) << vz;
    cout <<  " | ";
    cout << defaultfloat;
    setprecision(2);
    cout << running  << " ";
    cout << setw(6) << x_step << " ";
    cout << setw(6) << z_step;
    cout <<  " | ";
    cout << "X " << setw(12) << x << " ";
    cout << "Z " << setw(12) << z;
    cout << " | ";
    cout << "frametime " << duration.count()/100. << " framerate " << floor(100000/duration.count());
    cout << endl;

    glutSwapBuffers();  
}

void Reshape(int w1, int h1) {
    // Fungsi reshape
    float ratio;
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + vx, y + vy, z + vz,
        0., 1., 0.);
}


// ordinary fps control,
// wasd, add shift to key combination to run
void pressKey(unsigned char key, int xn, int yn) {
    switch (key) {
        case 'W':
            x_step+= .1;
            running = true;
        case 'w':
            x_step+= .05;
            break;
        case 'S':
            x_step-= .1;
            running = true;
        case 's':
            x_step-= .05;
            break;
        case 'A':
            z_step-= .1;
            running = true;
        case 'a':
            z_step-= .05;
            break;
        case 'D':
            z_step+= .1;
            running = true;
        case 'd':
            z_step+= .05;
    }
}

// ordinary fps control,
// wasd, add shift to key combination to run
void releaseKey(unsigned char key, int xn, int yn) {
    switch (key) {
        case 'W':
        case 'S':
            running = false;
        case 'w':
        case 's':
            x_step= 0;
            break;
        case 'A':
        case 'D':
            running = false;
        case 'a':
        case 'd':
            z_step= 0;
    }
}

void initGL() {
    glClearColor(0., .5, 0.5, 1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT3);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSetCursor(GLUT_CURSOR_NONE);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_SIZE[0], WIN_SIZE[1]);
    glutCreateWindow("FPS GGEH");
    glutIgnoreKeyRepeat(0); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)

    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);

    glutDisplayFunc(display);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus
    glutReshapeFunc(Reshape);
    
    glutPassiveMotionFunc(fpsGaming); //fps gaming
    initGL();
    glutMainLoop(); 
    return 0;
} 