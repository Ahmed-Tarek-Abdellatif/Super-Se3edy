/*
* Super Se3edy v1.0.0
*
* Ahmed Tarek - 2021 0 0366
* Amir Raafat - 2021 0 0333
*
*/

#include <cmath>
#include <windows.h>
#include <GL/glut.h>
using namespace std;

void display();
void land();

// void animation();
// void special_keyboard(int key, int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutFullScreen();

    // Set the callback functions
    glutDisplayFunc(display);
    // glutIdleFunc(animation);
    // glutSpecialFunc(special_keyboard);

    // Initialize OpenGL
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Background Color
    gluOrtho2D(0.0, 1000, 0.0, 1000);

    // Start the main loop
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    land();

    glFinish();
}

// TODO: Add 4f (opacity)
void land()
{
    // Organic Matter
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 150.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 150.0f, 0.0f);
    glVertex3f(0.0f, 150.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 135.0f, 0.0f);
    glVertex3f(0.0f, 135.0f, 0.0f);
    glEnd();

    // Surface Soil
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 125.0f, 0.0f);
    glVertex3f(0.0f, 125.0f, 0.0f);
    glEnd();

    // Subsoil
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
}

// void animation()
// {
//     rotate += 0.02;
//     fall -= 0.1;
//     // Go back to top
//     if ((fall * speed) < -1400)
//     {
//         fall = 0;
//         object1X = object1Random;
//         object2X = object2Random;
//         object3X = object3Random;
//     }
//     glutPostRedisplay();
// }

// void special_keyboard(int key, int x, int y)
// {
//     switch (key)
//     {
//         // Movement
//     case space: rocketY += 30; break;
//     case GLUT_KEY_DOWN: rocketY -= 30; break;
//     case GLUT_KEY_RIGHT: rocketX += 30; break;
//     case GLUT_KEY_LEFT: rocketX -= 30; break;

//         // Speed
//     case GLUT_KEY_F1: speed += 0.1; break;
//     case GLUT_KEY_F2: speed -= 0.1; break;
//     }
//     glutPostRedisplay();
// }

// </> with <3 by Ahmed & Amir