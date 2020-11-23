#include <GL/glut.h>

#define RED 1
#define BLUE 2
#define YELLOW 3
#define BLACK 4

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
  glutCreateWindow("Exercicio 1");
  
  // define a cor de background da janela
  glClearColor(0, 1.0, 0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
}

void writePolygon(float polygon[]) {
  glVertex3f(polygon[0], polygon[1], polygon[2]);
}

// Cria um losango
float** getLozenge(Point2d center, float size) {
  float** cube = (float **) malloc(4 * sizeof(float*));
  for (int i = 0; i < 4; i++) {
    cube[i] = (float* ) malloc(3 * sizeof(float));
  }
  
  float cubeAux[4][3] = {
    {center.x - (float) (size * 0.8), center.y, 0},
    {center.x, center.y + size, 0},
    {center.x + (float) (size * 0.8), center.y, 0},
    {center.x, center.y - size, 0}
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      cube[i][j] = cubeAux[i][j];
    }
  }

  return cube;
}

void printLozenge(float** lozenge, int color) {
  glBegin(GL_POLYGON);
    switch (color) {
      case RED:
        glColor3f(1, 0, 0);
        break;
      case BLUE:
        glColor3f(0, 0, 1);
        break;
      case YELLOW:
        glColor3f(1, 1, 0);
        break;
      case BLACK:
        glColor3f(0, 0, 0);
        break;
      default:
        break;
    }
    for (int vertice = 0; vertice < 4; vertice ++) {
      writePolygon(lozenge[vertice]);
    }
    
  glEnd();
}

void display() {
  // Limpa a janela, colocando na tela a cor definida pela função glClearColor
  glClear(GL_COLOR_BUFFER_BIT);
  float** bigLozenge = getLozenge(Point2d(0, 0), 0.4);

  float size = 0.3;
  printLozenge(getLozenge(Point2d(bigLozenge[0][0], bigLozenge[0][1]), size), YELLOW);
  printLozenge(getLozenge(Point2d(bigLozenge[1][0], bigLozenge[1][1]), size), BLUE);
  printLozenge(getLozenge(Point2d(bigLozenge[2][0], bigLozenge[2][1]), size), RED);
  printLozenge(getLozenge(Point2d(bigLozenge[3][0], bigLozenge[3][1]), size), BLACK);

 // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
  glFlush();
}

int main(int argc, char** argv)
{

 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  
  init();
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}