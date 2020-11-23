#include <GL/glut.h>

void init();
void display();

GLint wsize_x = 900;
GLint wsize_y = 900;


void init() {
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);
  
  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-4, 4, -4, 4, -4, 4);
  
}

void lines()
{
  glBegin(GL_LINES);
  glVertex3f(-4.0, 0.0, 0.0);
  glVertex3f(4.0, 0.0, 0.0);
  glVertex3f(0.0, 4.0, 0.0);
  glVertex3f(0.0, -4.0, 0.0);
  glEnd();
}
void quad()
{
  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.5, -0.5, 0.0);
  glVertex3f(0.5, -0.5, 0.0);
  glVertex3f(0.5, 0.5, 0.0);
  glVertex3f(-0.5, 0.5, 0.0);
  glEnd();
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glColor3f(0.0, 0.0, 0.0);
  lines();
  
  glColor3f(1.0, 0.0, 0.0);
  quad();
  
  glPushMatrix();
  glTranslatef(1.0, 0.0, 0.0);
  glScalef(0.5,0.5,0);
  glColor3f(0.0, 1.0, 0.0);
  quad();
  glPopMatrix();
  
  glScalef(2.0,2.0,0);
  glColor3f(0.0, 0.0, 1.0);
  quad();
  
  
  glutSwapBuffers();
}


int main(int argc, char** argv) {
  
  //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
  //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);
  
  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  
  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize(wsize_x, wsize_y);
  glutInitWindowPosition(200, 200);
  
  // Cria uma janela e define seu título
  glutCreateWindow("Primeiro OpenGL");
  
  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();
  
  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);
  
  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();
  
  return 0;
  
}
