// 
// The letter 'A'
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

using namespace std;


void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  // left and right sides
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(50.0, 70.0, 0.0);
  glVertex3f(30.0, 30.0, 0.0);
  glVertex3f(15.0, 30.0, 0.0);
  glVertex3f(42.0, 84.0, 0.0);
  glVertex3f(58.0, 84.0, 0.0);
  glVertex3f(85.0, 30.0, 0.0);
  glVertex3f(70.0, 30.0, 0.0);
  glEnd();

  // middle line
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(37.0, 44.0, 0.0);
  glVertex3f(42.0, 54.0, 0.0);
  glVertex3f(63.0, 44.0, 0.0);
  glVertex3f(58.0, 54.0, 0.0);
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
