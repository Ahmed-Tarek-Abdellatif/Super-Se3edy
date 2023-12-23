/*
* Super Se3edy v1.0.0
* -------------------
* Ahmed Tarek - 2021 0 0366
* Amir Raafat - 2021 0 0333
*/

#include <windows.h>
#include <string>
#include <GL/glut.h>
using namespace std;

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

enum GameState
{
    START_SCREEN,
    PLAYING,
    GAME_OVER
};

GameState gameState = START_SCREEN;
Color red = { 1.0f, 0.0f, 0.0f };
Color white = { 1.0f,1.0f,1.0f };
Color black = { 0.0f,0.0f,0.0f };
Color green = { 0.0f, 1.0f, 0.0f };
Color yellow = { 1.0f, 1.0f, 0.0f };

Color blue = { 0.529f, 0.807f, 0.921f };
Color brown = { 0.545f, 0.447f, 0.403f };

float windowWidth = 1920.0f;
float windowHeight = 1080.0f;

float moveGe3edyX = 0.0f;
float moveGe3edyY = 0.0f;

float beetleDirection = 1.0f;
float boxDirection = 1.0f;

int score = 0;
float gravity = -0.0001f;
float ge3edyVelocity = 0.0f;

float obstacleSpeed = 0.0f;
float boxSpeed = 0.0f;
float cloudSpeed = 0.0f;

bool isCollidingBeetle = false;
bool isCollidingBox = false;
bool isJumping = false;
bool isEating = false;
bool isEvading = true;

void init();

void drawRectangle(Color color, Point point, float width, float height);
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

void drawScoreBox();
void drawHealthBar();

void drawSun();
void drawCloud();
void drawCloudDesign(Point point);
void drawObstacle();
void drawBox();
void drawLand();

void handleKeyboardInput(unsigned char key, int x, int y);
void animateScene();
void moveClouds();
void moveBox();
void moveGe3edy();
void moveObstacles();

void drawHitbox(Point point, float width, float height);
void checkCollision();
void checkObstacleCollision();
void checkBoxCollision();


// --------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
}

void init()
{
    glutCreateWindow("Super Se3edy v1.0.0");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutFullScreen();
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);

    glutDisplayFunc(drawStartScreen);
    glutKeyboardFunc(handleKeyboardInput);
    glutIdleFunc(animateScene);
    glutMainLoop();
}


// --------------------------------------

void drawRectangle(Color color, Point point, float width, float height)
{
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POLYGON);
    glVertex3d(point.x, point.y, 0.0f);
    glVertex3d(point.x, point.y + height, 0.0f);
    glVertex3d(point.x + width, point.y + height, 0.0f);
    glVertex3d(point.x + width, point.y, 0.0f);
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
        glRasterPos3f(point.x, point.y, 0.0f);
        for (int i = 0; i < strlen(text); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


// --------------------------------------

void drawStartScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawAxe();
    drawCharacters();
    drawMessage({ 925.0f, 810.0f }, "Super", 1);
    drawMessage({ 915.0f, 780.0f }, "Se3edy", 1);
    drawMessage({ 915.0f, 100.0f }, "Press X", 2);
    glFinish();
}

void displayScene()
{
    glClearColor(0.529f, 0.807f, 0.921f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    animateScene();
    drawSun();
    drawScoreBox();
    drawHealthBar();
    moveObstacles();
    drawLand();
    checkCollision();
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
    drawRectangle(white, { 800.0f, 0.0f }, 320.0f, 1080.0f);
    // Yellow Circle
    drawCircle(yellow, { 960.0f, 775.0f }, 0.0f, 125.0f);

    // Ge3edy
    glPushMatrix();
    glScalef(2.5f, 2.5f, 0.0f);
    glTranslated(285.0f, -50.0f, 0.0f);
    drawGe3edy();
    glPopMatrix();

    // Score Shadow
    drawRectangle(black, { 820.0f, 930.0f }, 280, 150);
    drawRectangle(white, { 825.0f, 935.0f }, 270, 150);

    string finalScore = to_string(score);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawMessage({ 940.0f, 1050.0f }, "Final", 2);
    drawMessage({ 940.0f, 1020.0f }, "Score", 2);
    drawMessage({ 945.0f, 990.0f }, finalScore.c_str(), 2);
    drawMessage({ 880.0f, 100.0f }, "by Ahmed & Amir", 2);
    glFinish();
}


// --------------------------------------

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
    drawRectangle(white, { 99.0f, 99.0f }, 9.0f, 57.0f);
    // Wooden Handle
    drawRectangle({ 0.85f, 0.5f, 0.42f }, { 100.0f, 100.0f }, 7.0f, 55.0f);
    // Metal Head Shadow
    drawTriangle(white, 88.0f, 121.0f, 121.0f, 145.0f, 156.0f, 139.0f);
    // Metal Head
    drawTriangle(black, 90.0f, 120.0f, 120.0f, 145.0f, 155.0f, 140.0f);
    glPopMatrix();
}

void drawGe3edy()
{
    // Face
    drawCircle(brown, { 100.0f, 350.0f }, 0.0f, 30.0f);
    // Face Shadow
    drawCircle(black, { 100.0f, 350.0f }, 30.0f, 35.0f);

    // Eye
    drawCircle(white, { 118.0f, 355.0f }, 0.0f, 5.0f);
    // Pupil
    drawCircle(black, { 118.0f, 355.0f }, 0.0f, 2.0f);

    // Ear
    drawCircle(black, { 86.0f, 348.0f }, 0.0f, 9.5f);
    drawCircle(brown, { 90.0f, 348.0f }, 0.0f, 9.0f);
    drawCircle(black, { 86.0f, 346.0f }, 0.0f, 2.50f);

    // Mustache
    drawRectangle(black, { 110.0f, 334.0f }, 20.0f, 5.0f);

    // 3ema Shadow
    drawRectangle(black, { 72.0f, 370.0f }, 56.0f, 25.0f);
    // Gelbab Shadow
    drawRectangle(black, { 65.0f, 165.0f }, 70.0f, 150.0f);
    // Neck Shadow
    drawRectangle(black, { 88.0f, 295.0f }, 24.0f, 30.0f);

    // Health Bar
    if (isEating)
    {
        // Kersh
        drawCircle(white, { 115.0f, 230.0f }, 0.0f, 40.0f);
        // Kersh Shadow
        drawCircle(black, { 115.0f, 230.0f }, 35.0f, 40.0f);
    }

    // 3ema
    drawRectangle(white, { 77.0f, 370.0f }, 46.0f, 20.0f);
    // Gelbab
    drawRectangle(white, { 70.0f, 170.0f }, 60.0f, 140.0f);
    // Neck
    drawRectangle(brown, { 93.0f, 309.0f }, 14.0f, 16.0f);
    // Rounded Neck
    drawCircle(black, { 100.0f, 316.0f }, 7.0f, 10.0f);
    drawRectangle(brown, { 93.0f, 315.0f }, 14.0f, 15.0f);

    // Shoulder
    drawCircle(white, { 100.0f, 290.0f }, 0.0f, 6.0f);
    // Shoulder Shadow
    drawCircle(black, { 100.0f, 290.0f }, 6.0f, 10.0f);

    // Arm Shadow
    drawRectangle(black, { 95.0f, 205.0f }, 10.0f, 83.0f);
    // Leg Shadow
    drawRectangle(black, { 88.0f, 135.0f }, 24.0f, 35.0f);
    // Feet Shadow
    drawRectangle(black, { 88.0f, 130.0f }, 37.0f, 20.0f);

    // Arm
    drawRectangle(white, { 99.0f, 209.0f }, 2.0f, 81.0f);
    // Leg
    drawRectangle(brown, { 93.0f, 145.0f }, 14.0f, 25.0f);
    // Feet
    drawRectangle(brown, { 93.0f, 135.0f }, 27.0f, 10.0f);
}


// --------------------------------------

void drawBackground()
{
    drawRectangle(white, { 900.0f, 0.0f }, 120.0f, 1080.0f);
    // Top Triangle
    drawTriangle(black, 900.0f, 1020.0f, 960.0f, 1080.0f, 1080.0f, 1020.0f);
    // Bottom Triangle
    drawTriangle(black, 900.0f, 1020.0f, 960.0f, 0.0f, 0.0f, 60.0f);

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


// --------------------------------------

void drawScoreBox()
{
    string scoreText = "Score: " + to_string(score);
    drawMessage({ 1780.0f, 1030.0f }, scoreText.c_str(), 2);
}

void drawHealthBar()
{
    if (!isEating)
        drawRectangle(red, { 1780.0f, 990.0f }, 20.0f, 30.0f);
    else
    {
        drawRectangle(green, { 1780.0f, 990.0f }, 20.0f, 30.0f);
        drawRectangle(green, { 1810.0f, 990.0f }, 20.0f, 30.0f);
    }
}


// --------------------------------------

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
    drawCircle(white, { 300.0f, 950.0f }, 0.0f, 35.0f);
    // Right
    drawCircle(white, { 340.0f, 925.0f }, 0.0f, 30.0f);
    // Left
    drawCircle(white, { 260.0f, 920.0f }, 0.0f, 30.0f);
    // Bottom
    drawCircle(white, { 300.0f, 910.0f }, 0.0f, 35.0f);
    glPopMatrix();
}

void drawObstacle()
{
    // Body
    drawCircle(red, { 1628.0f, 135.0f }, 0.0f, 20.0f);
    drawRectangle(black, { 1600.0f, 135.0f }, 50.0f, 4.0f);
    // Head
    drawCircle(black, { 1605.0f, 140.0f }, 0.0f, 5.0f);
    drawRectangle(black, { 1603.8f, 145.0f }, 2.2f, 10.0f);
    // Antennae
    drawCircle(black, { 1602.0f, 153.0f }, 0.0f, 3.5f);
    // Shadow
    drawCircle(blue, { 1601.0f, 151.2f }, 0.0f, 2.2f);
    // Eye
    drawCircle(white, { 1605.0f, 140.0f }, 0.0f, 1.0f);
    // Body Dots
    drawCircle(black, { 1619.0f, 143.0f }, 0.0f, 2.5f);
    drawCircle(black, { 1629.0f, 143.0f }, 0.0f, 2.5f);
    drawCircle(black, { 1639.0f, 143.0f }, 0.0f, 2.5f);
}

void drawBox()
{
    // Rectangle Shadow
    drawRectangle(black, { 585.0f, 490.0f }, 100.0f, 90.0f);
    // Middle rectangle
    drawRectangle({ 0.066f, 0.168f, 0.235f }, { 590.0f, 495.0f }, 90.0f, 80.0f);
    // Water
    drawTriangle({ 0.180f, 0.639f, 0.949f }, 590.0f, 590.0f, 680.0f, 575.0f, 495.0f, 575.0f);
    // Orange
    drawCircle({ 1.0f, 0.647f, 0.0f }, { 655.0f, 520.0f }, 0.0f, 15.0f);
}

void drawLand()
{
    // Organic Soil
    drawRectangle(green, { 0.0f, 0.0f }, 1920.0f, 135.0f);
    // Surface Soil 
    drawRectangle({ 0.4f, 0.2f, 0.0f }, { 0.0f, 0.0f }, 1920.0f, 125.0f);
    // Subsoil
    drawRectangle({ 0.8f, 0.6f, 0.4f }, { 0.0f, 0.0f }, 1920.0f, 100.0f);
}


// --------------------------------------

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
        moveBox();
        moveObstacles();
        moveGe3edy();
    }
    glutPostRedisplay();
}

void moveClouds()
{
    cloudSpeed += 0.3f;
    glPushMatrix();
    glTranslated(cloudSpeed, 0.0f, 0.0f);
    drawCloud();
    glPopMatrix();
    if (cloudSpeed > windowWidth)
        cloudSpeed = -1600.0f;
}

void moveBox()
{
    boxSpeed += 0.4 * boxDirection;
    if (boxSpeed > 2000)
        boxSpeed = -1300;
    else if (boxSpeed < -1400)
        boxSpeed = 1900;

    glPushMatrix();
    glTranslated(boxSpeed, 0.0f, 0.0f);
    drawHitbox({ 585.0f, 490.0f }, 100.0f, 90.0f);
    drawBox();
    glPopMatrix();
}

void moveGe3edy()
{
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

    glPushMatrix();
    glTranslated(moveGe3edyX, moveGe3edyY, 0.0f);
    drawHitbox({ 60.0f, 135.0f }, 80.0f, 265.0f);
    drawGe3edy();
    glPopMatrix();
}

void moveObstacles()
{
    obstacleSpeed -= (0.3f * beetleDirection);
    if ((obstacleSpeed >= 700.0f) || (obstacleSpeed <= -1800.0f))
        beetleDirection *= -1;

    glPushMatrix();
    glTranslated(obstacleSpeed, 0.0f, 0.0f);
    glTranslated(1600.0f, 135.0f, 0.0f);
    glScalef(beetleDirection, 1, 1);
    glTranslated(-1600.0f, -135.0f, 0.0f);
    drawHitbox({ 1600.0f, 135.0f }, 54.0f, 21.0f);
    drawObstacle();
    glPopMatrix();
}


// --------------------------------------

void drawHitbox(Point point, float width, float height)
{
    drawRectangle(blue, { point.x, point.y }, width, height);
}

void checkCollision()
{
    checkObstacleCollision();
    checkBoxCollision();
}

void checkObstacleCollision()
{
    if ((moveGe3edyX + 60.0f >= obstacleSpeed + 1600.0f) && (moveGe3edyX <= obstacleSpeed + 1600.0f) && (moveGe3edyY <= 50.0f))
        isCollidingBeetle = true;
    else
        isCollidingBeetle = false;

    if (isCollidingBeetle)
    {
        if (isEating)
        {
            isEating = false;
            if ((beetleDirection == 1))
                obstacleSpeed = 500.0f;
            else
                obstacleSpeed = -1750;
            beetleDirection = -1;
            score -= 20;
        }
        else
        {
            score -= 20;
            glutDisplayFunc(drawEndScreen);
            gameState = GAME_OVER;
        }
    }

    //Add Score If Evaded Beetle
    if ((moveGe3edyX + 60.0f >= obstacleSpeed + 1600.0f) && (moveGe3edyX <= obstacleSpeed + 1600.0f))
    {
        if (isEvading)
        {
            score += 15;
            isEvading = false;
        }
    }
}

void checkBoxCollision()
{
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
        score += 10;
    }
}

// </> with <3 by Ahmed & Amir