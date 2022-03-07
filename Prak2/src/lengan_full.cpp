#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

class Tangan{
    public:
        Tangan(float x, float y, float z, bool kiri = true){
            this->shoulderP[0] = x; 
            this->shoulderP[1] = y; 
            this->shoulderP[2] = z;
            this->isKiri = kiri;
            if(kiri){
                this->mirror = -1;
            }
        }
        void draw(){
            glPushMatrix();
                // shoulder point of rotation
                glTranslatef(this->shoulderP[0], this->shoulderP[1], this->shoulderP[2]);
                if (!this->isKiri){
                    glScalef(1, 1, -1);
                }

                // sendi peluru bahu
                glRotatef(this->shoulderx*this->mirror, 1., 0., 0.);
                glRotatef(this->shoulderz*this->mirror, 0., 0., 1.);
                glRotatef(this->shouldery*this->mirror, 0., 1., 0.);
                glTranslatef(this->arm_len, 0., 0.);

                // arm
                glPushMatrix(); 
                    glScalef(2., .4, 1.);
                    glutSolidCube(1.);
                glPopMatrix();
                
                // elbow
                glTranslatef (this->forearm_len, 0., 0.);
                glRotatef (this->elbow, 0., 0., 1.);
                glTranslatef (this->forearm_len, 0., 0.);

                // forearm
                glPushMatrix();
                    glScalef(this->forearm_len*2, this->forearm_len*.4, this->forearm_len);
                    glutSolidCube(1.);
                glPopMatrix();
                
                // wrist
                glTranslatef(0.75, 0., 0.);
                glRotatef(this->palm, 0., 0., 1.);
                glTranslatef(0.75, 0., 0.);
                
                // palm
                glPushMatrix(); 
                    glScalef(1, .3, 1.25);
                    glutSolidCube (1.);
                glPopMatrix();

                // thumb
                glPushMatrix();
                    glTranslatef(0., 0., -.45); // kalibrasi posisi

                    glTranslatef(-.1, -.2, -2);
                    glRotatef(this->palm, 0., 0., 1.); // sendi jempol
                    glTranslatef(.1, .2, 2);

                    glPushMatrix();
                        // kalibrasi sudut jempol
                        glRotatef(60, 0., 1., 0.);
                        glRotatef(30, 1., 0., 0.);

                        for(int j = 0; j < 2; j++){
                            // sendi
                            glTranslatef (this->fing_size, 0., 0.);
                            glRotatef (this->palm, 0., 0., 1.);
                            glTranslatef (this->fing_size, 0., 0.);

                            glPushMatrix();
                                glScalef (.5, this->fing_size, this->fing_size);
                                glutSolidCube (1.);
                            glPopMatrix();
                        }
                    glPopMatrix();
                glPopMatrix();

                // fingeerrrrr non thumb
                for(int i = -2; i < 2; i++){
                    // -2: pinky, -1: ring, 0: middle, 1:index
                    glPushMatrix();
                        // kalibrasi posisi jari relatif telapak
                        // z axis
                        // i*const: spread,
                        // + const: offset
                        glTranslatef(this->fing_size, 0., i/3. + 0.17);
                        // per finger
                        for(int j = 0; j < 3; j++){
                            // sendi
                            glTranslatef(this->fing_size, 0., 0.);
                            glRotatef(this->palm, 0., 0., 1.);
                            glTranslatef (this->fing_size, 0., 0.);

                            //ruas
                            glPushMatrix();
                                glScalef(.5, this->fing_size, this->fing_size);
                                glutSolidCube(1.);
                            glPopMatrix();
                        }
                    glPopMatrix();
                }

            glPopMatrix();
        }

        void shoulderxup(int t = 1){
            this->shoulderx = (this->shoulderx + t) % 360;
        }
        void shoulderxdo(int t = 1){
            this->shoulderx = (this->shoulderx - t) % 360;
        }
        void shoulderzup(int t = 1){
            this->shoulderz = (this->shoulderz + t) % 360;
        }
        void shoulderzdo(int t = 1){
            this->shoulderz = (this->shoulderz - t) % 360;
        }
        void shoulderyup(int t = 1){
            this->shouldery = (this->shouldery + t) % 360;
        }
        void shoulderydo(int t = 1){
            this->shouldery = (this->shouldery - t) % 360;
        }
        void elbowup(int t = 1){
            this->elbow = (this->elbow + t) % 360;
        }
        void elbowdo(int t = 1){
            this->elbow = (this->elbow - t) % 360;
        }
        void palmup(int t = 1){
            this->palm = (this->palm + t) % 360;
        }
        void palmdo(int t = 1){
            this->palm = (this->palm - t) % 360;
        }

    private:
        float fing_size = .2;
        float thumb_size = fing_size *1.5;
        float palm_size = .3;
        float shoulderP[3];
        float arm_len = 1;
        float forearm_len = 1;
        int shoulderx = 0;
        int shouldery = 270;
        int shoulderz = 0;
        int elbow = 5;
        int palm = 5; 
        int mirror = 1;
        bool isKiri;
};

Tangan* tangan_kiri = new Tangan(-3, 0, 0);
Tangan* tangan_kanan = new Tangan(3, 0, 0, false);

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tangan_kiri->draw();
    tangan_kanan->draw();
    
    glutSwapBuffers();  
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1., 20.);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glTranslatef(0., 0., -5.0);
} 

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': // internal rotation
            tangan_kiri->shoulderzup();
            tangan_kanan->shoulderzup();
            break;
        case 'S': // internal rotation
            tangan_kiri->shoulderzdo();
            tangan_kanan->shoulderzdo();
            break;
        case 'q': // tangan naik
            tangan_kiri->shoulderxup();
            tangan_kanan->shoulderxup();
            break;
        case 'Q': // tangan turun
            tangan_kiri->shoulderxdo();
            tangan_kanan->shoulderxdo();
            break;
        case 'd': // tangan ke dalam
            tangan_kiri->shoulderyup();
            tangan_kanan->shoulderydo();
            break;
        case 'D': // tangan ke luar
            tangan_kiri->shoulderydo();
            tangan_kanan->shoulderyup();
            break;
        case 'e': // tutup sikut
            tangan_kiri->elbowup();
            tangan_kanan->elbowup();
            break;
        case 'E': // buka sikut
            tangan_kiri->elbowdo();
            tangan_kanan->elbowdo();
            break;
        case 'w': // genggam
            tangan_kiri->palmup();
            tangan_kanan->palmup();
            break;
        case 'W': // melepas
            tangan_kiri->palmdo();
            tangan_kanan->palmdo();
            break;
        case 27: 
            exit(0);
    }
    glutPostRedisplay(); 
} 


void initGL() {
    glClearColor(0, 0.2, 0.5, 0.8);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

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
    glutInitWindowSize(700, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    initGL();
    glutMainLoop(); 
    return 0;
} 