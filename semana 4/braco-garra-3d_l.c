#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define ESC 27

static int shoulderX = 0, shoulderY = 0, elbow = 0;
enum finger {index, middle, thumb};
int fingers[3] = {0, 0, 0};

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void makeArm() {
  glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glColor3f(1, 0, 0);
    glutSolidCube(1.0);
  glPopMatrix();
}

void makeForearm() {
  glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glColor3f(0, 1, 0);
    glutSolidCube(1.0);
  glPopMatrix();
}

void makeFinger() {
  /* origem posicionada no centro do dedo*/
  glTranslatef(0.2, 0.0, 0.0);
  glScalef(0.4, 0.15, 0.4);
  glutSolidCube(1.0);
}

void makeIndexFinger() {
  /* indicador */
  glPushMatrix();
    /* origem posicionada no início do dedo*/
    glTranslatef(0.0, -0.2, -0.3);
    glRotatef((GLfloat) fingers[index], 0.0, 0.0, 1.0);
    glColor3f(0, 0, 1);
    makeFinger();
  glPopMatrix();
}

void makeMiddleFinger() {
  /* medio */
  glPushMatrix();
    /* origem posicionada no início do dedo*/
    glTranslatef(0.0, -0.2, 0.3);
    glRotatef((GLfloat) fingers[middle], 0.0, 0.0, 1.0);
    glColor3f(0, 1, 1);
    makeFinger();
  glPopMatrix();
}

void makeThumbFinger() {
  /* polegar */
  glPushMatrix();
    /* origem posicionada no início do dedo*/
    glTranslatef(0.0, 0.2, 0.0);
    glRotatef((GLfloat) fingers[thumb], 0.0, 0.0, 1.0);
    glColor3f(1, 1, 0);
    makeFinger();
  glPopMatrix();
}

void makeFingers() {
  makeIndexFinger();
  makeMiddleFinger();
  makeThumbFinger();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
    /* origem posicionada no ombro */
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulderY, 0.0, 1.0, 0.0);
    glRotatef((GLfloat) shoulderX, 0.0, 0.0, 1.0);
    
    /* origem posicionada no centro do braço */ 
    glTranslatef(1.0, 0.0, 0.0);
    
    makeArm();
    
    /* origem posicionada no cotovelo */
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    /* origem posicionada no centro do antebraço*/
    glTranslatef(1.0, 0.0, 0.0);
    
    makeForearm();

    /* origem posicionada no pulso */
    glTranslatef(1.0, 0.0, 0.0);

    makeFingers();

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
}

int modifyAngle(int angle, int change) {
  return (angle + change) % 360;
}

int rotateAngle5(int angle, char direction) {
  if (direction == 'H' || direction == 'h') {
    return modifyAngle(angle, -5);
  } else if (direction == 'A' || direction == 'a') {
    return modifyAngle(angle, 5);
  }
}

void keyboard (unsigned char key, int x, int y) {
  switch (key) {
    case 's':
      shoulderX = rotateAngle5(shoulderX, 'h');
      break;
    case 'S':
      shoulderX = rotateAngle5(shoulderX, 'a');
      break;
    case 'b':
      shoulderY = rotateAngle5(shoulderY, 'h');
      break;
    case 'B':
      shoulderY = rotateAngle5(shoulderY, 'a');
      break;
    case 'e':
      elbow = rotateAngle5(elbow, 'h');
      break;
    case 'E':
      elbow = rotateAngle5(elbow, 'a');
      break;
    case 'i':
      fingers[index] = rotateAngle5(fingers[index], 'h');
      break;
    case 'I':
      fingers[index] = rotateAngle5(fingers[index], 'a');
      break;
    case 'm':
      fingers[middle] = rotateAngle5(fingers[middle], 'h');
      break;
    case 'M':
      fingers[middle] = rotateAngle5(fingers[middle], 'a');
      break;
    case 'p':
      fingers[thumb] = rotateAngle5(fingers[thumb], 'h');
      break;
    case 'P':
      fingers[thumb] = rotateAngle5(fingers[thumb], 'a');
      break;
    case ESC:
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500); 
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}