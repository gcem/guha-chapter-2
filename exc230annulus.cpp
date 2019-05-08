// 
// The number 8 using circular annulus
// The middle line is created by trimming the edges of triangles.
// Triangles at the sides of the middle line get distorted. I think
// it is not possible to draw this shape without calculating
// those two endpoints separately (or making the triangles overlap)
//
// Interaction:
// space: switch between wireframe and filled drawing
// +/-: change the number of vertices
//

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#endif


#define PI 3.14159265358979324


using namespace std;

// Global variables
static float X = 50;
static float Y = 50;
static int vertices = 40;
static int wire = 0;

void drawCircAnn(float x, float y, float rout, float rin, float depth)
// draw a circular annulus with triangles facing +z
// (modified to trim the y coordinates and orient the annuluses)
{
  float angle;
  float yOut, xOut;
  
  glBegin(GL_TRIANGLE_STRIP);

  for (int i = 0; i <= vertices; i++)
    {
      angle = 2 * PI * i / (float) vertices;

      // orient the annulus so that it looks better with a low number of vertices
      if (y > 50.0)
	angle -= PI / 2;
      else
	angle += PI / 2;

      xOut = cos(angle) * rout;
      yOut = sin(angle) * rout;

      if (y < 50.0) // drawing the bottom circle
      	{
	  if (y + yOut > 50.0)
	    {
	      xOut = xOut * (50.0 - y) / yOut;
	      yOut = 50.0 - y;
	    }
      	}
      else
      	{
	  if (y + yOut < 50.0)
	    {
	      xOut = xOut * (50.0 - y) / yOut;
	      yOut = 50.0 - y;
	    }
      	}
      
      glVertex3f(x + cos(angle) * rin, y + sin(angle) * rin, depth);
      glVertex3f(x + xOut, y + yOut, depth);
    }
  glEnd();
}


void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);
  if (wire)
    glPolygonMode(GL_FRONT, GL_LINE);
  else
    glPolygonMode(GL_FRONT, GL_FILL);
  drawCircAnn(50.0, 32.0, 25.0, 10.0, 0.0);
  drawCircAnn(50.0, 68.0, 25.0, 10.0, 0.0);

  glEnd();

  glFlush();
}

void setup(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 1.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27:
      exit(0);
      break;
    case 32:
      wire = !wire;
      break;
    case 43:
      vertices++;
      break;
    case 45:
      if (vertices > 3)
	vertices--;
      break;
    }
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("window");
  glutDisplayFunc(drawScene);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup();

  glutMainLoop();
}
