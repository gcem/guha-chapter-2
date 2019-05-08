// 
// Ring
//
// Interaction:
// +/-: change the number of vertices
//
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
static float R = 30;
static int vertices = 40;

void drawScene(void)
{
  float angle;
  
  glClear(GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  glColor3f(0.0, 0.0, 0.0);

  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i <= vertices; i++)
    {
      angle = 2 * PI * i / vertices;
      glVertex3f(R * cos(angle), R * sin(angle), -40.0);
      glVertex3f(R * cos(angle), R * sin(angle), -50.0);
    }

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
  glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0);
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
    // case 32:
    //   wire = !wire;
    //   break;
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
