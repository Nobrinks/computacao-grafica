/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor, Vinicius Sathler, Igor Silva
 */

#include <GL/glut.h>
#include <bits/stdc++.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define BLUE 0, 0, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define CYAN 0, 1, 1
#define YELLOW 1, 1, 0
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1

#define NOCOLOR -1

enum Estados{
	P1, P2, P3
};
//	L1	L5
//	L2	L6
//	L3	L7
//	L4	L8
enum Pernas{
	L1, L2, L3, L4, L5, L6, L7, L8
};

using namespace std;

Estados estado;
int winHeight = 800, winWidth = 800, stacks = 500;
GLdouble r_torax = 0.2, r_abd = 0.3, direcao;

pair<GLdouble, GLdouble> normalizeCoordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)winHeight)*x -1, (-2.0/(double)winWidth)*y +1);
}

GLuint texID[1];  // Texture ID's for the three textures.
char* textureFileNames[1] = {   // file names for the files from which texture images are loaded
            "textures/spider_fur.jpg",
       };
GLUquadricObj *quadricObj = gluNewQuadric();

void init(){
	estado = Estados::P1;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawSpiderBody(){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texID[0] );  // Bind texture #0 for use on the spider body.
        glColor3f(WHITE);

        glTranslated(0, 0, -1);
        glutSolidTeapot(0.2);

        glTranslated(0, -r_abd-r_torax, 0);
        gluQuadricDrawStyle(quadricObj, GLU_FILL);
        gluSphere(quadricObj, 0.3, 20, 20);
        gluQuadricTexture(quadricObj, GL_TRUE);
        
    glPopMatrix();

}

void display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glViewport(0, winHeight/2, winWidth/2, winHeight/2);
    glLoadIdentity(); 
    gluLookAt(0, 1, -1, 0, 0, -1, 0, 0, -1);
    drawSpiderBody();
    
    
    glViewport(winWidth/2, winHeight/2, winWidth/2, winHeight/2);
    glLoadIdentity();//isso aqui faz com que as coisas que resete matrizes anteriores 
    gluLookAt(-1, 0, -1, 0, 0, -1, 0, 1, 0);
    drawSpiderBody();
    
    glViewport(0, 0, winHeight/2, winWidth/2);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 0, -0.2, 0, -1, 0, 1, 0);
    drawSpiderBody();

    glViewport(winWidth/2, 0,  winWidth/2, winHeight/2);
    glLoadIdentity();
    drawSpiderBody();
    //glViewport(winWidth/2, winHeight/2, winWidth, winHeight/2);

    glFlush();
}

void loadTextures() {
	int width, height, nrChannels;
	unsigned char *data;

	glGenTextures(1, texID);

	for(int i = 0; i < 1;i++)
	{
        glBindTexture(GL_TEXTURE_2D, texID[i]);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture

        data = stbi_load(textureFileNames[i], &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri  (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
        }
        else
        {
            printf("Failed to load texture\n");
        }
        stbi_image_free(data);
	}
}

int main(int argc, char** argv){
    glutInit(&argc, argv);      
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Trabalho 2");
    init();
    loadTextures();
    glutDisplayFunc(display);
    //glutMouseFunc(mouse);
    //glutTimerFunc(50, update, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}