/*
* Super Se3edy v1.0.0
* -------------------
* Ahmed Tarek - 2021 0 0366
* Amir Raafat - 2021 0 0333
*/

// Libraries
#include <windows.h>
#include <GL/glut.h>
using namespace std;

// Functions
void display();
void land();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Background Color
    gluOrtho2D(0.0, 1920, 0.0, 1080);
    glutFullScreen();

    // Functions Calling
    glutDisplayFunc(display);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    land();
    glFinish();
}

void land()
{
    // Organic Soil
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 135.0f, 0.0f);
    glVertex3f(0.0f, 135.0f, 0.0f);
    glEnd();

    // Surface Soil 
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 125.0f, 0.0f);
    glVertex3f(0.0f, 125.0f, 0.0f);
    glEnd();

    // Subsoil
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.6f, 0.4f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 0.0f, 0.0f);
    glVertex3f(1920.0f, 100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
}

// </> with <3 by Ahmed & Amir