#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, fingers = 0, forefinger = 0, thumb = 0, middle_finger = 0, horizontal = 0;

void init(void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-5, 5, -5, 5, -5, 5);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
		// rotaciona o antebraco 
		glTranslatef (0.0, 0.0, 0.0);
		glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) horizontal, 0.0, 1.0, 0.0);
		glTranslatef (1.0, 0.0, 0.0);
        

		// desenho do antebraco 
		glPushMatrix();
            glColor3f(255.0, 0.0, 0.0);
            glScalef (2.0, 0.4, 1.0);
            glutSolidCube (1.0);
		glPopMatrix();

		//rotaciona braco 
		glTranslatef (1.0, 0.0, 0.0);
		glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
		glTranslatef (1.0, 0.0, 0.0);
		
		// desenho do braco
		glPushMatrix();
            glColor3f(0.0, 255.0, 0.0);
            glScalef (2.0, 0.4, 1.0);
            glutSolidCube (1.0);
		glPopMatrix();

			//polegar
			glPushMatrix();
				glTranslatef (1.0, -0.05, 0.0);
				glRotatef ((GLfloat) thumb, 0.0, 0.0, 1.0);
				glTranslatef (-0.2, -0.3, 0.0);
				glPushMatrix();
					glColor3f(0.7, 0.1, 0.7);
					glScalef (0.2, 0.6, 0.2);
					glutSolidCube (1.0);
				glPopMatrix();
			glPopMatrix();
			//medio
			glPushMatrix();
				glTranslatef (1.0, -0.05, -0.15);
				glRotatef ((GLfloat) middle_finger, 0.0, 0.0, 1.0);
				glTranslatef (0.15, -0.3, -0.15);
				glPushMatrix();
					glColor3f(0.7, 0.1, 0.3);
					glScalef (0.2, 0.6, 0.2);
					glutSolidCube (1.0);
				glPopMatrix();
			glPopMatrix();

			//indicador
			glPushMatrix();
				glTranslatef (1.0, -0.05, 0.15);
				glRotatef ( (GLfloat) forefinger, 0.0, 0.0, 1.0);
				glTranslatef (0.15, -0.3, 0.15);
				glPushMatrix();
					glColor3f(0.5, 0.7, 0.4);
					glScalef (0.2, 0.6, 0.2);
					glutSolidCube (1.0);
				glPopMatrix();
			glPopMatrix();


	glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'i':
		forefinger = (forefinger + 5) % 360;
		glutPostRedisplay();
		break;
	case 'I':
		forefinger = (forefinger - 5) % 360;
		glutPostRedisplay();
		break;
	case 'm':
		middle_finger = (middle_finger + 5) % 360;
		glutPostRedisplay();
		break;
	case 'M':
		middle_finger = (middle_finger - 5) % 360;
		glutPostRedisplay();
		break;
	case 'p':
		thumb = (thumb + 5) % 360;
		glutPostRedisplay();
		break;
	case 'P':
		thumb = (thumb - 5) % 360;
		glutPostRedisplay();
		break;
	case 'b':
		horizontal = (horizontal + 5) % 360;
		glutPostRedisplay();
		break;
	case 'B':
		horizontal = (horizontal - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1920, 720); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}