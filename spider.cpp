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

int const height = 800, length = 800, stacks = 1000, PI = 3.1415;
GLdouble radian, speed = 0.05, rot;
GLdouble const spider_body_r = 0.15, spider_head_r = 0.05, leg_size = 0.08, paw_size = 0.07, articulacao = -20,inclinacao_max = -20;

pair<GLdouble, GLdouble> pos, obj;
GLdouble direcao, p1= 20, p2=0, p3=-20, p4=-40, inclinacao;
bool inclinado;

pair<GLdouble, GLdouble> normalizeCoordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)length)*x -1, (-2.0/(double)height)*y +1);
}

GLdouble directionVector(pair<GLdouble, GLdouble> pos, pair<GLdouble, GLdouble> obj){
	GLdouble theta = (180*(atan2(obj.second-pos.second, obj.first-pos.first)))/M_PI;;
	if(theta < 0) theta += 360;
	return theta-90;
}

void spiderBody(GLdouble radius){
	glBegin(GL_LINE_LOOP);
	for(GLint i = 0; i<stacks; i++){
		glColor3f(BLUE);
		GLdouble theta = (2.0f * 3.14159265359 * i)/stacks;
		GLdouble border_x = radius*cosf(theta), border_y = radius*sinf(theta);
		glVertex2f(border_x, border_y);
	}
	glEnd();
}

void drawLeg(GLdouble posicao, GLdouble inclinacao, bool inclinado){
	if(!inclinado) inclinacao = 0;
	glPushMatrix();
			glRotated(-posicao, 0.0, 0.0, 1.0);
			glTranslated(-spider_body_r, 0 , 0.0);
			glRotated(-inclinacao, 0.0, 0.0, 1.0);
			glTranslated(-leg_size, 0 , 0.0);
			if(posicao > 90 || posicao < -90) glRotated(articulacao, 0.0, 0.0, 1.0);
			else glRotated(-articulacao, 0.0, 0.0, 1.0);
			glBegin(GL_LINES);
			glColor3f(BLUE);
				glVertex3f(0, 0, 0);
				glVertex3f(-paw_size, 0 , 0);
			glEnd();
			if(posicao > 90 || posicao < -90) glRotated(-articulacao, 0.0, 0.0, 1.0);
			else glRotated(articulacao, 0.0, 0.0, 1.0);
			glTranslated(leg_size, 0 , 0.0);
			glBegin(GL_LINES);
			glColor3f(BLUE);
				glVertex3f(0, 0, 0);
				glVertex3f(-leg_size, 0 , 0);
			glEnd();
			glRotated(inclinacao, 0.0, 0.0, 1.0);
			glTranslated(spider_body_r, 0 , 0.0);
			glRotated(posicao, 0.0, 0.0, 1.0);
	glPopMatrix();
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslated(pos.first, pos.second, 0.0);
		glRotated(direcao, 0.0, 0.0, 1.0);
		spiderBody(spider_body_r);
		drawLeg(180-p4, inclinacao, inclinado);
		drawLeg(180-p3, inclinacao, !inclinado);
		drawLeg(180-p2, inclinacao, inclinado);
		drawLeg(180-p1, inclinacao, !inclinado);
		drawLeg(p4, inclinacao, !inclinado);
		drawLeg(p3, inclinacao, inclinado);
		drawLeg(p2, inclinacao, !inclinado);
		drawLeg(p1, inclinacao, inclinado);
		glPushMatrix();
			glTranslated(0, spider_body_r+spider_head_r, 0.0);
			spiderBody(spider_head_r);
		glPopMatrix();
	glPopMatrix();
  	glutSwapBuffers();
}

void mouse(GLint button, GLint state, GLint x, GLint y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){
				obj = normalizeCoordinates(x,y);
				direcao = directionVector(pos, obj);
				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}

void move_spider(){
	GLdouble distance_x = obj.first - pos.first;
	GLdouble distance_y = obj.second - pos.second;

	inclinado = !inclinado;

	if (sqrt(pow(distance_x,2) + pow(distance_y,2)) < speed){
		pos.first = obj.first;
		pos.second =obj.second;
		inclinacao = 0;
	}
	else{
		inclinacao = inclinacao_max;
		radian = (direcao+90)*M_PI / 180;
		pos.first += cos(radian) * speed;
		pos.second += sin(radian) * speed;
	}
}

void update(int value){
	move_spider();
	glutPostRedisplay();
	glutTimerFunc(50,update,0);

}
void init(){
	inclinado = false;
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
   glutTimerFunc(50, update, 0);
   glutMainLoop();
   return EXIT_SUCCESS;
}
