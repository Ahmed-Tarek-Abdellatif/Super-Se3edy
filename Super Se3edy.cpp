/*
* Super Se3edy v1.0.0
* -------------------
* Ahmed Tarek - 2021 0 0366
* Amir Raafat - 2021 0 0333
*/


#include <windows.h>
#include <GL/glut.h>
using namespace std;

enum GameState
{
    START_SCREEN,
    PLAYING,
    GAME_OVER
};

struct Color
{
    float red;
    float green;
    float blue;
};

struct Point
{
    float x;
    float y;
};

struct Dimensions
{
    float length;
    float width;
};

GameState gameState = START_SCREEN;

float windowWidth = 1920.0f;
float windowHeight = 1080.0f;

float moveGe3edyX = 0.0f;
float moveGe3edyY = 0.0f;
float direction = 1.0f;
float boxDirection = 1.0f;

float gravity = -0.0001f;
float ge3edyVelocity = 0.0f;

float obstacleSpeed = 0.0f;
float boxSpeed = 0.0f;
float cloudSpeed = 0.0f;

bool isCollidingbeetle = false;
bool isCollidingBox = false;
bool isJumping = false;
bool isEating = false;
bool isEvading = true;

void drawRectangle(Color color, Point point, Dimensions dimensions);
void drawTriangle(Color color, float firstX, float secondX, float thirdX, float firstY, float secondY, float thirdY);
void drawCircle(Color color, Point translate, float innerRadius, float outerRadius);
void drawMessage(Point point, const char* text, int font);

void drawStartScreen();
void displayScene();
void drawEndScreen();

void drawAxe();
void drawAxeDesign(Point point, float angle, Point scale);
void drawGe3edy();

void drawBackground();
void drawCharacters();

void drawSun();
void drawCloud();
void drawCloudDesign(Point point);
void drawObstacle();
void drawFoodAndWater();
void drawLand();

void handleKeyboardInput(unsigned char key, int x, int y);
void animateScene();
void moveClouds();
void moveObstacles();
void moveBox();
void moveGe3edy();

void drawHitbox(Point point, Dimensions dimensions);
void checkCollision();


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutFullScreen();
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);

    glutDisplayFunc(drawStartScreen);
    glutKeyboardFunc(handleKeyboardInput);
    glutIdleFunc(animateScene);
    glutMainLoop();
}


// - Primitives ----------------------------

void drawRectangle(Color color, Point point, Dimensions dimensions)
{
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POLYGON);
    glVertex3d(point.x, point.y, 0.0f);
    glVertex3d(point.x, point.y + dimensions.width, 0.0f);
    glVertex3d(point.x + dimensions.length, point.y + dimensions.width, 0.0f);
    glVertex3d(point.x + dimensions.length, point.y, 0.0f);
    glEnd();
}

void drawTriangle(Color color, float firstX, float secondX, float thirdX, float firstY, float secondY, float thirdY)
{
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(firstX, firstY, 0.0f);
    glVertex3f(secondX, secondY, 0.0f);
    glVertex3f(thirdX, thirdY, 0.0f);
    glEnd();
}

void drawCircle(Color color, Point point, float innerRadius, float outerRadius)
{
    GLUquadric* quadric = gluNewQuadric();

    glPushMatrix();
    glColor3f(color.red, color.green, color.blue);
    glTranslated(point.x, point.y, 0.0f);
    gluDisk(quadric, innerRadius, outerRadius, 100.0f, 1.0f);
    glPopMatrix();
}

void drawMessage(Point point, const char* text, int font)
{
    glColor3f(0.0f, 0.0f, 0.0f);

    if (font == 1)
    {
        glPushMatrix();
        glTranslated(point.x, point.y, 0.0f);
        glScalef(0.15f, 0.15f, 0.0f);
        for (int i = 0; i < strlen(text); i++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
        glPopMatrix();
    }

    else if (font == 2)
    {
        glRasterPos3f(915.0f, 100.0f, 0.0f);
        for (int i = 0; i < strlen(text); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


// - 1 ----------------------------

void drawStartScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawAxe();
    drawCharacters();
    drawMessage({ 925.0f, 810.0f }, "Super", 1);
    drawMessage({ 915.0f, 780.0f }, "Se3edy", 1);
    drawMessage({ 915.0f, 780.0f }, "Press X", 2);
    glFinish();
}

void displayScene()
{
    glClearColor(0.529f, 0.807f, 0.921f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawSun();
    moveClouds();
    moveGe3edy();
    moveObstacles();
    drawLand();
    moveBox();
    glFinish();
}

void drawEndScreen()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Axe Background
    glPushMatrix();
    glScalef(5.0f, 5.0f, 0.0f);
    glTranslated(-765.0f, -820.0f, 0.0f);
    drawAxe();
    glPopMatrix();

    // Background
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 800.0f, 0.0f }, { 320.0f, 1080.0f });

    // Yellow Circle
    drawCircle({ 1.0f, 1.0f, 0.0f }, { 960.0f, 775.0f }, 0.0f, 125.0f);

    // Ge3edy
    glPushMatrix();
    glScalef(2.5f, 2.5f, 0.0f);
    glTranslated(285.0f, -50.0f, 0.0f);
    drawGe3edy();
    glPopMatrix();

    // Text
    drawMessage({ 915.0f, 780.0f }, "by Ahmed & Amir", 2);
    glFinish();
}


// - 2 ----------------------------

void drawAxe()
{
    // Left axe
    drawAxeDesign({ 910.0f, 850.0f }, -45.0f, { 1.0f, 1.0f });
    // Right axe
    drawAxeDesign({ 810.0f, 850.0f }, 45.0f, { -1.0f, 1.0f });
}

void drawAxeDesign(Point point, float angle, Point scale)
{
    glPushMatrix();
    glTranslated(point.x, point.y, 0.0f);
    glTranslated(100.0f, 150.0f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(scale.x, scale.y, 0.0f);
    glScalef(4.0f, 4.0f, 0.0f);
    glTranslated(-100.0f, -150.0f, 0.0f);

    // Wooden Handle Shadow
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 99.0f, 99.0f }, { 9.0f, 57.0f });
    // Wooden Handle
    drawRectangle({ 0.85f, 0.5f, 0.42f }, { 100.0f, 100.0f }, { 7.0f, 55.0f });
    // Metal Head Shadow
    drawTriangle({ 1.0f, 1.0f, 1.0f }, 88.0f, 121.0f, 121.0f, 145.0f, 156.0f, 139.0f);
    // Metal Head
    drawTriangle({ 0.0f, 0.0f, 0.0f }, 90.0f, 120.0f, 120.0f, 145.0f, 155.0f, 140.0f);
    glPopMatrix();
}

void drawGe3edy()
{
    // Face
    drawCircle({ 0.545f, 0.447f, 0.403f }, { 100.0f, 350.0f }, 0.0f, 30.0f);
    // Face Shadow
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 100.0f, 350.0f }, 30.0f, 35.0f);

    // Eye
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 118.0f, 355.0f }, 0.0f, 5.0f);
    // Pupil
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 118.0f, 355.0f }, 0.0f, 2.0f);

    // Ear
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 86.0f, 348.0f }, 0.0f, 9.5f);
    drawCircle({ 0.545f, 0.447f, 0.403f }, { 90.0f, 348.0f }, 0.0f, 9.0f);
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 86.0f, 346.0f }, 0.0f, 2.50f);

    // Mustache
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 110.0f, 334.0f }, { 20.0f, 5.0f });

    // Health Bar
    if (isEating)
    {
        // Kersh
        drawCircle({ 1.0f, 1.0f, 1.0f }, { 115.0f, 230.0f }, 0.0f, 40.0f);
        // Kersh Shadow
        drawCircle({ 0.0f, 0.0f, 0.0f }, { 115.0f, 230.0f }, 35.0f, 40.0f);
    }

    // 3ema Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 72.0f, 370.0f }, { 56.0f, 25.0f });
    // Gelbab Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 65.0f, 165.0f }, { 70.0f, 150.0f });
    // Neck Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 88.0f, 295.0f }, { 24.0f, 30.0f });

    // 3ema
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 77.0f, 370.0f }, { 46.0f, 20.0f });
    // Gelbab
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 70.0f, 170.0f }, { 60.0f, 140.0f });
    // Neck
    drawRectangle({ 0.545f, 0.447f, 0.403f }, { 93.0f, 309.0f }, { 14.0f, 16.0f });
    // Rounded Neck
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 100.0f, 316.0f }, 7.0f, 10.0f);
    drawRectangle({ 0.545f, 0.447f, 0.403f }, { 93.0f, 315.0f }, { 14.0f, 15.0f });

    // Shoulder
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 100.0f, 290.0f }, 0.0f, 6.0f);
    // Shoulder Shadow
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 100.0f, 290.0f }, 6.0f, 10.0f);

    // Arm Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 95.0f, 205.0f }, { 10.0f, 83.0f });
    // Leg Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 88.0f, 135.0f }, { 24.0f, 35.0f });
    // Feet Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 88.0f, 130.0f }, { 37.0f, 20.0f });

    // Arm
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 99.0f, 209.0f }, { 2.0f, 81.0f });
    // Leg
    drawRectangle({ 0.545f, 0.447f, 0.403f }, { 93.0f, 145.0f }, { 14.0f, 25.0f });
    // Feet
    drawRectangle({ 0.545f, 0.447f, 0.403f }, { 93.0f, 135.0f }, { 27.0f, 10.0f });
}


// - 3 ----------------------------

void drawBackground()
{
    drawRectangle({ 1.0f, 1.0f, 1.0f }, { 900.0f, 0.0f }, { 120.0f, 1080.0f });
    // Top Triangle
    drawTriangle({ 0.0f, 0.0f, 0.0f }, 900.0f, 1020.0f, 960.0f, 1080.0f, 1080.0f, 1020.0f);
    // Bottom Triangle
    drawTriangle({ 0.0f, 0.0f, 0.0f }, 900.0f, 1020.0f, 960.0f, 0.0f, 0.0f, 60.0f);

    // Dots
    glPushMatrix();
    {
        glPointSize(2);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        for (int i = 1; i < 100; i++)
        {
            int x = (rand() % 1920);
            int y = (rand() % 1080);
            glVertex3i(x, y, 0.0f);
        }
        glEnd();
    }
    glPopMatrix();
}

void drawCharacters()
{
    // Top Ge3edy
    glPushMatrix();
    glTranslated(1060.0f, 350.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    drawGe3edy();
    glPopMatrix();

    // Bottom Ge3edy
    glPushMatrix();
    glTranslated(860.0f, 50.0f, 0.0f);
    drawGe3edy();
    glPopMatrix();
}


// - 4 ----------------------------

void drawSun()
{
    // Inner layer
    drawCircle({ 1.0f, 0.8f, 0.2f }, { 0.0f, 1080.0f }, 0.0f, 125.0f);
    // Outer layer
    drawCircle({ 0.988f, 0.588f, 0.003f }, { 0.0f, 1080.0f }, 125.0f, 130.0f);
}

void drawCloud()
{
    drawCloudDesign({ 100.0f, -75.0f });
    drawCloudDesign({ 650.0f, -175.0f });
    drawCloudDesign({ 1250.0f, -125.0f });
}

void drawCloudDesign(Point point)
{
    glPushMatrix();
    glTranslated(point.x, point.y, 0.0f);

    // Top
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 300.0f, 950.0f }, 0.0f, 35.0f);
    // Right
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 340.0f, 925.0f }, 0.0f, 30.0f);
    // Left
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 260.0f, 920.0f }, 0.0f, 30.0f);
    // Bottom
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 300.0f, 910.0f }, 0.0f, 35.0f);
    glPopMatrix();
}

void drawObstacle()
{
    // Body
    drawCircle({ 1.0f, 0.0f, 0.0f }, { 1628.0f, 135.0f }, 0.0f, 20.0f);
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 1600.0f, 135.0f }, { 50.0f, 4.0f });

    // Head
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 1605.0f, 140.0f }, 0.0f, 5.0f);
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 1603.8f, 145.0f }, { 2.2f, 10.0f });

    // Antennae
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 1602.0f, 153.0f }, 0.0f, 3.5f);
    // Shadow
    drawCircle({ 0.529f, 0.807f, 0.921f }, { 1601.0f, 151.2f }, 0.0f, 2.2f);

    // Eye
    drawCircle({ 1.0f, 1.0f, 1.0f }, { 1605.0f, 140.0f }, 0.0f, 1.0f);

    // Body Dots
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 1619.0f, 143.0f }, 0.0f, 2.5f);
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 1629.0f, 143.0f }, 0.0f, 2.5f);
    drawCircle({ 0.0f, 0.0f, 0.0f }, { 1639.0f, 143.0f }, 0.0f, 2.5f);
}

void drawFoodAndWater()
{
    // Rectangle Shadow
    drawRectangle({ 0.0f, 0.0f, 0.0f }, { 585.0f, 490.0f }, { 100.0f, 90.0f });
    // Middle rectangle
    drawRectangle({ 0.066f, 0.168f, 0.235f }, { 590.0f, 495.0f }, { 90.0f, 80.0f });
    // Water
    drawTriangle({ 0.180f, 0.639f, 0.949f }, 590.0f, 590.0f, 680.0f, 575.0f, 495.0f, 575.0f);
    // Orange
    drawCircle({ 1.0f, 0.647f, 0.0f }, { 655.0f, 520.0f }, 0.0f, 15.0f);
}

void drawLand()
{
    // Organic Soil
    drawRectangle({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { 1920.0f, 135.0f });
    // Surface Soil 
    drawRectangle({ 0.4f, 0.2f, 0.0f }, { 0.0f, 0.0f }, { 1920.0f, 125.0f });
    // Subsoil
    drawRectangle({ 0.8f, 0.6f, 0.4f }, { 0.0f, 0.0f }, { 1920.0f, 100.0f });
}


// - 5 ----------------------------

void handleKeyboardInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':;
    case 'X':
        if (gameState == START_SCREEN)
        {
            gameState = PLAYING;
            glutDisplayFunc(displayScene);
        }
        break;
        // Left
    case 'a': if (moveGe3edyX > 0.0f)
        moveGe3edyX -= 50.0f;
        break;
        // Right
    case 'd': if (moveGe3edyX < 1700.0f)
        moveGe3edyX += 50.0f;
        break;
    }

    //Jump Using Spacebar/w
    if (!isJumping)
    {
        if ((key == 32) || (key == 'w'))
            moveGe3edyY += 100.0f;
        else
            isJumping = false;
    }
    glutPostRedisplay();
}

void animateScene()
{
    if (gameState == PLAYING)
    {
        moveClouds();
        moveObstacles();
        moveGe3edy();
    }
    glutPostRedisplay();
}

void moveClouds()
{
    cloudSpeed += 0.1f;
    glPushMatrix();
    glTranslated(cloudSpeed, 0.0f, 0.0f);
    drawCloud();
    glPopMatrix();
}

void moveObstacles()
{
    obstacleSpeed -= (0.3f * direction);
    if ((obstacleSpeed >= 300.0f) || (obstacleSpeed <= -1620.0f))
        direction *= -1;

    glPushMatrix();
    glTranslated(obstacleSpeed, 0.0f, 0.0f);
    drawHitbox({ 1600.0f, 135.0f }, { 54.0f, 21.0f });
    drawObstacle();
    glPopMatrix();
}

void moveBox()
{
    boxSpeed += 0.4 * boxDirection;
    if (boxSpeed > 2000)
        boxSpeed = -1300;

    glPushMatrix();
    glTranslated(boxSpeed, 0.0f, 0.0f);
    drawHitbox({ 585.0f, 490.0f }, { 100.0f, 90.0f });
    drawFoodAndWater();
    glPopMatrix();

    checkCollision();
}

void moveGe3edy()
{
    glPushMatrix();
    glTranslated(moveGe3edyX, moveGe3edyY, 0.0f);
    drawHitbox({ 60.0f, 135.0f }, { 80.0f, 265.0f });
    drawGe3edy();
    glPopMatrix();

    // Gravity
    if ((moveGe3edyY > 0.0f) || (ge3edyVelocity > 0.0f))
    {
        // Air/Upward Velocity : apply gravity
        moveGe3edyY += ge3edyVelocity;
        ge3edyVelocity += gravity;
    }
    else
        // Ground : reset the velocity
        ge3edyVelocity = 0.0f;

    // Jump Once
    if (moveGe3edyY > 0.0f)
        isJumping = true;
    else
    {
        isJumping = false;
        isEvading = true;
    }
}

// - 6 ----------------------------

void drawHitbox(Point point, Dimensions dimensions)
{
    drawRectangle({ 0.529f, 0.807f, 0.921f }, { point.x, point.y }, { dimensions.length, dimensions.width });
}

void checkCollision()
{
    // Check Obstacle Collision
    if ((moveGe3edyX + 60.0f >= obstacleSpeed + 1600.0f) && (moveGe3edyX <= obstacleSpeed + 1600.0f) && (moveGe3edyY <= 50.0f))
        isCollidingbeetle = true;
    else
        isCollidingbeetle = false;

    if (isCollidingbeetle)
    {
        if (isEating)
        {
            isEating = false;

            if ((direction == 1))
                obstacleSpeed = 500.0f;
            else
                obstacleSpeed = -1750;

            direction = -1;
        }
        else
        {
            glutDisplayFunc(drawEndScreen);
            gameState = GAME_OVER;
        }
    }

    // Box Collision
    if ((moveGe3edyX + 100.0f >= boxSpeed + 585.0f) && (moveGe3edyX <= boxSpeed + 585.0f) && (moveGe3edyY >= 90.0f))
        isCollidingBox = true;
    else
        isCollidingBox = false;

    if (isCollidingBox)
    {
        if (isEating == false)
            isEating = true;

        if (boxDirection == 1)
        {
            boxSpeed = 2000;
            boxDirection = -1;
        }
        else
        {
            boxSpeed = 1300.0;
            boxDirection = 1;
        }

    }
}

// </> with <3 by Ahmed & Amir