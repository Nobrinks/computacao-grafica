#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
GLuint texture;
double angle = 0;
typedef struct
{
    int X;
    int Y;
    int Z;
    double U;
    double V;
}VERTICES;

const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];
GLuint LoadTextureRAW( const char * filename );



void DisplaySphere (double R, GLuint texture)
{

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int b;
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    //glRotatef (90, 1, 0, 0);
   glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
    }



for ( b = 0; b <VertexCount; b++)
{

    glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);

    glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);

}

    glEnd();
}
void CreateSphere (double R, double H, double K, double Z) {
    int n;
    double a;
    double b;
    n = 0;
for( b = 0; b <= 90 - space; b+=space){

    for( a = 0; a <= 360 - space; a+=space)
    {
        VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
        VERTEX[n].V = (2 * b) / 360;
        VERTEX[n].U = (a) / 360;

        n++;
        VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
        VERTEX[n].V = (2 * (b + space)) / 360;
        VERTEX[n].U = (a) / 360;
        n++;
        VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
        VERTEX[n].V = (2 * b) / 360;
        VERTEX[n].U = (a + space) / 360;
        n++;
        VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /180 * PI) - H;
        VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /180 * PI) + K;
        VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
        VERTEX[n].V = (2 * (b + space)) / 360;
        VERTEX[n].U = (a + space) / 360;
        n++;
    }

}
}
void display (void) {

    glClearDepth(1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-10);
    glRotatef(angle,0,1,0);
    DisplaySphere(5, texture);
    glutSwapBuffers();
    angle ++;
}
void init (void) {
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );

    glDepthFunc(GL_LEQUAL);

    texture= LoadTextureRAW( "textures/spider_fur.jpg" );

    CreateSphere(30,0,0,0);
}
void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

    glMatrixMode (GL_MODELVIEW);
}
int main (int argc, char **argv) {

    glutInit (&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize (500, 500);

    glutInitWindowPosition (100, 100);

    glutCreateWindow ("A basic OpenGL Window");

    init();

    glutDisplayFunc (display);

    glutIdleFunc (display);

    glutReshapeFunc (reshape);

    glutMainLoop ();

    return 0;
}
GLuint LoadTextureRAW( const char * filename )
{

  GLuint texture;

  int width, height;

  unsigned char * data;

  FILE * file;



  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;



  width = 1024;

  height = 512;

  data = (unsigned char *)malloc( width * height * 3 );


    //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );

  fclose( file );

for(int i = 0; i < width * height ; ++i)
{
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];
    //B = data[index];
    data[index] = R;
    data[index+2] = B;

}


    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data );

return texture;
}

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLuint tex;
GLUquadric* sphere;

void make_tex(void)
{
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
	for (int x = 0; x < 255; x++) {
	    unsigned char *p = data[y][x];
	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
	}
    }
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void draw(void)
{
    glClearColor(0.5, 0.5, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0,-2.0);
    glRotatef(45, 0, 1, 0);

    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.0, 32, 16);

    glutSwapBuffers();
}

void resize(int w, int h)
{
    if (!h)
	h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0*w/h, 0.1, 100.0);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    make_tex();
    sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 512);

    glutCreateWindow("Test");

    glutDisplayFunc(draw);
    glutReshapeFunc(resize);

    init();

    glutMainLoop();
}

*/