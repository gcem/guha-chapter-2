// 
// Crescent moon, half-moon and three-quarter moon
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

// Global variables
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

void writeBitmapString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
} 

void drawMoon(float x, float y, float r, float rev)
{
  float angle;
  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i <= VERTICES; i++)
    {
      angle = PI / VERTICES * i - PI / 2;
      // left side (half circle)
      glVertex3f(x - cos(angle) * r, y + sin(angle) * r, 0.0);
      // right side (x coordinates scaled by cos(angle of revolution after full moon))
      glVertex3f(x + cos(angle) * r * cos(rev), y + sin(angle) * r, 0.0);
    }
  
  glEnd();

}
void drawScene(void)
{
  
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.2, 0.2, 0.2);

  drawMoon(45.0, 50.0, 25.0, PI * 3 / 4);
  drawMoon(105.0, 50.0, 25.0, PI / 2);
  drawMoon(165.0, 50.0, 25.0, PI / 4);

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos3f(26.0, 20.0, 0.0);
  writeBitmapString(GLUT_BITMAP_8_BY_13, "Crescent Moon");
  glRasterPos3f(91.0, 20.0, 0.0);
  writeBitmapString(GLUT_BITMAP_8_BY_13, "Half Moon");
  glRasterPos3f(149.0, 20.0, 0.0);
  writeBitmapString(GLUT_BITMAP_8_BY_13, "Three-quarter Moon");
  
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
  glOrtho(0.0, 200.0, 1.0, 100.0, -1.0, 1.0);
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
  glutInitWindowSize(1000, 500);
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
