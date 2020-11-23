#include <GL/glut.h>
#include <stdio.h>
using namespace std;
GLint winWidth = 900, winHeight = 600; //Initial display-window size.
GLfloat x0 = 25.0, y0 = 25.0, z0 = 50.0; //Viewing-coordinate origin.
GLfloat xref = 25.0, yref = 25.0, zref = 0.0;// Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.

// Set coordinate limits for the clipping window:
GLfloat xwMin = -100.0, ywMin = -100.0, xwMax = 100.0, ywMax = 100.0;
//Set positions for near and far clipping planes:
 GLfloat dnear = 50.0, dfar = 100.0;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

}
void displayFcn(void) {

	glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
    glMatrixMode( GL_MODELVIEW );
	/* Set parameters for a square fill area. */
	glColor3f(0.0, 1.0, 0.0);
// Set fill color to green.
	glPolygonMode(GL_FRONT, GL_FILL);

	glPushMatrix();
		glTranslatef(0,0, -50);
		glBegin(GL_POLYGON); // Face frontal
		glColor3f(1, 0, 0);
		glNormal3f(0,0,1); // Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, 0.0);
		glVertex3f(50.0, 50.0, 0.0);
		glVertex3f(0.0, 50.0, 0.0);
		glEnd();
		glBegin(GL_POLYGON); // Face traseira
		glColor3f(0.0, 1.0, 0.0);
		glNormal3f(0,0,-1); // Normal da face
		glVertex3f(0.0, 0.0, -50.0);
		glVertex3f(50.0, 0.0, -50.0);
		glVertex3f(50.0, 50.0, -50.0);
		glVertex3f(0.0, 50.0, -50.0);
		glEnd();
		glBegin(GL_POLYGON); // Face lateral esquerda
		glColor3f(1.0, 0.0, 1.0);
		glNormal3f(-1,0,0); // Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -50.0);
		glVertex3f(0.0, 50.0, -50.0);
		glVertex3f(0.0, 50.0, 0.0);
		glEnd();
		glBegin(GL_POLYGON); // Face lateral direita
		glColor3f(0.0, 0.0, 1.0);
		glNormal3f(1,0,0); // Normal da face
		glVertex3f(50.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, -50.0);
		glVertex3f(50.0, 50.0, -50.0);
		glVertex3f(50.0, 50.0, 0.0);
		glEnd();
		glBegin(GL_POLYGON); // Face superior
		glColor3f(1.0, 1.0, 0.0);
		glNormal3f(0,1,0); // Normal da face
		glVertex3f(0.0, 50.0, 0.0);
		glVertex3f(50.0, 50.0, 0.0);
		glVertex3f(50.0, 50.0, -50.0);
		glVertex3f(0.0, 50.0, -50.0);
		glEnd();
		glBegin(GL_POLYGON); // Face inferior
		glColor3f(0.0, 1.0, 1.0);
		glNormal3f(0,-1,0); // Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, -50.0);
		glVertex3f(0.0, 0.0, -50.0);
		glEnd();
	glPopMatrix();
	glFlush();
}
void reshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

void keyboard (unsigned char key, int x, int y){
	switch (key)
	{
		case 'q':	x0++;
							break;
		case 'w':   y0++;
							break;
		case 'e':	z0++;
							break;
		case 'a':	xref++;
							break;
		case 's':   yref++;
							break;
		case 'd':	zref++;
							break;
		case 'z':	Vx = 0;
							break;
		case 'x':   Vy = 0;
							break;
		case 'c':	Vz = 0;
							break;	
		case 'Q':	x0--;
							break;
		case 'W':   y0--;
							break;
		case 'E':	z0--;
							break;
		case 'A':	xref--;
							break;
		case 'S':   yref--;
							break;
		case 'D':	zref--;
							break;
		case 'Z':	Vx = 1;
							break;
		case 'X':   Vy = 1;
							break;
		case 'C':	Vz = 1;
							break;
    }
	printf("(x0, y0, z0,): (%f, %f, %f)\n", x0, y0, z0);
    displayFcn();
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A Square");
	init();
   	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();

 return 0;
}