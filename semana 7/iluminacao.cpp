// TeaPot3D.cpp - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualiza??o
// de objetos 3D.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLint especMaterial = 60;
GLfloat posX = 0.0, posY = -50.0, posZ = -50.0;
float R = 1.0, G = 1.0, B = 1.0; 
// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.1,0.1,0.1,1.0};
	GLfloat luzDifusa[4]={0.0,1.0,1.0,1.0}; // "cor"
	GLfloat luzEspecular[4]={R, G, B, 1};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	GLfloat luzEspecular1[4]={1.0, 0.0, 0.0, 1};// "brilho"
	GLfloat posicaoLuz1[4]={posX, posY, posZ, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};

	for (int i = 0; i < 3; i++)
	{
		luzEspecular[i] /= luzEspecular[3]; 
	}
	
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	
	//define os parâmetros de luz de numero 1
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1 );
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);


}
// Fun??o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela de visualiza??o com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	DefineIluminacao();


	// Desenha um cubo
	glBegin(GL_POLYGON); // Face posterior
	glNormal3f(0,0,1); // Normal da face
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glEnd();
	glBegin(GL_POLYGON); // Face frontal
	glNormal3f(0,0,-1); // Normal da face
	glVertex3f(50.0, 50.0, -50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glEnd();
	glBegin(GL_POLYGON); // Face lateral esquerda
	glNormal3f(-1,0,0); // Normal da face
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glEnd();
	glBegin(GL_POLYGON); // Face lateral direita
	glNormal3f(1,0,0); // Normal da face
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(50.0, 50.0, -50.0);
	glEnd();
	glBegin(GL_POLYGON); // Face superior
	glNormal3f(0,1,0); // Normal da face
	glVertex3f(-50.0, 50.0, -50.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, -50.0);
	glEnd();
	glBegin(GL_POLYGON); // Face inferior
	glNormal3f(0,-1,0); // Normal da face
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glEnd();
	// Execu??o dos comandos de desenho
	glutSwapBuffers();
}


// Inicializa??o
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita a luz de número 1
	glEnable(GL_LIGHT1);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_FLAT);
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=50;

	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsZ = 180;
}


// Fun??o usada para especificar a posi??o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Especifica posi??o do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Fun??o usada para especificar o volume de visualiza??o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje??o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje??o
	glLoadIdentity();

	// Especifica a proje??o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);
	//glOrtho(-60,60,-60,60,-60,60);
	PosicionaObservador();
}


// Fun??o callback chamada quando o tamanho da janela ? alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens?es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre??o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


// Fun??o callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;
		case GLUT_KEY_F1: 	if (especMaterial <= 160) especMaterial += 5;
							break;
		case GLUT_KEY_F2:	if (especMaterial >= 0) especMaterial -= 5;
							break;

	}
	PosicionaObservador();
	glutPostRedisplay();
}
void keyboard (unsigned char key, int x, int y){
	switch (key)
	{
		case 'X':	posX++;
							break;
		case 'Y':   posY++;
							break;
		case 'Z':	posZ++;
							break;
		case 'x':	posX--;
							break;
		case 'y':   posY--;
							break;
		case 'z':	posZ--;
							break;	
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Programa Principal
int main()
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);

	// Especifica a posi??o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de um teapot com ilumina??o");

	glutKeyboardFunc(keyboard);

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);
	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
	// Registra a funcao callback para tratamento do redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);

	Inicializa();
	glutMainLoop();
}