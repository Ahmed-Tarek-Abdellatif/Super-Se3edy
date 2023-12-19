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
void sun();
void beetle();
void land();
void ge3edy();
void mainGe3edy();
void clouds();

void endScreen();

void my_keyboard(unsigned char key, int x, int y);
void obstacleMovement();

void checkCollision();
void beetleHitbox();
void ge3edyHitbox();


// Variables
float moveGe3edyX = 0.0;
float moveGe3edyY = 0.0;
float direction = 1.0f;
float gravity = -0.0001; // Adjust Gravity Strength
float ge3edyVelocityY = 0.0;
float beetleMovement = 0.0f;

bool collision = false;
bool isJumping = false;
bool isEating = false;
bool isAlive = true;


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
    glutIdleFunc(obstacleMovement);
    glutMainLoop();
}


// - Start Screen ----------------------------

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
    char screen2[] = "Press x";
    for (int i = 0; i < strlen(screen2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, screen2[i]);
}


// - Display ----------------------------

void display()
{
    glClearColor(0.529f, 0.807f, 0.921f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    sun();
    beetle();
    land();
    mainGe3edy();
    clouds();
    glFinish();
}

void sun()
{
    GLUquadric* quadric = gluNewQuadric();

    // Inner layer
    glPushMatrix();
    glTranslated(0, 1080, 0);
    glColor3f(1.0f, 0.8f, 0.2f);
    gluDisk(quadric, 0, 125, 100, 1);
    // Outer layer
    glColor3f(0.988f, 0.588f, 0.003f);
    gluDisk(quadric, 125, 130, 100, 1);
    glPopMatrix();
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

    // Health Bar
    if (isEating)
    {
        // Kersh
        glPushMatrix();
        glTranslated(115, 230, 0);
        glColor3f(1.0f, 1.0f, 1.0f);
        gluDisk(quadric, 0, 40, 100, 1);
        // Kersh Shadow
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(quadric, 35, 40, 100, 1);
        glPopMatrix();
    }

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

// Ge3edy Movement
void mainGe3edy()
{
    //Movement
    glPushMatrix();
    glTranslated(moveGe3edyX, moveGe3edyY, 0);
    ge3edyHitbox();
    ge3edy();
    glPopMatrix();

    // Gravity
    if ((moveGe3edyY > 0) || (ge3edyVelocityY > 0))
    {
        // Air/Upward Velocity : apply gravity
        moveGe3edyY += ge3edyVelocityY;
        ge3edyVelocityY += gravity;
    }
    else
        // Ground : reset the velocity
        ge3edyVelocityY = 0.0;

    // Jump One time
    if (moveGe3edyY > 0)
        isJumping = true;
    else
        isJumping = false;
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

    glEnd();
}

void beetle()
{
    GLUquadric* quadric = gluNewQuadric();

    //Beetle Movement
    glPushMatrix();
    glTranslated(beetleMovement, 0, 0);
    beetleHitbox();

    // Body
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslated(1628, 135, 0);
    gluDisk(quadric, 0, 20, 100, 1);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1600.0f, 135.0f, 0.0f);
    glVertex3f(1650.0f, 135.0f, 0.0f);
    glVertex3f(1650.0f, 139.0f, 0.0f);
    glVertex3f(1600.0f, 139.0f, 0.0f);
    glEnd();

    // Head
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1605, 140, 0);
    gluDisk(quadric, 0, 5, 100, 1);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glVertex3f(1603.8f, 145.0f, 0.0f);
    glVertex3f(1606.0f, 145.0f, 0.0f);
    glVertex3f(1606.0f, 155.0f, 0.0f);
    glVertex3f(1603.8f, 155.0f, 0.0f);
    glEnd();

    // Circle
    glPushMatrix();
    glTranslated(1602, 153, 0);
    gluDisk(quadric, 0, 3.5, 100, 1);
    glPopMatrix();

    // Shadow
    glPushMatrix();
    glColor3f(0.529f, 0.807f, 0.921f);
    glTranslated(1601, 151.2, 0);
    gluDisk(quadric, 0, 2.2, 100, 1);
    glPopMatrix();

    // Eye
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(1605, 140, 0);
    gluDisk(quadric, 0, 1, 100, 1);
    glPopMatrix();

    // Body Dots
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1619, 143, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1629, 143, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(1639, 143, 0);
    gluDisk(quadric, 0, 2.5, 100, 1);
    glPopMatrix();

    glPopMatrix();
}

// - End Screen ----------------------------

void endScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Axe Background
    glPushMatrix();
    glScalef(5, 5, 0);
    glTranslated(-765, -820, 0);
    axe();
    glPopMatrix();

    // Rectangle
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3d(800.0f, 0.0f, 0.0f);
    glVertex3d(800.0f, 1080.0f, 0.0f);
    glVertex3d(1120.0f, 1080.0f, 0.0f);
    glVertex3d(1120.0f, 0.0f, 0.0f);
    glEnd();

    // Yellow Circle
    glPushMatrix();
    GLUquadric* quadric = gluNewQuadric();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslated(960, 775, 0);
    gluDisk(quadric, 0, 125, 100, 1);
    glPopMatrix();

    // Ge3edy
    glPushMatrix();
    glScalef(2.5, 2.5, 0);
    glTranslated(285, -50, 0);
    ge3edy();
    glPopMatrix();

    // Text
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(915.0f, 100.0f, 0.0f);
    char screen2[] = "by Ahmed & Amir";
    for (int i = 0; i < strlen(screen2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, screen2[i]);
    glFinish();
}


// - Animation ----------------------------

void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':;
    case 'X': glutDisplayFunc(display);
        break;
        // Left 
    case 'a': moveGe3edyX -= 50;
        break;
        // Right
    case 'd': moveGe3edyX += 50;
        break;
    }

    //Jump Using Spacebar/w
    if (!isJumping)
    {
        if ((key == 32) || (key == 'w'))
            moveGe3edyY += 100;
        else
            isJumping = false;
    }
    glutPostRedisplay();
}

void obstacleMovement()
{
    beetleMovement -= (0.3 * direction);
    if ((beetleMovement >= 300) || (beetleMovement <= -1620))
        direction *= -1;

    checkCollision();
    glutPostRedisplay();
}


// - Collision ----------------------------

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
    glColor3f(0.529f, 0.807f, 0.921f);
    glVertex3f(1600.0f, 156.5f, 0.0f);
    glVertex3f(1654.0f, 156.5f, 0.0f);
    glVertex3f(1654.0f, 135.0f, 0.0f);
    glVertex3f(1600.0f, 135.0f, 0.0f);
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

// </> with <3 by Ahmed & Amir