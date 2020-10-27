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

void spider_body(GLdouble radius){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	//cout << pos.first << " " << pos.second << endl;
	glPushMatrix();
	glScalef (1, 1, 0);
	glTranslated(pos.first, pos.second, 0.0);
	spider_body(0.2);//imagem cresce muito
  	glPopMatrix();
  	glutSwapBuffers();
}

void mouse(GLint button, GLint state, GLint x, GLint y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			pos = normalize_coordinates(x,y);
			click = 1;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void init(){

	click = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char** argv) {
   glutInit(&argc, argv);      
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(200,200);
   glutInitWindowSize(length,height);
   glutCreateWindow("Tarefa 2");
   init();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMainLoop();
   return EXIT_SUCCESS;
}
