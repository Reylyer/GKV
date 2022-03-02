#include<stdlib.h>
#include<gl/glut.h>
#include<stdio.h>
#include<cmath>

float x1,x2,yy1,y2;

void display(void){
	float dy,dx,step,x,y,k,Xin,Yin;
	x1 = 1;
	yy1 = 1;
	x2 = 80;
	y2 = 60;
	dx= x2-x1;
	dy= y2-yy1;
	
	if(abs(dx)>abs(dy)){
		step = abs(dx);
	}
	else
		step = abs(dy);
		
	Xin = dx/step;
	Yin = dy/step;
	
	x = x1;
	y = yy1;
	
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	
	for (k=1; k<=step ; k++){
		x = x + Xin;
		y = y + Yin;
		
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}
	glFlush();
}

void init(void){
	glClearColor(0.7,0.3,0.7,0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-25,100,-25,100);
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(200,200);
	glutCreateWindow("DDA Line Algorithm untuk (1,1) hingga (80,60)");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
