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
void welcomeScreen();
void welcomeScreenBackgroundColor();
void axe();
void axeWelcomeScreen();
void welcomeText();

void display();
void land();

void my_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutFullScreen();
    gluOrtho2D(0.0, 1920, 0.0, 1080);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Background Color

    // Functions Calling
    glutDisplayFunc(welcomeScreen);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
}

void welcomeScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    welcomeScreenBackgroundColor();
    axeWelcomeScreen();
    welcomeText();
    glFinish();
}

void welcomeScreenBackgroundColor()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.749f, 0.572f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 1080.0f, 0.0f);
    glVertex3d(1920.0f, 1080.0f, 0.0f);
    glVertex3d(1920.0f, 0.0f, 0.0f);
    glEnd();
}

void axe()
{
    // Wooden Handle
    glBegin(GL_POLYGON);
    glColor3f(0.85f, 0.5f, 0.42f);
    glVertex3d(100.0f, 100.0f, 0.0f);
    glVertex3d(100.0f, 155.0f, 0.0f);
    glVertex3d(107.0f, 155.0f, 0.0f);
    glVertex3d(107.0f, 100.0f, 0.0f);
    glEnd();

    // Metal Head
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(90.0f, 145.0f, 0.0f);
    glVertex3f(120.0f, 155.0f, 0.0f);
    glVertex3f(120.0f, 140.0f, 0.0f);
    glEnd();
}

void axeWelcomeScreen()
{
    // Left axe
    glPushMatrix();
    glTranslated(850, 480, 0);
    glTranslated(100, 150, 0);
    glRotatef(-45, 0, 0, 1);
    glScalef(4, 4, 0);
    glTranslated(-100, -150, 0);
    axe();
    glPopMatrix();

    // Right axe
    glPushMatrix();
    glTranslated(750, 480, 0);
    glTranslated(100, 150, 0);
    glRotatef(45, 0, 0, 1);
    glScalef(-1, 1, 0);
    glScalef(4, 4, 0);
    glTranslated(-100, -150, 0);
    axe();
    glPopMatrix();

}

void welcomeText()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslated(350, 500, 0);
    char gameName[] = "Super se3edy";
    for (int i = 0; i < strlen(gameName); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameName[i]);

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(850.0f, 300.0f, 0.0f);
    char screen2[] = "Press x to start";
    for (int i = 0; i < strlen(screen2); i++) 
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, screen2[i]);
    
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

void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x': glutDisplayFunc(display);
    }
    glutPostRedisplay();
}

// </> with <3 by Ahmed & Amir