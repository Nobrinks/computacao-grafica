#include <GL/glut.h>

void init();
void display();

GLint wsize_x = 900;
GLint wsize_y = 900;

float alpha = 0;

void init() {
	// define a cor de background da janela
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// define o sistema de visualização - tipo de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, -4, 4);
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'R':
    alpha = 60;
    glutPostRedisplay();
    break;

  default:
    break;
  }
}

void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 
 glColor3f(0.0, 0.0, 0.0);
 
 glBegin(GL_LINES);
 glVertex3f(-4.0, 0.0, 0.0);
 glVertex3f(4.0, 0.0, 0.0);
 glVertex3f(0.0, 4.0, 0.0);
 glVertex3f(0.0, -4.0, 0.0);
 glEnd();
 
 glTranslatef(1.5, 0.5, 0.0);
 glRotatef(alpha, 0.0, 0.0, 1.0);
 glTranslatef(-1.5, -0.5, 0.0);
 
 glBegin(GL_QUADS);
 glVertex3f(1.0, 0.0, 0.0);
 glVertex3f(2.0, 0.0, 0.0);
 glVertex3f(2.0, 1.0, 0.0);
 glVertex3f(1.0, 1.0, 0.0);
 glEnd();
 
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
    
    glutKeyboardFunc(keyboard);
	//Inicia o loop de processamento de desenhos com GLUT.
	// Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
	glutMainLoop();

	return 0;

}

