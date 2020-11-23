#include <GL/glut.h>

class Point2d {
  public:
    float x;
    float y;
    
  Point2d(float x, float y) {
    this -> x = x;
    this -> y = y;
  }
};

void init(void);
void display(void);

void init(void) {
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Exercicio 2");
  
  glClearColor(1.0, 1.0, 0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
}

void writeLine(float polygon[]) {
  glVertex3f(polygon[0], polygon[1], polygon[2]);
}

void writePoint(float point[]) {
  glVertex3f(point[0], point[1], point[2]);
}

float** getCube(Point2d center, float size) {
  float** cube = (float **) malloc(4 * sizeof(float*));
  for (int i = 0; i < 4; i++) {
    cube[i] = (float* ) malloc(3 * sizeof(float));
  }
  
  float sizeX = (float) (size * 0.8);

  float cubeAux[4][3] = {
    {center.x - sizeX, center.y - size, 0},
    {center.x - sizeX, center.y + size, 0},
    {center.x + sizeX, center.y + size, 0},
    {center.x + sizeX, center.y - size, 0}
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      cube[i][j] = cubeAux[i][j];
    }
  }

  return cube;
}

float** getLine(Point2d beggin, Point2d end) {
  float** line = (float **) malloc(2 * sizeof(float*));
  for (int i = 0; i < 2; i++) {
    line[i] = (float* ) malloc(3 * sizeof(float));
  }
  
  float lineAux[2][3] = {
    {beggin.x, beggin.y, 0},
    {end.x, end.y, 0}
  };

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      line[i][j] = lineAux[i][j];
    }
  }

  return line;
}

void printLine(float** line) {
  glColor3f(1, 0, 0);
  glBegin(GL_LINE_LOOP);
    for (int vertice = 0; vertice < 2; vertice ++) {
      writeLine(line[vertice]);
    }
  glEnd();
}

void printCubeLine(float** cubeLine) {
  glPointSize(10);
  glColor3f(1, 0, 0);
  glBegin(GL_LINE_LOOP);
    for (int vertice = 0; vertice < 4; vertice ++) {
      writeLine(cubeLine[vertice]);
    }
  glEnd();

  glBegin(GL_POINTS);
    for (int vertice = 0; vertice < 4; vertice ++) {
      writePoint(cubeLine[vertice]);
    }
  glEnd();
}

void printPoint(Point2d point) {
  glPointSize(20.0);
  glColor3f(1, 1, 0);
  glBegin(GL_POINTS);
    glVertex3f(point.x, point.y, 0);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  float size = 15.0;
  glLineWidth(size);
  glPointSize(size);

  printCubeLine(getCube(Point2d(0, 0), 0.7));
  printLine(getLine(Point2d(0, -1.1), Point2d(0, 1.1)));
  printLine(getLine(Point2d(-1.1, 0), Point2d(1.1, 0)));
  printPoint(Point2d(0, 0));

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