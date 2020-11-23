#include <GL/glut.h>
#include <stdio.h>

GLfloat movebola=0.0;
GLint direcao=1;

void init(void);
void display(void);
void bola(int passo);
void keyboard(unsigned char key, int x, int y);

float max_x = 4;
float min_x = -4;
float max_y = 4;
float min_y = -4;

int rotate = 0;


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(min_x, max_x, min_y, max_y, -4, 4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void){

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);

//   if (rotate == 1)
//    {
// 	  glTranslatef(movebola, 0.0, 0.0);
	  glRotatef(15, 0.0, 0.0, 1.0);
// 	  glTranslatef(-movebola, 0.0, 0.0);
// 	  rotate = 0;
//    }


  glPointSize(15.0);
  glBegin(GL_POINTS);
  glVertex3f(movebola,0.0,0.0);
  glEnd();


  glutSwapBuffers();
 }

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
	exit(0);
	break;
  }
}

void bola(int passo)
{
if(direcao==1)
{
 movebola += (float)passo/50;

if(movebola >= max_x)
	{
		direcao = 0;
		rotate = 1;

	}
}
else
{
movebola -= (float)passo/50;

if(movebola <= min_x)
	{
		direcao = 1;
		rotate = 1;
	}
}

glutPostRedisplay();
glutTimerFunc(100,bola, 1);

}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Animacao 2D");
  init();
  glutDisplayFunc(display);
  glutTimerFunc(10,bola,1);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}