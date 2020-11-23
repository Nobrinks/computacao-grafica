/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor
 */

#include <GL/glut.h>
#include <bits/stdc++.h>
#include <math.h>

#define BLUE 0, 0, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define CYAN 0, 1, 1
#define YELLOW 1, 1, 0
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1

using namespace std;

int const HEIGHT = 800, LENGTH = 800, STACKS = 1000, PI = 3.1415;

double radian, speed = 10, rot;

GLint click = 0;
pair<GLdouble, GLdouble> pos, obj;

pair<GLdouble, GLdouble> normalize_coordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)LENGTH)*x -1, (-2.0/(double)HEIGHT)*y +1);
}

void spider_body(GLdouble radius){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	for(GLint i = 0; i<STACKS; i++){
		glColor3f(0, 0, 255);
		GLdouble theta = (2.0f * 3.14159265359 * i)/STACKS;
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
	GLdouble distance_x = pos.first - obj.first;
	GLdouble distance_y = pos.second - obj.second;

	switch(button){
		case GLUT_LEFT_BUTTON:
			pos = normalize_coordinates(x,y);
			if (sqrt(pow(pos.first,2) + pow(pos.second,2)) < speed){
				
			}
			click = 1;
			break;
		default:
			break;
	}
}
void move_spider(int value){
	mouse();
	glutPostRedisplay();
	glutTimerFunc(10,move_spider,0);
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
   glutInitWindowSize(LENGTH,HEIGHT);
   glutCreateWindow("Tarefa 2");
   init();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMainLoop();
   return EXIT_SUCCESS;
}
