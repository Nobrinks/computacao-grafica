#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector> 
using namespace std;

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

  void print() {
    cout << "(" << x << ", " << y << ")" << endl;
  }

  string toString() {
    return ("(" + to_string(x) + ", " + to_string(y) + ")");
  }
};

vector<Point2d> windowDots;

void init(void);
void display(void);

void init(void) {
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
}

void writeDot(Point2d dot) {
  glVertex3f(dot.x, dot.y, 0);
}

void printDots(vector<Point2d> &windowDots) {
  glPointSize(50);
  glBegin(GL_POINTS);
  glColor3f(0, 0, 0);
  for (int vertice = 0; vertice < windowDots.size(); vertice ++) {
    writeDot(windowDots[vertice]);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  printDots(windowDots);
  glFlush();
}

Point2d mapDot(GLint windowX, GLint windowY) {
  return Point2d(
    ((windowX - ((glutGet(GLUT_WINDOW_WIDTH) / 2.0f))) / glutGet(GLUT_WINDOW_WIDTH)) * 2.0,
    ((glutGet(GLUT_WINDOW_HEIGHT) / 2.0f) - windowY) / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f);
}

void mouse(GLint button, GLint action, GLint x, GLint y) {
  switch(button) {
    case GLUT_LEFT_BUTTON:
      if (action == GLUT_DOWN) {
        windowDots.push_back(mapDot(x, y));
      }
      break;
    case GLUT_RIGHT_BUTTON:
      windowDots.clear();
      break;
    default: 
      break;
  }
  display();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize (600, 600);
  glutInitWindowPosition (200, 200);
  glutCreateWindow ("Tarefa 2");

  init();

  glutDisplayFunc(display);

  glutMouseFunc(mouse);
  glutMainLoop();

  return 0;
}