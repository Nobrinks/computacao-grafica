#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

const auto PI = acos(-1);

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

  void print(){
    cout << "(" << x << ", " << y << ")" << endl;
  }
};

void init(void);
void display(void);

void init(void) {
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Exercicio 3");
  
  // define a cor de background da janela
  glClearColor(0, 0, 0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
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

float** getStar3(Point2d center, float radius) {
  Point2d externPoint(center.x, center.y + radius);
  Point2d innerPoint(Point2d(center.x, center.y + (radius / 3.0f)).rotate(60));

  float angle = 120;
  float angleIterate = 0;
  float star[6][3];

  for (int i = 0; i < 3; i ++) {
    angleIterate = angle * (i + 1);
    star[i * 2][0] = externPoint.rotate(angleIterate).x;
    star[i * 2][1] = externPoint.rotate(angleIterate).y;
    star[i * 2][2] = 0;

    star[i * 2 + 1][0] = innerPoint.rotate(angleIterate).x;
    star[i * 2 + 1][1] = innerPoint.rotate(angleIterate).y;
    star[i * 2 + 1][2] = 0;
  }

  return copy3dArray(star, 6);
}

void printStar(float** star) {
  glColor3f(1, 0, 0); // vermelho
  glBegin(GL_LINE_LOOP);
    writePolygon(star[5]);
    writePolygon(star[0]);
    glColor3f(0, 0, 1);
    writePolygon(star[1]);
    writePolygon(star[2]);
    glColor3f(0, 1, 0); // verde
    writePolygon(star[3]);
    writePolygon(star[4]);
  glEnd();
}

void display() {
  glLineWidth(5.0);
  glClear(GL_COLOR_BUFFER_BIT);
  printStar(getStar3(Point2d(0.0, 0.0), 0.6));
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  init();
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}