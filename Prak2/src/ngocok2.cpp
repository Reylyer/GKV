#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

static int shoulderx = 0;
static int shouldery = 0;
static int shoulderz = 0;
static int elbow = 0;
static int palmx = 0;
static int palmz = 0;

void init() {
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
}

void display() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glColor3f(1, 1, 1);
        glRasterPos2f(-3, -3);
        int len, i;
        char contmes[256];
        sprintf(contmes, "shoulderx %d shouldery %d shoulderz %d elbow %d palmx %d, palmz %d", shoulderx, shouldery, shoulderz, elbow, palmx, palmz);
        len = strlen(contmes);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, contmes[i]);
        }
    glPopMatrix();

    glPushMatrix();
        glTranslatef (-3.0, 0.0, 0.0);
        glRotatef ((GLfloat) shoulderx, 1.0, 0.0, 0.0);
        glRotatef ((GLfloat) shouldery, 0.0, 1.0, 0.0);
        glRotatef ((GLfloat) shoulderz, 0.0, 0.0, 1.0);
        glTranslatef (1.0, 0.0, 0.0);
        glPushMatrix();
            glScalef(2.0, 0.6, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();

        glTranslatef (1.0, 0.0, 0.0);
        glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
        glTranslatef (1.0, 0.0, 0.0);
        glPushMatrix();
            glScalef (2.0, 0.4, 1.0);
            glutSolidCube (1.0);
        glPopMatrix();
        
        glTranslatef (1, 0.0, 0.0);
        glRotatef ((GLfloat) palmx, 1.0, 0.0, 0.0);
        glRotatef ((GLfloat) palmz, 0.0, 0.0, 1.0);
        glTranslatef (0.5, 0.0, 0.0);
        glPushMatrix();
            glScalef (1, 0.2, 1.5);
            glutSolidCube (1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.1, 0.0, -.5); // kalibrasi posisi

            glTranslatef(-0.1, -0.2, -2);
            glRotatef((GLfloat) 2*palmz, 0.0, 0.0, 1.0); // sendi jempol
            glTranslatef(0.1, 0.2, 2);

            glPushMatrix();
                // kalibrasi sudut jempol
                glRotatef(90, 0.0, 1.0, 0.0);
                glRotatef(30, 1.0, 0.0, 0.0);
                glRotatef(30, 1.0, 0.0, 1.0);

                for(int j = 0; j < 2; j++){
                    glTranslatef (0.2, 0.0, 0.0);
                    glRotatef ((GLfloat) 2*palmz, 0.0, -4, 1.0);
                    glTranslatef (0.25, 0.0, 0.0);

                    glPushMatrix();
                        glScalef (0.5, 0.2, 0.2);
                        glutSolidCube(1);
                    glPopMatrix();
                }
            glPopMatrix();
        glPopMatrix();

        for(int i = -2; i < 2; i++){
            // -2: pinky, -1: ring, 0: middle, 1:index
            glPushMatrix();
                glTranslatef(0.2, 0.0, (i/3.0)+0.2);
                // per finger
                for(int j = 0; j < 3; j++){
                    glTranslatef (.25, 0., 0.);
                    glRotatef ((GLfloat) 2*palmz, 0., 0., 1.);
                    glTranslatef (.25, 0., 0.);

                    glPushMatrix();
                        glScalef (.5, .25, .25);
                        glutSolidCube (1.);
                    glPopMatrix();
                }
            glPopMatrix();
        }

        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();  
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (GLfloat)w / (GLfloat)h, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -5);
}

static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 :
            exit(0);
            break;
        case 'w':
            shoulderz = (shoulderz + 1) % 360;
            break;
        case 's':
            shoulderz = (shoulderz - 1) % 360;
            break;
        case 'a':
            shouldery = (shouldery - 1) % 360;
            break;
        case 'd':
            shouldery = (shouldery + 1) % 360;
            break;
        case 'e':
            shoulderx = (shoulderx + 5) % 360;
            break;
        case 'q':
            shoulderx = (shoulderx - 5) % 360;
            break;
        case 't':
            if (elbow < 120) {
                elbow = (elbow + 1);                
            } break;
        case 'g':
            if (elbow > 0) {
                elbow = (elbow - 1);                
            } break;
        case 'i':
            if (palmz < 43) {
                palmz = (palmz + 1);                
            } break;
        case 'k':
            if (palmz > 0) {
                palmz = (palmz - 1);                
            } break;
        case 'j':
            if (palmx < 20) {
                palmx = (palmx + 1);                
            } break;
        case 'l':
            if (palmx > -20) {
                palmx = (palmx - 1);                
            } break;
        case '/':
            shoulderx = 0;
            shouldery = 0;
            shoulderz = 0;
            elbow = 0;
            palmx = 0;
            palmz = 0;
            break;
    }
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
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
    glutMainLoop();
    return 0;
}