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
void startScreen();
void background();
void axe();
void axeDesign(int x, int y, int angle, int scaleX, int scaleY);
void characters();
void message();

void display();
void land();
void ge3edy();
void ge3edyHitbox();
void clouds();
void beetle();
void beetleHitbox();
void changeColor();

void my_keyboard(unsigned char key, int x, int y);
void obstacleMovement();
void checkCollision();

// Variables
float moveGe3edyX = 0.0;
float moveGe3edyY = 0.0;
float beetleMovement = 0.0f;
float direction = 1.0f;
float gravity = -0.0001; // Adjust the gravity strength as needed
float ge3edyVelocityY = 0.0;
bool collision = false;
bool isJumping = false;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutFullScreen();
    gluOrtho2D(0.0, 1920, 0.0, 1080);

    // Functions Calling
    glutDisplayFunc(startScreen);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
}

void startScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    axe();
    characters();
    message();
    glFinish();
}

void background()
{
    // Rectangle
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3d(900.0f, 0.0f, 0.0f);
    glVertex3d(900.0f, 1080.0f, 0.0f);
    glVertex3d(1020.0f, 1080.0f, 0.0f);
    glVertex3d(1020.0f, 0.0f, 0.0f);
    glEnd();

    // Top Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(900.0f, 1080.0f, 0.0f);
    glVertex3f(1020.0f, 1080.0f, 0.0f);
    glVertex3f(960.0f, 1020.0f, 0.0f);
    glEnd();

    // Bottom Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(900.0f, 0.0f, 0.0f);
    glVertex3f(1020.0f, 0.0f, 0.0f);
    glVertex3f(960.0f, 60.0f, 0.0f);
    glEnd();

    // Stars
    glPushMatrix();
    {
        glPointSize(1.5);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 1; i < 100; i++)
        {
            int x = (rand() % 1920);
            int y = (rand() % 1080);
            glVertex3i(x, y, 0);
        }
        glEnd();
    }
    glPopMatrix();
}

void axe()
{
    // Left axe
    axeDesign(910, 850, -45, 1, 1);

    // Right axe
    axeDesign(810, 850, 45, -1, 1);
}

void axeDesign(int x, int y, int angle, int scaleX, int scaleY)
{
    glPushMatrix();
    glTranslated(x, y, 0);
    glTranslated(100, 150, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scaleX, scaleY, 0);
    glScalef(4, 4, 0);
    glTranslated(-100, -150, 0);

    // Wooden Handle Shadow
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3d(99.0f, 99.0f, 0.0f);
    glVertex3d(99.0f, 156.0f, 0.0f);
    glVertex3d(108.0f, 156.0f, 0.0f);
    glVertex3d(108.0f, 99.0f, 0.0f);
    glEnd();

    // Wooden Handle
    glBegin(GL_POLYGON);
    glColor3f(0.85f, 0.5f, 0.42f);
    glVertex3d(100.0f, 100.0f, 0.0f);
    glVertex3d(100.0f, 155.0f, 0.0f);
    glVertex3d(107.0f, 155.0f, 0.0f);
    glVertex3d(107.0f, 100.0f, 0.0f);
    glEnd();

    // Metal Head Shadow
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(88.0f, 145.0f, 0.0f);
    glVertex3f(121.0f, 156.0f, 0.0f);
    glVertex3f(121.0f, 139.0f, 0.0f);
    glEnd();

    // Metal Head
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(90.0f, 145.0f, 0.0f);
    glVertex3f(120.0f, 155.0f, 0.0f);
    glVertex3f(120.0f, 140.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

void characters()
{
    // Bottom Ge3edy
    glPushMatrix();
    glTranslated(860, 50, 0);
    ge3edy();
    glPopMatrix();

    // Top Ge3edy
    glPushMatrix();
    glTranslated(1060, 350, 0);
    glScalef(-1, 1, 1);
    ge3edy();
    glPopMatrix();
}

void message()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslated(925, 810, 0);
    glScalef(0.15, 0.15, 0.0);
    char super[] = "Super";
    for (int i = 0; i < strlen(super); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, super[i]);
    glPopMatrix();

    glPushMatrix();
    glTranslated(915, 780, 0);
    glScalef(0.15, 0.15, 0.0);
    char se3edy[] = "Se3edy";
    for (int i = 0; i < strlen(se3edy); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, se3edy[i]);
    glPopMatrix();

    glRasterPos3f(915.0f, 100.0f, 0.0f);
    char screen2[] = "Press x to start";
    for (int i = 0; i < strlen(screen2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, screen2[i]);
}

void display()
{
    glClearColor(0.529f, 0.807f, 0.921f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    beetle();
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

void beetle()
{
    GLUquadric* quadric = gluNewQuadric();

    // Body
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslated(1628, 150, 0);
    gluDisk(quadric, 0, 20, 100, 1);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1600.0f, 150.0f, 0.0f);
    glVertex3f(1650.0f, 150.0f, 0.0f);
    glVertex3f(1650.0f, 154.0f, 0.0f);
    glVertex3f(1600.0f, 154.0f, 0.0f);
    glEnd();

    // Head
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1605, 155, 0);
    gluDisk(quadric, 0, 5, 100, 1);
    glPopMatrix();

    // Body Dots
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1619, 158, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1629, 158, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1639, 158, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    // Legs
    glBegin(GL_POLYGON);
    glColor3f(0.529f, 0.807f, 0.921f);
    glVertex3f(1600.0f, 135.0f, 0.0f);
    glVertex3f(1650.0f, 135.0f, 0.0f);
    glVertex3f(1650.0f, 150.0f, 0.0f);
    glVertex3f(1600.0f, 150.0f, 0.0f);
    glEnd();

    // glBegin(GL_POLYGON);
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glVertex3f(1600.0f, 135.0f, 0.0f);
    // glVertex3f(1650.0f, 135.0f, 0.0f);
    // glVertex3f(1650.0f, 150.0f, 0.0f);
    // glVertex3f(1600.0f, 150.0f, 0.0f);
    // glEnd();
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

void ge3edyHitbox()
{
    glBegin(GL_POLYGON);
    glColor3f(0.529f, 0.807f, 0.921f);
    glVertex3f(60.0f, 400.0f, 0.0f);
    glVertex3f(60.0f, 135.0f, 0.0f);
    glVertex3f(140.0f, 135.0f, 0.0f);
    glVertex3f(140.0f, 400.0f, 0.0f);
    glEnd();
}

void beetleHitbox()
{
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    changeColor();
    glVertex3f(1600.0f, 175.0f, 0.0f);
    glVertex3f(1650.0f, 175.0f, 0.0f);
    glVertex3f(1650.0f, 150.0f, 0.0f);
    glVertex3f(1600.0f, 150.0f, 0.0f);
    glEnd();
}

void checkCollision()
{
    // Check Beetle Collision
    if ((moveGe3edyX + 60 >= beetleMovement + 1600) && (moveGe3edyX <= beetleMovement + 1600) && (moveGe3edyY <= 50)) 
        collision = true;
    else 
        collision = false; 
}

void changeColor()
{
    if (collision) 
        glColor3f(1.0f, 0.0f, 0.0f);
    else 
        glColor3f(0.0f, 1.0f, 0.0f);
}

// </> with <3 by Ahmed & Amir