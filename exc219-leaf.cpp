/////////////////////////////////////////////////////////////////////         
//
// Interaction:
// Press +/- to increase/decrease the number of vertices of the loop. 
//
// Sumanta Guha.
///////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>

#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

#define PI 3.14159265358979324

using namespace std;

// Globals.
static float R = 40.0; // Radius of sides
static float RC = 200.0; // Radius of centerline
static float X = 50.0; // X-coordinate of center of leaf
static float Y = 50.0; // Y-coordinate of center of leaf
static int numVertices = 20; // Number of vertices on half leaf

// Drawing routine.
void drawScene(void)
{
  float t; // Angle parameter.
  float x;
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  glBegin(GL_LINE_STRIP);

  t = - PI / 3;
  x = X - R / 2;
  // draw the right side
  for(i = 0; i < numVertices; ++i)
    {
      glVertex3f(x + R * cos(t), Y + R * sin(t), 0.0);
      t += PI / (numVertices * 1.5);
    }

  t = PI / 1.5;
  x = X + R / 2; 
  // draw the left side
  for(i = 0; i < numVertices; ++i)
    {
      glVertex3f(x + R * cos(t), Y + R * sin(t), 0.0);
      t += PI / (numVertices * 1.5);
    }


  // calculate the center's distance to X using Pythagoras' Theorem
  float cx = X - sqrt(RC * RC - R * sin(PI / 3) * R * sin(PI / 3));
  t = - asin(R * sin(PI / 3) / RC);
  // draw the arc at the center of the leaf
  for(i = 0; i <= numVertices; ++i)
    {
      glVertex3f(cx + RC * cos (t - 2 * t * i / numVertices), Y + RC * sin(t - 2 * t * i / numVertices), 0.0);
    }
		      
  glEnd();

  glFlush();
}

// Initialization routine.
void setup(void) 
{
  glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
    {
    case 27:
      exit(0);
      break;
    case '+':
      numVertices++;
      glutPostRedisplay();
      break;
    case '-':
      if (numVertices > 3) numVertices--;
      glutPostRedisplay();
      break;
    default:
      break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
  printInteraction();
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100); 
  glutCreateWindow("circle.cpp");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 
   
  glutMainLoop(); 
}
