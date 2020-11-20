/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor, Vinicius Sathler, Igor Silva
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

#define NOCOLOR -1

enum Estados{
	P1, P2, P3
};
//	L1	L5
//	L2	L6
//	L3	L7
//	L4	L8
enum Pernas{
	L1, L2, L3, L4, L5, L6, L7, L8
};

using namespace std;

Estados estado;
int const height = 800, length = 800;
GLdouble r_torax, r_abd, direcao;


pair<GLdouble, GLdouble> normalizeCoordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)length)*x -1, (-2.0/(double)height)*y +1);
}

void init(){
	estado = Estados::P1;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glColor3f(BLACK);
    //gluSphere(gluNewQuadric(), 100, 100, 25);

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);      
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(length,height);
    glutCreateWindow("Trabalho 2");
    init();
    glutDisplayFunc(display);
    //glutMouseFunc(mouse);
    //glutTimerFunc(50, update, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}