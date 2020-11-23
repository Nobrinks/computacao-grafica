#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

#define GLUT_KEY_SPACE ' '
const auto PI = acos(-1);

void init(void);
void display(void);


class Point2d {
  public:
    float x;
    float y;

  Point2d(float x, float y) {
    this -> x = x;
    this -> y = y;
  }

  Point2d(Point2d *point) {
    *this = point;
  }

  Point2d rotate(double angle) {
    float x,y ;
    angle = angle * PI / 180;
    x = (( this -> x) * cos(angle)) - (( this -> y) * sin(angle));
    y = (( this -> x) * sin(angle)) + (( this -> y) * cos(angle));
    return Point2d(x, y);
  }

  void print() {
    cout << "(" << x << ", " << y << ")" << endl;
  }
};

void init(void) {
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-1, 1, -1, 1, -1, 1);
}

void writePolygon(float polygon[]) {
  glVertex3f(polygon[0], polygon[1], polygon[2]);
}

float** copy3dArray(float array[][3], int rows) {
  float** arrAux = (float **) malloc(rows * sizeof(float*));
  for (int i = 0; i < rows; i++) {
    arrAux[i] = (float* ) malloc(3 * sizeof(float));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 3; j++) {
      arrAux[i][j] = array[i][j];
    }
  }

  return arrAux;
}

float** getCube(Point2d center, float width, float height) {
  float cubeAux[4][3] = {
    {center.x - width, center.y - height, 0},
    {center.x - width, center.y + height, 0},
    {center.x + width, center.y + height, 0},
    {center.x + width, center.y - height, 0}
  };

  return copy3dArray(cubeAux, 4);
}

float** getTriangle(Point2d p1, Point2d p2, Point2d p3) {
  float triangleAux[3][3] = {
    {p1.x, p1.y, 0},
    {p2.x, p2.y, 0},
    {p3.x, p3.y, 0},
  };

  return copy3dArray(triangleAux, 3);
}

float** getRoof(Point2d p1, Point2d p2, float height) {
  return getTriangle(p1, p2, Point2d((p1.x + p2.x) / 2.0f, p1.y + height));
}

void printHouseWall(float** wall) {
  glBegin(GL_POLYGON);
  glColor3f(0, 0, 1);
  for (int vertice = 0; vertice < 4; vertice ++) {
    writePolygon(wall[vertice]);
  }
  glEnd();
}

void printHouseRoof(float** roof) {
  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  for (int vertice = 0; vertice < 3; vertice ++) {
    writePolygon(roof[vertice]);
  }
  glEnd();
}

void printHouseDoor(float** door) {
  glBegin(GL_POLYGON);
  glColor3f(1, 1, 1);
  for (int vertice = 0; vertice < 4; vertice ++) {
    writePolygon(door[vertice]);
  }
  glEnd();
}

void printHouseWindon(float** windon) {
  glBegin(GL_POLYGON);
  glColor3f(1, 1, 1);
  for (int vertice = 0; vertice < 4; vertice ++) {
    writePolygon(windon[vertice]);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  float width = 0.6, height = 0.4;
  float** wall = getCube(Point2d(0.0, 0.0), width, height);
  printHouseWall(wall);
  printHouseRoof(getRoof(Point2d(wall[1][0], wall[1][1]), Point2d(wall[2][0], wall[2][1]), 0.4));
  printHouseDoor(getCube(Point2d(0.0, -0.06), width/3.6f, height/1.3f));

  float** window = getCube(Point2d(0.4, 0.1), 0.08, 0.06);
  float windowWidth = 0.075, windowHeight = 0.055;
  // printHouseWindon(getCube(Point2d(0.3, 0.0), 0.05, 0.0375));
  printHouseWindon(getCube(Point2d(window[0][0], window[0][1]), windowWidth, windowHeight));
  printHouseWindon(getCube(Point2d(window[1][0], window[1][1]), windowWidth, windowHeight));
  printHouseWindon(getCube(Point2d(window[2][0], window[2][1]), windowWidth, windowHeight));
  printHouseWindon(getCube(Point2d(window[3][0], window[3][1]), windowWidth, windowHeight));

  glFlush();
}

void keyboard(unsigned char key, GLint x, GLint y ) {
  static bool black = false;
  if (key == GLUT_KEY_SPACE && !black) {
    black = true;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    display();
    return;
  }
  black = false;
  glClearColor(1.0, 1.0, 1.0, 1.0);

  display();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize (800, 800);
  glutInitWindowPosition (200, 200);
  glutCreateWindow ("Tarefa 1");

  init();

  glutDisplayFunc(display);

  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}