// 
// Ellipse
//
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
#define SAMPLES 50

using namespace std;

// Global variables
static float X = 50;
static float Y = 50;
static float A = 40;
static float B = 28;

void drawScene(void)
{
  float t;
  
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  // draw axes
  glBegin(GL_LINES);
  glVertex3f(50.0, 0.0, 0.0);
  glVertex3f(50.0, 100.0, 0.0);
  glVertex3f(0.0, 50.0, 0.0);
  glVertex3f(100.0, 50.0, 0.0);
  glEnd();

  // draw the ellipse
  glBegin(GL_LINE_LOOP);
  glColor3f(0.7, 0.0, 0.0);
  for (int i = 0; i < SAMPLES; i++)
    {
      t = 2 * PI / SAMPLES * i;
      glVertex3f(X + A * cos(t), Y + B * sin(t), 0.0);
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
    }
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
