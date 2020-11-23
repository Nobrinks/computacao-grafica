#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

const auto PI = acos(-1);
float mouseCoord[2];
bool  resetPoints = true;
float objCoord[2] = {0.5, 0.5};
float angle = 0;

void  display(void);
void  reshape(int w, int h);
int   main(int argc, char** argv);
void  init();
void  drawCircle(int sides, float radius);
void  drawTriangleEq(float size);
void  mapDot(GLint windowX, GLint windowY);
void  mouse(GLint button, GLint action, GLint x, GLint y);
float innerProduct(float* vetA, float* vetB, int vetSize);
float norm(float* vetA, int vetSize);
float vectorsAngle(float* vetA, float* vetB, int vetSize);
float angleObjMouse();

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
  glutMainLoop();
  return 0;
}

void init() {
  // define a cor de background da janela
  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho (-1, 1, -1, 1, -1, 1);
  glClearColor(0, 0, 0, 0);

}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  //glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glOrtho (-1, 1, -1, 1, -1, 1);
  glClearColor(0, 0, 0, 0);
}

void display(void) {
  if(resetPoints) {
    glClear(GL_COLOR_BUFFER_BIT);
  } else {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glPointSize(20);
    glBegin(GL_POINTS);
      glVertex3f(mouseCoord[0], mouseCoord[1], 0.0);
    glEnd();
  }
  glColor3f(0, 1, 0);
  glPushMatrix();
    
    glTranslatef(objCoord[0], objCoord[1], 0.0);
    glRotatef(angleObjMouse(), 0, 0, 1.0);
    drawCircle(32, 0.2);
    glPushMatrix();
      glTranslatef(0.0, 0.2, 0.0);
      drawTriangleEq(0.1);
    glPopMatrix();
  glPopMatrix();
  glutSwapBuffers();
  glFlush();
  cout << angleObjMouse() << endl;
}

void mouse(GLint button, GLint action, GLint x, GLint y) {
  switch(button) {
    case GLUT_LEFT_BUTTON:
      if (action == GLUT_DOWN) {
        mapDot(x, y);
        resetPoints = false;
      }
      break;
    case GLUT_RIGHT_BUTTON:
      resetPoints = true;
      break;
    default:
      break;
  }
  display();
}

float innerProduct(float* vetA, float* vetB, int vetSize) {
  float result = 0;
  for(int i = 0; i < vetSize; i++) {
    result = (vetA[i] * vetB[i]) + result;
  }
  return result;
}

float norm(float* vet, int vetSize) {
  float result = 0;
  for(int i = 0; i < vetSize; i++) {
    result = (vet[i] * vet[i]) + result;
  }
  return sqrt(result);
}

float vectorsAngle(float* vetA, float* vetB, int vetSize) {
  float angleVets = acos(innerProduct(vetA, vetB, vetSize) / (norm(vetA, vetSize) * norm(vetB, vetSize))) * 180.0 / PI;
  if (vetA[0] - vetB[0] < 0) {
    return angleVets;
  }
  return -angleVets;
}

float angleObjMouse() {
  float shiftObj[2] = {-objCoord[0], -objCoord[1]};
  float shiftMouse[2] = {mouseCoord[0] + shiftObj[0], mouseCoord[1] + shiftObj[1]};
  float angleShift = vectorsAngle(shiftObj, shiftMouse, 2);
  cout <<  angleShift << " " << angle << " ";
  angle = ((int) (angleShift - angle)) % 360;
  cout << angle << endl;
  return angleShift;
}

void mapDot(GLint windowX, GLint windowY) {
  mouseCoord[0] = (windowX * (2.0f / glutGet(GLUT_WINDOW_WIDTH))) - 1;
  mouseCoord[1] = 1 - (windowY * (2.0f / glutGet(GLUT_WINDOW_HEIGHT)));
}

void drawCircle(int sides, float radius) {
  glBegin(GL_POLYGON);
    for(int i = 0; i < sides; i++) {
      float theta = 2.0f * PI * float(i) / float(sides);
      glVertex2f(radius * cosf(theta), radius * sinf(theta));
    }
  glEnd();
}

void drawTriangleEq(float size) {
  glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCircle(3, size);
  glPopMatrix();
}