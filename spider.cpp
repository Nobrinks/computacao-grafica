/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor
 */

#include <GL/glut.h>
#include <bits/stdc++.h>

#define BLUE 0, 0, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define CYAN 0, 1, 1
#define YELLOW 1, 1, 0
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1

using namespace std;

int const height = 800, length = 800, stacks = 1000;

GLint click = 0;
pair<GLdouble, GLdouble> pos, obj;

pair<GLdouble, GLdouble> normalize_coordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)length)*x -1, (-2.0/(double)height)*y +1);
}

void spider_body(pair<GLdouble,GLdouble> pos, GLdouble radius){
	glBegin(GL_LINE_LOOP);
	for(GLint i = 0; i<stacks; i++){
		glColor3f(0, 0, 255);
		GLdouble theta = (2.0f * 3.14159265359 * i)/stacks;
		GLdouble border_x = radius*cosf(theta), border_y = radius*sinf(theta);
		glVertex2f(border_x, border_y);
	}
	glEnd();
}
void display(){
	glClear (GL_COLOR_BUFFER_BIT);

	spider_body(pos, 0.5);//imagem cresce muito
	glScalef (1, 1, 0);
	if(click==1){
		//GLdouble pixelx = 220*(2.0/800.0) - 1, pixely = 1-220*(2.0/800.0);
		//glPushMatrix();

		spider_body(pos, 0.5);//imagem cresce muito
		glScalef (1, 1, 0);
		//spider_body(pixelx,pixely, 0.5, 10000);//real, mal se mexe, quanto maior mais ele desce
		//glPopMatrix();
	}
	glutSwapBuffers();;
}
void mouse(GLint button, GLint state, GLint x, GLint y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			pos = normalize_coordinates(x,y);
			click = 1;
			break;
		default:
			break;
		//case GLUT_RIGHT_BUTTON:
		//	click = 2;
		//	break;
	}
	glutPostRedisplay();
}

void init(){
	//define a cor do fundo da janela
	click = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//definem o sistema de visualiza��o; neste caso est�o definindo o tipo de posi��o/proje��o
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(200,200);
   glutInitWindowSize(length,height);
   glutCreateWindow("Tarefa 2");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMainLoop();
   return EXIT_SUCCESS;
}
