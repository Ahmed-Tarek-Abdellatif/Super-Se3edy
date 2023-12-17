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
void message();

void display();
void land();
void ge3edy();
void clouds();

void my_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutFullScreen();
    gluOrtho2D(0.0, 1920, 0.0, 1080);

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
    message();
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

void message()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslated(350, 500, 0);
    char gameName[] = "Super se3edy";
    for (int i = 0; i < strlen(gameName); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameName[i]);
    glPopMatrix();

    glRasterPos3f(850.0f, 300.0f, 0.0f);
    char screen2[] = "Press x to start";
    for (int i = 0; i < strlen(screen2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, screen2[i]);
}

void display()
{
    glClearColor(0.529f, 0.807f, 0.921f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    land();
    ge3edy();
    clouds();
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

void ge3edy()
{
    GLUquadric* quadric = gluNewQuadric();

    // Face
    glPushMatrix();
    glTranslated(100, 350, 0);
    glColor3f(0.545f, 0.447f, 0.403f);
    gluDisk(quadric, 0, 30, 100, 1);
    // Face Shadow
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 30, 35, 100, 1);
    glPopMatrix();

    // Eyes
    glPushMatrix();
    glTranslated(118, 355, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluDisk(quadric, 0, 5, 100, 1);
    // Pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0, 2, 100, 1);
    glPopMatrix();

    // Ears
    glPushMatrix();
    glTranslated(86, 348, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0, 9.5, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(90, 348, 0);
    glColor3f(0.545f, 0.447f, 0.403f);
    gluDisk(quadric, 0, 9, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(86, 346, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0, 2, 100, 1);
    glPopMatrix();

    // Mustache
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(130.0f, 340.0f, 0.0f);
    glVertex3f(130.0f, 335.0f, 0.0f);
    glVertex3f(110.0f, 335.0f, 0.0f);
    glVertex3f(110.0f, 340.0f, 0.0f);
    glEnd();

    // Neck Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(88.0f, 325.0f, 0.0f);
    glVertex3f(88.0f, 295.0f, 0.0f);
    glVertex3f(112.0f, 295.0f, 0.0f);
    glVertex3f(112.0f, 325.0f, 0.0f);
    glEnd();

    // Gelbab Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(65.0f, 315.0f, 0.0f);
    glVertex3f(65.0f, 165.0f, 0.0f);
    glVertex3f(135.0f, 165.0f, 0.0f);
    glVertex3f(135.0f, 315.0f, 0.0f);
    glEnd();

    // 3ema Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(128.0f, 370.0f, 0.0f);
    glVertex3f(128.0f, 395.0f, 0.0f);
    glVertex3f(72.0f, 395.0f, 0.0f);
    glVertex3f(72.0f, 370.0f, 0.0f);
    glEnd();

    // 3ema
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(123.0f, 370.0f, 0.0f);
    glVertex3f(123.0f, 390.0f, 0.0f);
    glVertex3f(77.0f, 390.0f, 0.0f);
    glVertex3f(77.0f, 370.0f, 0.0f);
    glEnd();

    // Gelbab
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(70.0f, 310.0f, 0.0f);
    glVertex3f(70.0f, 170.0f, 0.0f);
    glVertex3f(130.0f, 170.0f, 0.0f);
    glVertex3f(130.0f, 310.0f, 0.0f);
    glEnd();

    // Neck
    glBegin(GL_POLYGON);
    glColor3f(0.545f, 0.447f, 0.403f);
    glVertex3f(93.0f, 325.0f, 0.0f);
    glVertex3f(93.0f, 310.0f, 0.0f);
    glVertex3f(107.0f, 310.0f, 0.0f);
    glVertex3f(107.0f, 325.0f, 0.0f);
    glEnd();

    // Rounded Neck
    glPushMatrix();
    glTranslated(100, 316, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 6, 10, 100, 1);
    glPopMatrix();

    // Neck #2
    glBegin(GL_POLYGON);
    glColor3f(0.545f, 0.447f, 0.403f);
    glVertex3f(93.0f, 330.0f, 0.0f);
    glVertex3f(93.0f, 315.0f, 0.0f);
    glVertex3f(107.0f, 315.0f, 0.0f);
    glVertex3f(107.0f, 330.0f, 0.0f);
    glEnd();

    // Shoulder
    glPushMatrix();
    glTranslated(100, 290, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluDisk(quadric, 0, 6, 100, 1);
    // Shoulder Shadow
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 6, 10, 100, 1);
    glPopMatrix();

    // Arm Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(95.0f, 288.0f, 0.0f);
    glVertex3f(95.0f, 205.0f, 0.0f);
    glVertex3f(105.0f, 205.0f, 0.0f);
    glVertex3f(105.0f, 288.0f, 0.0f);
    glEnd();

    // Arm
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(99.0f, 290.0f, 0.0f);
    glVertex3f(99.0f, 209.0f, 0.0f);
    glVertex3f(101.0f, 209.0f, 0.0f);
    glVertex3f(101.0f, 290.0f, 0.0f);
    glEnd();

    // Feet Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(93.0f, 150.0f, 0.0f);
    glVertex3f(93.0f, 135.0f, 0.0f);
    glVertex3f(125.0f, 135.0f, 0.0f);
    glVertex3f(125.0f, 150.0f, 0.0f);
    glEnd();

    // Leg Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(88.0f, 170.0f, 0.0f);
    glVertex3f(88.0f, 135.0f, 0.0f);
    glVertex3f(112.0f, 135.0f, 0.0f);
    glVertex3f(112.0f, 170.0f, 0.0f);
    glEnd();

    // Leg
    glBegin(GL_POLYGON);
    glColor3f(0.545f, 0.447f, 0.403f);
    glVertex3f(93.0f, 170.0f, 0.0f);
    glVertex3f(93.0f, 145.0f, 0.0f);
    glVertex3f(107.0f, 145.0f, 0.0f);
    glVertex3f(107.0f, 170.0f, 0.0f);
    glEnd();

    // Feet
    glBegin(GL_POLYGON);
    glColor3f(0.545f, 0.447f, 0.403f);
    glVertex3f(93.0f, 145.0f, 0.0f);
    glVertex3f(93.0f, 135.0f, 0.0f);
    glVertex3f(120.0f, 135.0f, 0.0f);
    glVertex3f(120.0f, 145.0f, 0.0f);
    glEnd();
}

void clouds()
{
    GLUquadric* quadric = gluNewQuadric();

    glPushMatrix();
    glTranslated(300, 950, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluDisk(quadric, 0, 30, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(340, 930, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluDisk(quadric, 0, 30, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(260, 925, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluDisk(quadric, 0, 30, 100, 1);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(88.0f, 170.0f, 0.0f);
    glVertex3f(88.0f, 135.0f, 0.0f);
    glVertex3f(112.0f, 135.0f, 0.0f);
    glVertex3f(112.0f, 170.0f, 0.0f);
    glEnd();
}

void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x': glutDisplayFunc(display);
    case 'X': glutDisplayFunc(display);
    case ' ':; break;
    }
    glutPostRedisplay();
}

// </> with <3 by Ahmed & Amir