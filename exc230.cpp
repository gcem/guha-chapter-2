// 
// The number 8, using 4 circles
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
#define VERTICES 40

using namespace std;


void drawCircle(float x, float y, float r, float depth)
{
  float angle;

  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(x, y, 0.0);
  for (int i = 0; i <= VERTICES; i++)
    {
      angle = 2 * PI * i / (float) VERTICES;
      glVertex3f(x + cos(angle) * r, y + sin(angle) * r, depth);
    }
  glEnd();
}

void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glEnable(GL_DEPTH_TEST);
  
  glColor3f(0.0, 0.5, 0.3);
  drawCircle(50.0, 32.0, 25.0, 0.0);
  drawCircle(50.0, 68.0, 25.0, 0.0);
  
  glColor3f(1.0, 1.0, 1.0);
  drawCircle(50.0, 32.0, 10.0, 0.1);
  drawCircle(50.0, 68.0, 10.0, 0.1);
  
  glDisable(GL_DEPTH_TEST);
  
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

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
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
