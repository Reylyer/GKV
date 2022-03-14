#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>

static int shoulder = 0, elbow = 0, palm=0, index1 = 0, index2 = 0, middle1 = 0, middle2 = 0, ring1 = 0, ring2 = 0, pinkie1 = 0, pinkie2 = 0, thumb = 0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	
		glTranslatef(-1.0,0.0,0.0);
		glRotatef((GLfloat) shoulder, 0.0,0.0,1.0);
		glTranslatef(1.0,0.0,0.0);
		
		glPushMatrix();
			glScalef(2.0,0.4,1.0);
			glutWireCube(1.0);
		glPopMatrix();
		
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat) elbow, 0.0,0.0,1.0);
		glTranslatef(1.0,0.0,0.0);
		 
		glPushMatrix();
			glScalef(2.0,0.4,1.0);
			glutWireCube(1.0);
		glPopMatrix();
		
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat) palm, 0.0,0.0,1.0);
		glTranslatef(0.5,0.0,0.0);
		
		glPushMatrix();
			glScalef(1.0,0.4 ,1.0);
			glutWireCube(1.0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.5,0.0,0.0);
			glRotatef((GLfloat) index1, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.25,0.0,0.0);
			glRotatef((GLfloat) index2, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();	
			glTranslatef(0.5,0.0,0.0);
			glRotatef((GLfloat) middle1, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.25,0.0,0.0);
			glRotatef((GLfloat) middle2, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.5,0.0,-0.2);
			glRotatef((GLfloat) ring1, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.25,0.0,0.0);
			glRotatef((GLfloat) ring2, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.5,0.0,-0.4);
			glRotatef((GLfloat) pinkie1, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.25,0.0,0.0);
			glRotatef((GLfloat) pinkie2, 0.0,0.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			
			glPushMatrix();
				glScalef(0.5,0.2 ,0.20);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.2,0.0,0.4);
			glRotatef((GLfloat) thumb, -1.0,0.0,0.0);
			glTranslatef(0.0,0.0,0.25);
			
			glPushMatrix();
				glScalef(0.2,0.2 ,0.50);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,(GLfloat) w/ (GLfloat) h, 1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-5.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 's': shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
		case 'S': shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
		case 'e': elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
		case 'E' : elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
		case 'd': palm = (palm + 5) % 360;
		glutPostRedisplay();
		break;
		case 'D': palm = (palm - 5) % 360;
		glutPostRedisplay();
		break;
		case 'f': index1 = (index1 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'F': index1 = (index1 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'r': index2 = (index2 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'R': index2 = (index2 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'g': middle1 = (middle1 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'G': middle1 = (middle1 - 5) % 360;
		glutPostRedisplay();
		break;
		case 't': middle2 = (middle2 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'T': middle2 = (middle2 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'h': ring1 = (ring1 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'H': ring1 = (ring1 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'y': ring2 = (ring2 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'Y': ring2 = (ring2 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'j': pinkie1 = (pinkie1 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'J': pinkie1 = (pinkie1 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'u': pinkie2 = (pinkie2 + 5) % 360;
		glutPostRedisplay();
		break;
		case 'U': pinkie2 = (pinkie2 - 5) % 360;
		glutPostRedisplay();
		break;
		case 'k': thumb = (thumb + 5) % 360;
		glutPostRedisplay();
		break;
		case 'K': thumb = (thumb - 5) % 360;
		glutPostRedisplay();
		break;
		case 27: exit(0);
		break;
		default: break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}