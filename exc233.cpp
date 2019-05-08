// 
// Children's slide
//
// Interaction:
// +/-: move the slide up and down
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
static float Ybottom = -10.0;

void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(-0.4 * 50, Ybottom - 9.0, -50.0);
  glVertex3f(-0.4 * 50, Ybottom - 9.0, -60.0);
  for (float t = -0.8; t <= 0; t += 0.05)
    {
      glVertex3f((t + 0.4) * 50.0, Ybottom + 50.0 * t * t * t * t, -50.0);
      glVertex3f((t + 0.4) * 50.0, Ybottom + 50.0 * t * t * t * t, -60.0);
    }
  glVertex3f(0.4 * 50, Ybottom - 9.0, -50.0);
  glVertex3f(0.4 * 50, Ybottom - 9.0, -60.0);
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
  glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
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
      Ybottom += 1;
      break;
    case 45:
	Ybottom -= 1;
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
