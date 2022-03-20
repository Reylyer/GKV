#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <chrono>

#define M_PI        3.13159265358979323846
#define onii        using
#define oniichan    using
#define suki        std::cout
#define hentai      std::endl
#define kirai       std::setprecision
#define kimoi       std::setw
#define kowaii      std::fixed
#define kakkoii     std::defaultfloat
#define chan        namespace
#define mendokusai  std::chrono


oniichan suki;
oniichan hentai;
oniichan kirai;
oniichan kimoi;
oniichan kowaii;
oniichan kakkoii;
onii chan mendokusai;

/* nikmati sebelum code spageti
                        /\
                       /||\
                      //||\\
                     ///||\\\
                    ////||\\\\
                   /||\\||//||\
                  //||\\||//||\\
                 ///||\\||//||\\\
                ////||\\||//||\\\\
               /||\\||//||\\||//||\
              //||\\||//||\\||//||\\
             ///||\\||//||\\||//||\\\
            ////||\\||//||\\||//||\\\\
           /||\\||//||\\||//||\\||//||\
          //||\\||//||\\||//||\\||//||\\
         ///||\\||//||\\||//||\\||//||\\\
        ////||\\||//||\\||//||\\||//||\\\\
       /||\\||//||\\||//||\\||//||\\||//||\
      //||\\||//||\\||//||\\||//||\\||//||\\
     ///||\\||//||\\||//||\\||//||\\||//||\\\
    //||\\||//||\\||\\||//||\\||//||\\||//||\\
   ///||\\||//||\\||\\||//||\\||//||\\||//||\\\
  //||\\||//||\\||//||\\||//||\\||//||\\||//||\\
 ///||\\||//||\\||//||\\||//||\\||//||\\||//||\\\
//||\\||//||\\||\\||//||\\||//||\\||//||\\||//||\\

hewego
*/


const int   WIN_SIZE[] = {640, 480};
const float SENSITIVITY = 1.;
const float MAX_VEL_RUNNING = 0.2;
const float MAX_VEL_WALKING = 0.1;

const GLfloat light0_position[] = { 10.0f, 5.0f, 0.0f, 1.0f };
const GLfloat light1_position[] = { -10.0f, 5.0f, 0.0f, 1.0f };
const GLfloat light_ambient[]   = { 0.0f, 0.0f, 0.0f, 0.f };
const GLfloat light_diffuse[]   = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat light_specular[]  = { 1.0f, 1.0f, 1.0f, 0.3f };

const GLfloat mat_ambient[]     = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]     = { 0.8f, 0.8f, 0.8f, 0.3f };
const GLfloat mat_specular[]    = { 1.0f, 1.0f, 1.0f, 0.2f };

const float compass[4][3] = {
    { 1,  1, 0},
    { 1, -1, 0},
    {-1, -1, 0},
    {-1,  1, 0}
};

const GLubyte mejikuhibiniu[][3] = {
    {138, 0, 211},
    {75, 0, 130},
    {0, 0, 255},
    {0, 255, 0},
    {255, 255, 0},
    {255, 127, 0},
    {255, 0 , 0}
};

bool running = false;
int yaw   = 180, 
    pitch = 90;
// n step from camera before commiting movement
float x_step = 0, 
      z_step = 0; 
float x = 0., 
      y = 1.75, 
      z = 25.; // posisi awal kamera
float vx = 0., vy = 0., vz = 0.;
float dMove = 0, h, w;
int bitmapHeight = 12;

int mposx = WIN_SIZE[0]/2, mposy = WIN_SIZE[1]/2;

class Kontainer{
    public:
        Kontainer(){}
        Kontainer(float x, float y, float z){
            this->konP[0] = x; 
            this->konP[1] = y; 
            this->konP[2] = z;
        }

        void draw_kon(){
            glPushMatrix();
                glTranslatef(this->konP[0], this->konP[1] + this->width*1.5, this->konP[2]);
                glPushMatrix();
                    glTranslatef(0, 1.5, 0);
                    glRotatef(90, 0, 1, 0);
                    draw_waved_container(this->width, this->width*4, 30);
                glPopMatrix();

                //roda karet
                glColor3ub(0, 0, 0);
                for(auto com: compass){
                    glPushMatrix();
                        glTranslatef(this->width*com[0], -this->width, this->width*1.4*com[1]);
                        glRotatef(90, 0, 1, 0);
                        draw_roda(this->width/2.5);
                    glPopMatrix();
                }
                //roda velg
                glColor3ub(200, 200, 200);
                int i = 0;
                for(auto com: compass){
                    glPushMatrix();
                        glTranslatef(this->width*com[0]*1.1, -this->width, this->width*1.4*com[1]);
                        glRotatef(90, 0, 1, 0);
                        if(i > 1){
                            glRotatef(180, 0, 1, 0);
                        }
                        draw_roda(this->width/5.);
                    glPopMatrix();
                    i++;
                }
                //draw slate
                glColor3ub(100, 100, 100);
                draw_slate();
                glPushMatrix();
                    glTranslatef(0, -1, this->width*3);
                    glScalef(this->width/4, 0.25, 1.5);
                    draw_custom_cube(1);
                glPopMatrix();
            glPopMatrix();
        }

        void draw_custom_cube(float sisi){
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
                        for(auto com: compass) glVertex3f(sisi*com[0], sisi*com[1], 0);
                    glEnd();
                glPopMatrix();
                if(i == 3) select++;
            }
        }
        void draw_waved_container(float height, float length, float num_of_wave){
            float rotation[] = {0, 90, 180, 270};
            float x, z, stop, step, wave_low, beam_height, waved_side_height;
            int state;
            step = length/num_of_wave;
            stop = length/2.;
            wave_low = -height/10.;
            beam_height = -wave_low;
            waved_side_height = height - beam_height;

            glPushMatrix();
                // 4 waved side
                for(auto rot: rotation){
                    glPushMatrix();
                        glRotatef(rot, 1, 0, 0);
                        glTranslatef(0, 0, height);
                        state = 0;
                        z = 0;
                        glBegin(GL_QUAD_STRIP);
                            for(x = -stop; x <= stop; x+=step){
                                glVertex3f(x, waved_side_height, z);
                                glVertex3f(x, -waved_side_height, z);
                                if(state % 2) z = z == 0 ? -wave_low : 0;
                                state++;
                            }
                        glEnd();
                    glPopMatrix();
                }
                // balok pinggir biar rapih
                for(auto com: compass){
                    glPushMatrix();
                        glTranslatef(com[2]*height, com[1]*height, com[0]*height);
                        glPushMatrix();
                            glScalef(stop, beam_height, beam_height);
                            draw_custom_cube(1);
                        glPopMatrix();
                    glPopMatrix();
                }
                // pintu container
                for(int i = -1; i <=1; i+=2){
                    glPushMatrix();
                        glTranslatef(i*(length/2. + beam_height), 0, 0);
                        glRotatef(90, 0, 1, 0);
                        glPushMatrix();
                            glScalef(height+beam_height, height+beam_height, beam_height);
                            draw_custom_cube(1);
                        glPopMatrix();
                    glPopMatrix();
                }
            glPopMatrix();
        }

        void draw_linkeran(float r){
            float rad;
            glBegin(GL_TRIANGLE_FAN);
                for(int i = 0; i < 360; i+=10){
                    rad = i * M_PI / 180.;
                    glVertex3f(cos(rad)*r, sin(rad)*r, 0);
                }
            glEnd();
        }

        void draw_roda(float r){
            float rad, tebel, pcos, psin;
            tebel = r/2.;
            glPushMatrix();
                glTranslatef(0, 0, -tebel/2.);
                for(int i = 0; i < 2; i += 1){
                    glPushMatrix();
                        glTranslatef(0, 0, tebel*i);
                        draw_linkeran(r);
                    glPopMatrix();
                }
                glBegin(GL_QUAD_STRIP);
                    for(int i = 0; i <= 370; i+=10){
                        rad = i * M_PI / 180.;
                        pcos = cos(rad)*r;
                        psin = sin(rad)*r;
                        glVertex3f(pcos, psin, 0);
                        glVertex3f(pcos, psin, tebel);
                    }
                glEnd();
            glPopMatrix();
        }
        void draw_slate(){
            glPushMatrix();
                glTranslatef(0, -1, 0);
                glPushMatrix();
                    glScalef(this->width*1.25, 0.25, this->width*2.4);
                    draw_custom_cube(1);
                glPopMatrix();
                glTranslatef(0, -.75, 0);
                glPushMatrix();
                    glScalef(this->width*1.25, 0.5, this->width*0.75);
                    draw_custom_cube(1);
                glPopMatrix();
                glPushMatrix();
                    glScalef(this->width*0.75, 0.5, this->width*2);
                    draw_custom_cube(1);
                glPopMatrix();
            glPopMatrix();
        }
        
    private:
        float konP[3];
        float width = 2;

};

class Kepala_Truk: public Kontainer{
    public:
        Kepala_Truk(){}
        Kepala_Truk(float x, float y, float z){
            this->trukP[0] = x; 
            this->trukP[1] = y; 
            this->trukP[2] = z;
        }
        void draw_truk(){
            glPushMatrix();
                glTranslatef(this->trukP[0], this->trukP[1] + this->width*1.5, this->trukP[2]);
                
                // kepala
                glColor3ub(100, 100, 100);
                glPushMatrix();
                    glTranslatef(0, this->width/2, this->width*1.25);
                    glPushMatrix();
                        glScalef(2.5, 1.75, 1.5);
                        draw_custom_cube(1);   
                    glPopMatrix();

                    glTranslatef(0, -this->width/2.5, this->width);
                    glPushMatrix();
                        glScalef(2.5, 2.5, 0.5);
                        draw_custom_cube(1);   
                    glPopMatrix();
                    
                    // decor

                    // kaca depan
                    glColor3ub(0,0,0);
                    glTranslatef(0, this->width/1.5, 0);
                    glPushMatrix();
                        glScalef(2, 1, 0.55);
                        draw_custom_cube(1);
                    glPopMatrix();
                    
                    // kaca samping
                    glTranslatef(0, 0, -this->width/2.5);
                    glPushMatrix();
                        glScalef(2.55, 1, 1);
                        draw_custom_cube(1);
                    glPopMatrix();

                    // gagang pintu
                    glTranslatef(0, -this->width/1.5, -this->width/2.5);
                    glPushMatrix();
                        glScalef(2.55, 0.05, 0.1);
                        draw_custom_cube(1);
                    glPopMatrix();

                    // bemper
                    glTranslatef(0, -this->width*1.25, this->width);
                    glPushMatrix();
                        glScalef(2.55, 0.25, 0.25);
                        draw_custom_cube(1);
                    glPopMatrix();

                    // lampu
                    glTranslatef(0, this->width/3, 0);
                    for(int i = -1; i < 2; i+=2){
                        glPushMatrix();
                            glColor3ub(255,255,255);
                            glTranslatef(i*this->width, 0, 0);
                            glPushMatrix();
                                glScalef(0.2, 0.25, 0.2);
                                draw_custom_cube(1);
                            glPopMatrix();

                            glColor3ub(255,255,0);
                            glTranslatef(-i*this->width/5, 0, 0);
                            glPushMatrix();
                                glScalef(0.2, 0.25, 0.2);
                                draw_custom_cube(1);
                            glPopMatrix();
                        glPopMatrix();
                    }

                    // spion
                    glTranslatef(0, this->width*1.5, -this->width/10);
                    for(int i = -1; i < 2; i+=2){
                        glPushMatrix();
                            glColor3ub(0,0,0);
                            glTranslatef(i*this->width*1.4, 0, 0);
                            glPushMatrix();
                                glScalef(0.2, 0.6, 0.1);
                                draw_custom_cube(1);
                            glPopMatrix();
                            glTranslatef(0, 0, -this->width/100);
                            glColor3ub(255,255,255);
                            glPushMatrix();
                                glScalef(0.18, 0.55, 0.09);
                                draw_custom_cube(1);
                            glPopMatrix();
                        glPopMatrix();
                    }

                    // stiker
                    char ded_string[] = "SUS";
                    glTranslatef(-this->width/1.75, -this->width*1.2, this->width/5);
                    glLineWidth(10);
                    glColor3ub(0,0,0);
                    glPushMatrix();
                        glScalef(0.007, 0.01, 0.01);
                        int len = (int) strlen(ded_string);
                        for (int i = 0; i < len; i++) {
                            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ded_string[i]);
                        }
                    glPopMatrix();


                glPopMatrix();
                
                glColor3ub(100, 100, 100);
                draw_slate();


                //roda karet
                glColor3ub(0, 0, 0);
                for(auto com: compass){
                    glPushMatrix();
                        glTranslatef(this->width*com[0], -this->width, this->width*1.4*com[1]);
                        glRotatef(90, 0, 1, 0);
                        draw_roda(this->width/2.5);
                    glPopMatrix();
                }

                //roda velg
                glColor3ub(200, 200, 200);
                int i = 0;
                for(auto com: compass){
                    glPushMatrix();
                        glTranslatef(this->width*com[0]*1.1, -this->width, this->width*1.4*com[1]);
                        glRotatef(90, 0, 1, 0);
                        if(i > 1){
                            glRotatef(180, 0, 1, 0);
                        }
                        draw_roda(this->width/5.);
                    glPopMatrix();
                    i++;
                }   
            glPopMatrix();
        }
        void draw_slate(){
            glPushMatrix();
                glTranslatef(0, -1, 0);
                glPushMatrix();
                    glScalef(this->width*1.25, 0.25, this->width*2);
                    draw_custom_cube(1);
                glPopMatrix();
                glTranslatef(0, -.75, 0);
                glPushMatrix();
                    glScalef(this->width*1.25, 0.5, this->width*0.75);
                    draw_custom_cube(1);
                glPopMatrix();
                glPushMatrix();
                    glScalef(this->width*0.75, 0.5, this->width*2);
                    draw_custom_cube(1);
                glPopMatrix();
            glPopMatrix();
        }
        
    private:
        float trukP[3];
        float width = 2;
};

Kepala_Truk *kepala_truk = new Kepala_Truk(0, 0, 11);
Kontainer *kontainers = new Kontainer[13];

void orientCamera();
void movePlayer(float maju_mundur, float kanan_kiri);
void fpsGaming(int x1, int y1);
void draw_asphalt();
void Reshape(int w1, int h1);

void display() {
    auto start = high_resolution_clock::now();
    movePlayer(x_step, z_step);
    orientCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_asphalt();
    kepala_truk->draw_truk();

    for(int i = 0, col = 0, col_step = 1; i < 13; i++){
        glColor3ubv(mejikuhibiniu[col]);
        kontainers[i].draw_kon();
        if(i == 6) col_step*=-1;
        col+=col_step;
    }

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

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_NONE);


    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);

    for(int i = 0; i < 13; i++) kontainers[i] = Kontainer(0, 0, -i*12);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_SIZE[0], WIN_SIZE[1]);
    glutCreateWindow("SUS truck");
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


void draw_asphalt(){
    glColor3f(0.1, 0.1, 0.1);
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0, 0.01, 0);
        glRectf(-5, -50, 5, 150);
    glPopMatrix();
}

// https://stackoverflow.com/a/1568687/13052716 with modif
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
    glutWarpPointer(w / 2, h / 2);
    yaw += (int)1*dx;
    pitch += (int)1*dy;
    if(pitch>=179) pitch =179;
    else if(pitch<1) pitch=1;
}

void Reshape(int w1, int h1) {
    // Fungsi reshape
    float ratio;
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    mposx = w/2;
    mposy = h/2;
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