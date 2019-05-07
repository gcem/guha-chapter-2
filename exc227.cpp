// 
// Sine wave between -pi and pi
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

void drawScene(void)
{
  float angle;
  
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  // draw axes
  glBegin(GL_LINES);
  glVertex3f(50.0, 0.0, 0.0);
  glVertex3f(50.0, 100.0, 0.0);
  glVertex3f(0.0, 50.0, 0.0);
  glVertex3f(100.0, 50.0, 0.0);
  glEnd();

  // draw the sine wave
  glBegin(GL_LINE_STRIP);
  glColor3f(0.1, 0.1, 0.7);
  for (int i = 0; i <= SAMPLES; i++)
    {
      glVertex3f(50.0 + (2 * i - SAMPLES) / (float) SAMPLES * 30.0, 50.0 + sin((2 * i - SAMPLES) *  PI / SAMPLES) * 30.0, 0.0);
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
