#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#define M_PI 3.14159265358979323846

const int WIN_SIZE[] = {640, 480};
const float SENSITIVITY = 1.;
const float MAX_VEL_RUNNING = 0.2;
const float MAX_VEL_WALKING = 0.1;

const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 1.0f };
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

bool running = false;
int yaw   = 0, 
    pitch = 90;

float ratio;
// n step from camera before commiting movement
float x_step = 0, 
      z_step = 0; 
float x = 0., y = 1.75, z = 15.; // posisi awal kamera
float vx = 0., vy = 0., vz = 0.;
float dMove = 0, h, w;
int bitmapHeight = 12;

int mposx = 0, mposy = 0;


void draw_custom_cube(float sisi){
    // float w = sisi, l = sisi*2;
    // float bodyVerts[4][3] = {
    //     {w, l, 0},
    //     {-w, l, 0},
    //     {-w, -l, 0},
    //     {w, -l, 0}
    // };
    // float sideVerts[4][3] = {
    //     {l, l, 0},
    //     {-l, l, 0},
    //     {-l, -l, 0},
    //     {l, -l, 0}
    // };
    // float bodyRot[6] = {0, -90, -180, 90, -90, 90};
    // float bodyRotaxis[6][3] = {
    //     {0, 0, 0},
    //     {1, 0, 0},
    //     {1, 0, 0},
    //     {1, 0, 0},
    //     {0, 1, 0},
    //     {0, 1, 0}
    // };
    // glPushMatrix();
    //     glTranslatef(0, l, 0);
    //     for (int i = 0; i < 4; i++) {
    //         glPushMatrix();
    //             glRotatef(bodyRot[i], bodyRotaxis[i][0], bodyRotaxis[i][1], bodyRotaxis[i][2]);
    //             glTranslatef(0, 0, l);
    //             glBegin(GL_QUADS);
    //                 for (auto v: bodyVerts) glVertex3fv(v);
    //             glEnd();
    //         glPopMatrix();
    //     };
    //     for (int i = -1; i < 2; i += 2) {
    //         glPushMatrix();
    //             glRotatef(i*90, 0, 1., 0.);
    //             glTranslatef(0, 0, w);
    //             glBegin(GL_QUADS);
    //                 for (auto v: sideVerts) glVertex3fv(v);
    //             glEnd();
    //         glPopMatrix();
    //     }
    // glPopMatrix();
    float base_vert[4][3] = {
        {sisi,  sisi,  0},
        {-sisi, sisi,  0},
        {-sisi, -sisi, 0},
        {sisi,  -sisi, 0}
    };
    float rot[] = {0, -90, -180, 90, -90, 90};
    float vect[][3] = {
        {1, 0, 0},
        {0, 1, 0}
    };
    int select = 0;
    for(int i = 0; i < 6; i++){
        glPushMatrix();
            glRotatef(rot[i], vect[select][0], vect[select][1], vect[select][2]);
            glTranslatef(0, 0, sisi);
            glBegin(GL_QUADS);
                for(auto v: base_vert) glVertex3fv(v);
            glEnd();
        glPopMatrix();
        if(i == 2 || i == 3){
            for(auto v: base_vert) glTexCoord3fv(v);
        }
        if(i == 3) select++;
    }
}

void draw_linkeran(int step = 1, float r = 1){
    float rad;
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i < 360; i+=step){
            rad = i * M_PI / 180.;
            glVertex3d(cos(rad)*r, sin(rad)*r, 0);
        }
    glEnd();
}

void draw_roda(float r, float tebel){
    float rad;
    glPushMatrix();
        glTranslatef(0, 0, -tebel/2.);
        GLUquadric* a = gluNewQuadric();
        gluCylinder(a, r, r, tebel, 100, 1);
        gluQuadricTexture(a, GLU_TRUE);
        
        for(int i = 0; i < 2; i += 1){
            glPushMatrix();
                glTranslatef(0, 0, tebel*i);
                draw_linkeran(1, r);
            glPopMatrix();
        }
    glPopMatrix();
}

class Kepala_Truk{
    public:
        Kepala_Truk(){}
        Kepala_Truk(float x, float y, float z){
            this->trukP[0] = x; 
            this->trukP[1] = y; 
            this->trukP[2] = z;
            
        }
        void draw(){
            glPushMatrix();
                glTranslatef(this->trukP[0], this->trukP[1], this->trukP[2]);
                glColor3ub(255, 0, 0);
                draw_custom_cube(this->width);

                glColor3ub(0, 0, 0);
                glPushMatrix();
                    glTranslatef(this->width, 0, 0);
                    glRotatef(90, 0, 1, 0);
                    draw_roda(3, 2);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(-this->width, 0, 0);
                    glRotatef(90, 0, 1, 0);
                    draw_roda(3, 2);
                glPopMatrix();
               

            glPopMatrix();
        }
        
    private:
        float trukP[3];
        float width = 5;
};

class Kontainer{
    public:
        Kontainer(){}
        Kontainer(float x, float y, float z){
            this->konP[0] = x; 
            this->konP[1] = y; 
            this->konP[2] = z;
            
        }
        void draw(){
            glPushMatrix();
                glTranslatef(this->konP[0], this->konP[1], this->konP[2]);
                glColor3ub(255, 1, 1);
                glPushMatrix();
                    glScalef(this->x, this->y, this->z);
                    draw_custom_cube(1);
                glPopMatrix();

                glColor3ub(20, 20, 20);
                glPushMatrix();
                    glTranslatef(this->x, -this->y, 0);
                    glRotatef(90, 0, 1, 0);
                    draw_roda(1.5, 2);
                glPopMatrix();

                // glPushMatrix();
                //     glTranslatef(-this->x, 0, 0);
                //     glRotatef(90, 0, 1, 0);
                //     draw_roda(3, 2);
                // glPopMatrix();
               

            glPopMatrix();
        }
        
    private:
        float konP[3];
        float x = 4, y = 4, z = 8;
};


Kepala_Truk *kepala_truk = new Kepala_Truk(0, 0, 3);

Kontainer *kontainers = new Kontainer[100];
Kontainer *kontainer = new Kontainer(0, 5, 6);


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
    yaw += (int)1*dx;
    pitch += (int)1*dy;
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
    const float gap = 10;
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(4);
    glBegin(GL_LINES);
        for (i = Z_MIN; i <= Z_MAX; i += gap) {
            glVertex3f(i, 0, Z_MIN);
            glVertex3f(i, 0, Z_MAX);
        }
        for (i = X_MIN; i <= X_MAX; i += gap) {
            glVertex3f(X_MIN, 0, i);
            glVertex3f(X_MAX, 0, i);
        }
    glEnd();
}

void draw_asphalt(){
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glRectf(-100, -100, 100, 100);
    glPopMatrix();
}

void display() {
    movePlayer(x_step, z_step);
    orientCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Grid();
    // draw_asphalt();

    kepala_truk->draw();
    // kontainer->draw();
    // for(int i = 1; i < 100; i++) kontainers[i].draw();
    std::cout << std::fixed;
    std::setprecision(5);
    std::cout << "yaw "    << std::setw(4) << yaw << " ";
    std::cout << "pitch " << std::setw(4) << pitch;
    std::cout << " | ";
    std::cout << std::setw(12) << vx << " ";
    std::cout << std::setw(12) << vy << " ";
    std::cout << std::setw(12) << vz;
    std::cout <<  " | ";
    std::cout << std::defaultfloat;
    std::setprecision(2);
    std::cout << "len(vect) " << sqrt(vx*vx + vy*vy + vz*vz);
    std::cout <<  " | ";
    std::cout << running  << " ";
    std::cout << std::setw(6) << x_step << " ";
    std::cout << std::setw(6) << z_step;
    std::cout <<  " | ";
    std::cout << "X " << std::setw(12) << x << " ";
    std::cout << "Z " << std::setw(12) << z;
    std::cout << std::endl;

    glutSwapBuffers();  
}

void Reshape(int w1, int h1) {
    // Fungsi reshape
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1. * w / h;
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
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSetCursor(GLUT_CURSOR_NONE);

    // glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    // glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    // glLightfv(GL_LIGHT3, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    for(int i = 1; i < 100; i++) kontainers[i] = Kontainer(i*5, 3, 3);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_SIZE[0], WIN_SIZE[1]);
    glutCreateWindow("3D Lighting");
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