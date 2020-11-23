#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define IMP 0.0001
using namespace std;

GLfloat x0 = 100.0, y0 = 50.0, z0 = 50.0; //Viewing-coordinate origin.
GLfloat xref = 50.0, yref = 50.0, zref = 0.0;// Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.

// Set coordinate limits for the clipping window:
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
//Set positions for near and far clipping planes:
GLfloat dnear = 25.0, dfar = 300;

GLfloat white[] = {1, 1, 1, 1};

void init();
void display();
void reshape(GLint newWidth, GLint newHeight);
void keyboard(int key, int x, int y);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Perspective View of A Square");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(keyboard);
  glutMainLoop();
  return 0;
}

void init() {
  GLfloat black[] = {0, 0, 0, 1};
  GLfloat yellow[] = {1, 1, 0, 1};
  GLfloat cyan[] = {0, 1, 1, 1};
  GLfloat direction[] = {0, -100, 0, 1.0};


  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glClearColor(0, 0, 0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
  /* Set parameters for a square fill area. */
  glColor3f(0.0, 1.0, 0.0);
  // Set fill color to green.
  glutSolidCube(50);
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
    glTranslatef(0, -100, 0);
    glutSolidSphere(5, 20, 20);
  glPopMatrix();

  glFlush();
}

void reshape(GLint newWidth, GLint newHeight) {
  glViewport(0, 0, newWidth, newHeight);
}

void keyboard(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT: // d
      x0 += 1;
      cout << "left" << endl;
      break;
    case GLUT_KEY_RIGHT: // f
      x0 += -1;
      cout << "right" << endl;
      break;
    case GLUT_KEY_UP: // f
      y0 += 1;
      cout << "Up" << endl;
      break;
    case GLUT_KEY_DOWN: // f
      y0 += -1;
      cout << "Down" << endl;
      break;
    default:
      break;
  }
  display();
}

