#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

//Game Speed
int FirstSpeed = 50;
//Game Track
int start = 0;
int gv = 0;
int level = 0;

//Track Score
int score = 0;

//For move track
float roadDivTop = 0;
float roadDivMdl = 0;
float roadDivBtm = 0;
float roadDivTree = 0;

//For Card Left / RIGHT
int lrIndex = 0;

//Car Coming
int Car1 = 0;
int lrIndex1 = 0;
int Car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void tree(int x, int y, float scale = 1.0)
{
    int newx = x;
    int newy = y;

    // Bottom
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11 * scale, newy + 55 * scale);
    glVertex2f(newx + 12 * scale, newy + 55 - 10 * scale);
    glVertex2f(newx + 10 * scale, newy + 55 - 10 * scale);
    glEnd();

    // Top
    glColor3f(0.365, 0.933, 0.565);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11 * scale, newy + 55 + 3 * scale);
    glVertex2f(newx + 12 * scale + 3 * scale, newy + 55 - 3 * scale);
    glColor3f(0.900, 0.900, 0.900);
    glVertex2f(newx + 10 * scale - 3 * scale, newy + 55 - 3 * scale);
    glEnd();
}



void startGame()
{
    tree(80, roadDivTree + 0, 1);
    tree(82, roadDivTree + -15, 1);
    tree(80, roadDivTree + 15, 1);
    tree(2, roadDivTree + 0, 1);
    tree(2, roadDivTree + 15, 1);
    tree(0, roadDivTree + 30, 1);
    roadDivTree = roadDivTree - 0.5;
    if (roadDivTree < -60)
    {
        roadDivTree = 60;
        score++;
    }

    //Road
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(22, 100);
    glVertex2f(22, 0);
    glEnd();

    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(78, 0);
    glVertex2f(78, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    //TOP
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();
    roadDivTop = roadDivTop - 0.5;
    if (roadDivTop < -100)
    {
        roadDivTop = 20;
        score++;
    }
    //Middle
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();
    roadDivMdl = roadDivMdl - 0.5;
    if (roadDivMdl < -60)
    {
        roadDivMdl = 60;
        score++;
    }
    //Bottom
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();
    roadDivBtm = roadDivBtm - 0.5;
    if (roadDivBtm < -20)
    {
        roadDivBtm = 100;
        score++;
    }

    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(80, 97);
    glVertex2f(100, 97);
    glVertex2f(100, 98 - 8);
    glVertex2f(80, 98 - 8);
    glEnd();

    //Print Score
    char buffer[50];
    sprintf_s(buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95, (void*)font3, buffer);
    //Speed Print
    char buffer1[50];
    sprintf_s(buffer1, "SPEED:%dKm/h", FirstSpeed);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 2, (void*)font3, buffer1);
    //level Print
    if (score % 50 == 0)
    {
        int last = score / 50;
        if (last != level)
        {
            level = score / 50;
            FirstSpeed = FirstSpeed + 2;
        }
    }
    char level_buffer[50];
    sprintf_s(level_buffer, "LEVEL: %d", level + 1);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 4, (void*)font3, level_buffer);

    //Increase Speed With level

    //MAIN car
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 5);
    glVertex2f(lrIndex + 26 - 2, 7);
    glVertex2f(lrIndex + 30 + 2, 7);
    glVertex2f(lrIndex + 30 + 2, 5);
    glEnd();
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 1);
    glVertex2f(lrIndex + 26 - 2, 3);
    glVertex2f(lrIndex + 30 + 2, 3);
    glVertex2f(lrIndex + 30 + 2, 1);
    glEnd();
    //Car Body
    glColor3f(0.900, 0.900, 0.900);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 1);
    glVertex2f(lrIndex + 26, 8);
    glColor3f(0.900, 0.000, 0.000);

    glVertex2f(lrIndex + 28, 10);
    glVertex2f(lrIndex + 30, 8);
    glVertex2f(lrIndex + 30, 1);
    glEnd();


    //Opposite car 1
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, Car1 + 100 - 4);
    glVertex2f(lrIndex1 + 26 - 2, Car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, Car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, Car1 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, Car1 + 100);
    glVertex2f(lrIndex1 + 26 - 2, Car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, Car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, Car1 + 100);
    glEnd();
    glColor3f(0.678, 0.847, 0.902);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, Car1 + 100);
    glVertex2f(lrIndex1 + 26, Car1 + 100 - 7);
    glColor3f(0.933, 0.678, 0.933);
    //glVertex2f(lrIndex1 + 28, Car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, Car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, Car1 + 100);
    glEnd();
    Car1--;
    if (Car1 < -100)
    {
        Car1 = 0;
        lrIndex1 = lrIndex;
    }
    //Kill check Car1
    if ((abs(lrIndex - lrIndex1) < 8) && (Car1 + 100 < 10))
    {
        PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
        start = 0;
        gv = 1;
    }



    //Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, Car2 + 100 - 4);
    glVertex2f(lrIndex2 + 26 - 2, Car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, Car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, Car2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, Car2 + 100);
    glVertex2f(lrIndex2 + 26 - 2, Car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, Car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, Car2 + 100);
    glEnd();
    glColor3f(1.000, 0.000, 0.500);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26, Car2 + 100);
    glVertex2f(lrIndex2 + 26, Car2 + 100 - 7);
    glColor3f(0.933, 0.678, 0.933);
    //glVertex2f(lrIndex2 + 28, Car2 + 100 - 9);
    glVertex2f(lrIndex2 + 30, Car2 + 100 - 7);
    glVertex2f(lrIndex2 + 30, Car2 + 100);
    glEnd();
    Car2--;
    if (Car2 < -100)
    {
        Car2 = 0;
        lrIndex2 = lrIndex;
    }
    //Kill check Car2
    if ((abs(lrIndex - lrIndex2) < 8) && (Car2 + 100 < 10))
    {
        PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
        start = 0;
        gv = 1;
    }

    //Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
    glEnd();
    glColor3f(0.000, 0.271, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    //glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    car3--;
    if (car3 < -100)
    {
        car3 = 0;
        lrIndex3 = lrIndex;
    }
    //Kill check car3
    if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10))
    {
        PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
        start = 0;
        gv = 1;
    }
}

void fristDesign()
{

    //Road BackGround
    glColor3f(0.000, 0.350, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glColor3f(0.6, 0.8, 0.3);
    glVertex2f(100, 50 - 50);
    glVertex2f(0, 50 - 50);
    glEnd();

    //Road Design In Front Page
    glColor3f(0, 0.3, 0.3);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(32 + 58, 50 - 50);
    glVertex2f(32 - 22, 50 - 50);
    glEnd();
    //Road Middle
    glColor3f(0.8, 0.8, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(50 + 2, 50 - 50);
    glVertex2f(50 - 2, 50 - 50);
    glEnd();

    //Road Sky
    glColor3f(0.000, 0.60, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(0, 100);
    glColor3f(0.933, 0.933, 0.933);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glEnd();

    //Hill 1
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 55 + 10);
    glVertex2f(20 + 7, 55);
    glVertex2f(0, 55);
    glEnd();

    //Hill 2
    glColor3f(0.000, 0.400, 0.000);
    glBegin(GL_TRIANGLES);
    glVertex2f(20 + 15, 55 + 12);
    glVertex2f(20 + 20 + 10, 55);
    glVertex2f(0 + 10, 55);
    glEnd();

    //Hill 4
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(87, 55 + 10);
    glVertex2f(100, 55);
    glVertex2f(60, 55);
    glEnd();

    //Hill 3
    glColor3f(0.000, 0.400, 0.000);
    glBegin(GL_TRIANGLES);
    glVertex2f(70, 70);
    glVertex2f(90, 55);
    glVertex2f(50, 55);
    glEnd();

    //Tree on front page
    tree(5, -15, 1);
    tree(0, 0, 1);
    tree(9, 5, 1);
    tree(80, 0, 1);
    tree(75, -15, 1);
    tree(72, 5, 1);

    //Menu Place Holder
    glColor3f(0.098, 0.098, 0.439);
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();

    glColor3f(00, 0, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 4 + 10);
    glVertex2f(32 - 4, 50 + 4 + 10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(32 + 45, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 + 45, 50 - 15 + 10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 - 14 + 10);
    glVertex2f(32 + 46, 50 - 14 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 - 5, 50 + 5 + 10);
    glVertex2f(32 - 5, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();

    //Text Information in First Page
    if (gv == 1)
    {
        glColor3f(1.000, 0.000, 1.000);
        renderBitmapString(35, 60 + 15, (void*)font1, "GAME OVER");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2[50];
        sprintf_s(buffer2, "Your Score is : %d", score);
        renderBitmapString(33, 60 - 4 + 15, (void*)font1, buffer2);
    }

    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to Start");
    renderBitmapString(30, 50 - 3 + 10, (void*)font2, "Press ESC      to Exit");

    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(30, 50 - 6 + 10, (void*)font3, "Press UP    to Increase Speed");
    renderBitmapString(30, 50 - 8 + 10, (void*)font3, "Press DWON  to Decrease Speed");
    renderBitmapString(30, 50 - 10 + 10, (void*)font3, "Press RIGHT to Turn Right");
    renderBitmapString(30, 50 - 12 + 10, (void*)font3, "Press LEFT  to Turn Left");
    ;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (start == 1)
    {
        glClearColor(0.000, 0.392, 0.000, 1);
        startGame();
    }

    else
    {
        fristDesign();
    }

    glFlush();
    glutSwapBuffers();
}

void spe_key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        if (FirstSpeed > (50 + (level * 2)))
            FirstSpeed = FirstSpeed - 2;
        break;
    case GLUT_KEY_UP:
        FirstSpeed = FirstSpeed + 2;
        break;

    case GLUT_KEY_LEFT:
        if (lrIndex >= 0)
        {
            lrIndex = lrIndex - (FirstSpeed / 10);
            if (lrIndex < 0)
            {
                lrIndex = -1;
            }
        }
        break;

    case GLUT_KEY_RIGHT:
        if (lrIndex <= 44)
        {
            lrIndex = lrIndex + (FirstSpeed / 10);
            if (lrIndex > 44)
            {
                lrIndex = 45;
            }
        }
        break;

    default:
        break;
    }
}

void processKeys(unsigned char key, int x, int y)
{

    switch (key)
    {
    case ' ':
        if (start == 0)
        {
            //PlaySound("car.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            start = 1;
            gv = 0;
            FirstSpeed = 50;
            roadDivTop = 0;
            roadDivMdl = 0;
            roadDivBtm = 0;
            lrIndex = 0;
            Car1 = 0;
            lrIndex1 = 0;
            Car2 = +35;
            lrIndex2 = 0;
            car3 = +70;
            lrIndex3 = 0;
            score = 0;
            level = 0;
        }
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FirstSpeed, timer, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 650);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("2D-Car-Game by MD RUBEL");



    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);

    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}