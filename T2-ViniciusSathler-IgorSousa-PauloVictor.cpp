/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor, Vinicius Sathler, Igor Silva
 */

#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GL/glut.h>

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

enum Dados{
	APOS, OPOS, INCPOS, L, INCART
};

GLdouble const apos = 30;

GLdouble const Val[8][3][5] = {
    //l1
    {
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -60, 45, 0.25, 90
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l2
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -20, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l3
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, 20, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l4
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, 45, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l5
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -120, 45, 0.25, 90
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l6
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -160, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l7
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -200, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
	//l8
	{
		//p1
		{
			//APOS, OPOS, INCPOS, L, INCART
			apos, -225, 45, 0.20, 60
		},
		//p2
		{
			0, 0, 0, 0, 0
		},
		//p3
		{
			0, 0, 0, 0, 0
		}
	},
};

using namespace std;

Estados estado;
int winHeight = 800, winWidth = 800, stacks = 500;
GLdouble r_torax = 0.2, r_abd = 0.3, direcao, h_spider = 0;

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

void drawLeg(Pernas perna){
    GLdouble l1 = Val[perna][estado][Dados::L];
    GLdouble inc_articulacao = Val[perna][estado][Dados::INCART], inc_pos = Val[perna][estado][Dados::INCPOS];

    GLdouble pos_alpha = Val[perna][estado][Dados::APOS], pos_omega = Val[perna][estado][Dados::OPOS], h_pos = (r_abd-r_torax) + r_torax*(1 - cos((90-pos_alpha)*M_PI/180.0));
    GLdouble hl = l1*(sin(inc_pos*(M_PI/180.0)));
    GLdouble bl = inc_pos + inc_articulacao - 90;
    GLdouble l2 = (hl + h_pos)/(cos(bl*(M_PI/180.0)));

    glPushMatrix();
    glRotated(pos_omega, 0, 0, 1.0);
    glRotated(pos_alpha, 0, 1.0, 0);
    glTranslatef(-r_torax, 0, 0);

    glRotated(-pos_alpha-inc_pos, 0, 1.0, 0);
    glTranslated(-l1, 0, 0);
    glRotated(180-inc_articulacao, 0, 1.0, 0);
    glTranslated(-l2/2, 0, 0);
    glPushMatrix();
        glScaled(l2, 0.02, 0.02);
        glutSolidCube(1.0);
    glPopMatrix();
    glTranslated(l2/2, 0, 0);
    glRotated(-(180-inc_articulacao), 0, 1.0, 0);
    glTranslated(l1/2, 0, 0);
    glPushMatrix();
        glScaled(l1, 0.02, 0.02);
        glutSolidCube(1.0);
    glPopMatrix();
    glTranslated(l1/2, 0, 0);

    glRotated(pos_alpha+inc_pos, 0, 1.0, 0);

    glTranslated(r_torax, 0, 0);
    glRotated(-pos_alpha, 0, 1.0, 0);
    glRotated(-pos_omega, 0, 0, 1.0);
    glPopMatrix();
}

void drawSpiderBody(){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texID[0] );  // Bind texture #0 for use on the spider body.
        glColor3f(WHITE);
       
        //glTranslated(0, 0, -1);
        //gluSphere(quadricObj, r_torax, 20, 20);

        for(int i = Pernas::L1; i <= Pernas::L8; i++) drawLeg(Pernas(i));

        glutWireSphere(r_torax, 20, 20);

        glTranslated(0, -r_abd-r_torax, 0);
        gluQuadricDrawStyle(quadricObj, GLU_FILL);
        glutWireSphere(r_abd, 20, 20);

        //gluSphere(quadricObj, r_abd, 20, 20);
        //gluQuadricTexture(quadricObj, GL_TRUE);
        
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