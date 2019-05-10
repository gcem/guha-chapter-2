///////////////////////////////////////////////////////////////////////////////////////          
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
//
// Interaction:
// Press P/p to increase/decrease the number of longitudinal slices.
// Press Q/q to increase/decrease the number of latitudinal slices.
// Press x, X, y, Y, z, Z to turn the hemisphere.
//
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////// 

#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#define PI 3.14159265

using namespace std;

// Globals.
static float R = 5.0; // Radius of hemisphere.
static int p = 9; // Number of longitudinal slices.
static int q = 12; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.

// Initialization routine.
void setup(void) 
{
  glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// Drawing routine.
void drawScene(void)
{
  int  i, j;

  glClear (GL_COLOR_BUFFER_BIT);

  glLoadIdentity();

  // Command to push the hemisphere, which is drawn centered at the origin, 
  // into the viewing frustum.
  glTranslatef(0.0, 0.0, -10.0);

  // Commands to turn the hemisphere.
  glRotatef(Zangle, 0.0, 0.0, 1.0);
  glRotatef(Yangle, 0.0, 1.0, 0.0);
  glRotatef(Xangle, 1.0, 0.0, 0.0);
   
  // Hemisphere properties.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);

  // Array of latitudinal triangle strips, each parallel to the equator, stacked one
  // above the other from the equator to the north pole.
  for(j = 0; j < q; j++)
    {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= p; i++)
	{
	  glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		      R * sin( (float)(j+1)/q * PI/2.0 ),
		      R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );
	  glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		      R * sin( (float)j/q * PI/2.0 ),
		      R * cos( (float)j/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );         
	}
      glEnd();
    }

  // i made the following part by copying the same code three times. this code is
  // bad but i don't want to spend more time for an exercise
  
  // side at i = 0
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0, 0.0, 0.0);
  i = 0;
  for(j = 0; j < q; j++)
    {

      glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)(j+1)/q * PI/2.0 ),
		  R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );
      glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)j/q * PI/2.0 ),
		  R * cos( (float)j/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );         
    }
  glEnd();
  
  // side at i = p
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0, 0.0, 0.0);
  i = p;
    
  for(j = 0; j < q; j++)
    {

      glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)(j+1)/q * PI/2.0 ),
		  R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );
      glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)j/q * PI/2.0 ),
		  R * cos( (float)j/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );         
    }
  glEnd();

  // bottom
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0, 0.0, 0.0);
  j = 0;
    
  for(i = 0; i <= p; i++)
    {

      glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)(j+1)/q * PI/2.0 ),
		  R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );
      glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 1.0 / 6 * (float)i/p * PI ),
		  R * sin( (float)j/q * PI/2.0 ),
		  R * cos( (float)j/q * PI/2.0 ) * sin( 1.0 / 6 * (float)i/p * PI ) );         
    }
  glEnd();
  
  glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
    {
    case 27:
      exit(0);
      break;
    case 'P':
      p += 1;
      glutPostRedisplay();
      break;
    case 'p':
      if (p > 3) p -= 1;
      glutPostRedisplay();
      break;
    case 'Q':
      q += 1;
      glutPostRedisplay();
      break;
    case 'q':
      if (q > 3) q -= 1;
      glutPostRedisplay();
      break;
    case 'x':
      Xangle += 5.0;
      if (Xangle > 360.0) Xangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'X':
      Xangle -= 5.0;
      if (Xangle < 0.0) Xangle += 360.0;
      glutPostRedisplay();
      break;
    case 'y':
      Yangle += 5.0;
      if (Yangle > 360.0) Yangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'Y':
      Yangle -= 5.0;
      if (Yangle < 0.0) Yangle += 360.0;
      glutPostRedisplay();
      break;
    case 'z':
      Zangle += 5.0;
      if (Zangle > 360.0) Zangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'Z':
      Zangle -= 5.0;
      if (Zangle < 0.0) Zangle += 360.0;
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
  cout << "Press P/p to increase/decrease the number of longitudinal slices." << endl
       << "Press Q/q to increase/decrease the number of latitudinal slices." << endl
       << "Press x, X, y, Y, z, Z to turn the hemisphere." << endl;
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
  glutCreateWindow("hemisphere.cpp");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 
   
  glutMainLoop(); 
}

