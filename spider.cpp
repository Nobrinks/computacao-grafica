/*
 * spider.cpp
 *
 *  Created on: 23 de out. de 2020
 *      Author: Paulo Victor, Vinicius Sathler, Igor Silva
 */

#include <GL/glut.h>
#include <bits/stdc++.h>

#define BLUE 0, 0, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define CYAN 0, 1, 1
#define YELLOW 1, 1, 0
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1

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
	POS, FEMURI, FEMURS, TIBIAI, TIBIAS
};

using namespace std;

int const height = 800, length = 800, stacks = 1000;
GLdouble radian, speed = 0.10;
GLdouble const spider_body_r = 0.05, spider_head_r = 0.1;

pair<GLdouble, GLdouble> pos, obj;
GLdouble direcao, p1= 20, p2=0, p3=-20, p4=-40;
Estados estado;

GLdouble const Val[8][3][5] = {
	//l1
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			p1,40,0.15,-20,0.05
		},
		//p2
		{
			p1,50,0.17,-20,0.04
		},
		//p3
		{
			p1,40,0.10,-30,0.04
		}
	},
	//l2
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			p2,30,0.07,-80,0.10
		},
		//p2
		{
			p2,20,0.07,-70,0.10
		},
		//p3
		{
			p2,40,0.07,-80,0.10
		}
	},
	//l3
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			p3,40,0.07,-80,0.10
		},
		//p2
		{
			p3,45,0.07,-80,0.10
		},
		//p3
		{
			p3,35,0.07,-80,0.10
		}
	},
	//l4
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			p4,50,0.07,-80,0.15
		},
		//p2
		{
			p4,30,0.07,-70,0.20
		},
		//p3
		{
			p4,55,0.07,-90,0.12
		}
	},
	//l5
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			180-p1,-40,0.15,20,0.05
		},
		//p2
		{
			180-p1,-40,0.10,30,0.04
		},
		//p3
		{
			180-p1,-50,0.17,20,0.04
		}
	},
	//l6
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			180-p2,-30,0.07,80,0.10
		},
		//p2
		{
			180-p2,-40,0.07,80,0.10
		},
		//p3
		{
			180-p2,-20,0.07,70,0.10
		}
	},
	//l7
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			180-p3,-40,0.07,80,0.10
		},
		//p2
		{
			180-p3,-35,0.07,80,0.10
		},
		//p3
		{
			180-p3,-45,0.07,80,0.10
		}
	},
	//l8
	{
		//p1
		{
			//POS, FEMURI, FEMURS, TIBIAI, TIBIAS
			180-p4,-50,0.07,80,0.15
		},
		//p2
		{
			180-p4,-55,0.07,90,0.12
		},
		//p3
		{
			180-p4,-30,0.07,70,0.20
		}
	},
};

pair<GLdouble, GLdouble> normalizeCoordinates(GLdouble x, GLdouble y){
	return make_pair((2.0/(double)length)*x -1, (-2.0/(double)height)*y +1);
}

GLdouble directionVector(pair<GLdouble, GLdouble> pos, pair<GLdouble, GLdouble> obj){
	GLdouble theta = (180*(atan2(obj.second-pos.second, obj.first-pos.first)))/M_PI;;
	if(theta < 0) theta += 360;
	return theta-90;
}

void spiderBody(GLdouble radius){
	glBegin(GL_LINE_LOOP);
	for(GLint i = 0; i<stacks; i++){
		glColor3f(BLUE);
		GLdouble theta = (2.0f * 3.14159265359 * i)/stacks;
		GLdouble border_x = radius*cosf(theta), border_y = radius*sinf(theta);
		glVertex2f(border_x, border_y);
	}
	glEnd();
}

void drawLeg(Pernas perna, Estados estado){
	glPushMatrix();
		glRotated(-Val[perna][estado][POS], 0.0, 0.0, 1.0);
		glTranslated(-spider_body_r, 0 , 0.0);
		glRotated(-Val[perna][estado][FEMURI], 0.0, 0.0, 1.0);
		glTranslated(-Val[perna][estado][FEMURS], 0 , 0.0);
		glRotated(-Val[perna][estado][TIBIAI], 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glColor3f(BLUE);
			glVertex3f(0, 0, 0);
			glVertex3f(-Val[perna][estado][TIBIAS], 0 , 0);
		glEnd();
		glRotated(Val[perna][estado][TIBIAI], 0.0, 0.0, 1.0);
		glTranslated(Val[perna][estado][FEMURS], 0 , 0.0);
		glBegin(GL_LINES);
			glColor3f(BLUE);
			glVertex3f(0, 0, 0);
			glVertex3f(-Val[perna][estado][FEMURS], 0 , 0);
		glEnd();
		glRotated(Val[perna][estado][FEMURI], 0.0, 0.0, 1.0);	
		glTranslated(spider_body_r, 0 , 0.0);
		glRotated(Val[perna][estado][POS], 0.0, 0.0, 1.0);
	glPopMatrix();
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslated(pos.first, pos.second, 0.0);
		glRotated(direcao, 0.0, 0.0, 1.0);
		spiderBody(spider_body_r);
		for(int i = Pernas::L1; i<= Pernas::L8; i++) drawLeg(Pernas(i), estado);
		glPushMatrix();
			glTranslated(0, -spider_body_r-spider_head_r, 0.0);
			spiderBody(spider_head_r);
		glPopMatrix();
	glPopMatrix();
  	glutSwapBuffers();
}

void mouse(GLint button, GLint state, GLint x, GLint y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){
				obj = normalizeCoordinates(x,y);
				direcao = directionVector(pos, obj);
				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}

void move_spider(){
	GLdouble distance_x = obj.first - pos.first;
	GLdouble distance_y = obj.second - pos.second;


	if (sqrt(pow(distance_x,2) + pow(distance_y,2)) < speed){
		pos.first = obj.first;
		pos.second =obj.second;
		estado = P1;
	}
	else{
		if(estado == Estados::P2) estado = Estados::P3;
		else estado = Estados::P2;
		radian = (direcao+90)*M_PI / 180;
		pos.first += cos(radian) * speed;
		pos.second += sin(radian) * speed;
	}
}

void update(int value){
	move_spider();
	glutPostRedisplay();
	glutTimerFunc(500,update,0);

}
void init(){
	estado = Estados::P1;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);      
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(200,200);
   glutInitWindowSize(length,height);
   glutCreateWindow("Tarefa 2");
   init();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutTimerFunc(50, update, 0);
   glutMainLoop();
   return EXIT_SUCCESS;
}
