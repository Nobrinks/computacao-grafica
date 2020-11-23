#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#define IMP 0.0001
using namespace std;

const auto PI = acos(-1);
float mouseCoord[2];
bool  resetPoints = true;
float objCoord[2] = {0, 0};
bool  animSide = false;

void display();
void reshape(int w, int h);
int  main(int argc, char** argv);
void init();
void mapDot(GLint windowX, GLint windowY);
void mouse(GLint button, GLint action, GLint x, GLint y);
void drawQuad();
void keyboard(int key, int x, int y);
void anim(int step);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutSpecialFunc(keyboard);
  glutTimerFunc(100, anim, 1);
  glutMainLoop();
  return 0;
}

void init() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho (-1, 1, -1, 1, -1, 1);
  glClearColor(0, 0, 0, 0);
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_MODELVIEW);
  glOrtho (-1, 1, -1, 1, -1, 1);
  glClearColor(0, 0, 0, 0);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glColor3f(0, 1, 0);
  glTranslatef(objCoord[0], 0, 0);
  glScalef(0.2, 0.2, 0.2);
  //glTranslatef(objCoord[3], 0, 0);
  glColor3f(1.0, 1.0, 1.0);
  drawQuad();
  glutSwapBuffers();
  glFlush();
}

void mouse(GLint button, GLint action, GLint x, GLint y) {
  display();
}

void keyboard(int key, int x, int y) {
  cout << key << endl;
  switch(key) {
    case GLUT_KEY_LEFT: // d
      animSide = true;
      cout << "left" << endl;
      break;
    case GLUT_KEY_RIGHT: // f
      animSide = false;
      cout << "right" << endl;
      break;
    default:
      break;
  }
  display();
}

void drawQuad() {
  glBegin(GL_LINE_LOOP);
    glVertex3f(0.5, 0.5, 0);
    glVertex3f(0.5, -0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(-0.5, 0.5, 0);
  glEnd();
}

void anim(int step) {
  float v = 0.05;
  if (animSide) {
    v = -v;
  }
  objCoord[0] = objCoord[0] + v;
  if (objCoord[0] + 1.1 < IMP ) {
    objCoord[0] = 1.1;
  }
  if (objCoord[0] - 1.1 > IMP) {
    objCoord[0] = -1.1;
  }
  glutPostRedisplay();
  glutTimerFunc(200, anim, 1);
}