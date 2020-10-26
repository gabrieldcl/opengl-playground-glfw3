#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#define NULL_POINT_VALUE 999
#define PI 3.14159265

typedef struct Limits {
    double minX;
    double maxX;
    double minY;
    double maxY;
} Limits;

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct DiceFace {
    Point pointA;
    Point pointB;
    Point pointC;
    Point pointD;

    Point dots[6];
} DiceFace;

void runOpenGlWindow();
void printDiceFace(DiceFace* diceFaces);
void printDiceFaceDots(Point* diceFacePoints, int currentSquare);
bool checktIfDotIsValid(Point diceFacePoint);
Point scalePoint(const Point point);
void normalizeDiceFaces(DiceFace* diceFaces);
void normalizeDiceFaceDots(Point* diceFaceDots);
void drawSquare(DiceFace* diceFace);
void drawDice(DiceFace* diceFaces);
void drawDiceFaceDots(Point* diceFacePoints);
float normalizeValue(float value);
void moveDiceFaceX(DiceFace* diceFaces, float amount);
void moveDiceFaceDotsX(Point* diceFacePoints, float amount);
void movePointX(Point* point, float amount);
void moveDiceFaceY(DiceFace* diceFaces, float amount);
void moveDiceFaceDotsY(Point* diceFacePoints, float amount);
void movePointY(Point* point, float amount);
void scaleDice(DiceFace* diceFaces, float amount, float centerX, float centerY);
void changeDiceCenter(DiceFace* diceFaces, float centerX, float centerY);
void changeDiceFaceDots(Point* diceFaceDots, float centerX, float centerY);
void changePointCenter(Point* point, float centerX, float centerY);
void scaleDiceFaces(DiceFace* diceFaces, float amount);
void scaleDiceFaceDots(Point* diceFaceDots, float amount);
void scaleDicePoint(Point* point, float amount);
void rotateDice(DiceFace* diceFaces, int degree);
void rotateDiceFaceDots(Point* diceFaceDots, int degree);
void rotatePoint(Point* point, int degree);
void separateDiceFaces(DiceFace* diceFaces);
void resetDice();

Limits limits = { -10, 10, -10, 10 };

DiceFace defaultDiceFaces[6] = {
    { { -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 }, { { 0,0 }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE } } },
    { { 1, 1 }, { 3, 1 }, { 3, -1 }, { 1, -1 }, { { 1.5, 0.5 }, { 2.5, -0.5 }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE } } },
    { { -1, 3 }, { 1, 3 }, { 1, 1 }, { -1, 1 }, { { -0.5, 2.5 }, { 0, 2 }, { 0.5, 1.5 }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE } } },
    { { -1, -1 }, { 1, -1 }, { 1, -3 }, { -1, -3 }, { { -0.5, -1.5 }, { 0.5, -1.5 }, { -0.5, -2.5 }, { 0.5, -2.5 }, { NULL_POINT_VALUE, NULL_POINT_VALUE }, { NULL_POINT_VALUE, NULL_POINT_VALUE } } },
    { { -3, 1 }, { -1, 1 }, { -1, -1 }, { -3, -1 }, { { -2.5, 0.5 }, { -1.5, 0.5 }, { -2, 0 }, { -2.5, -0.5 }, { -1.5, -0.5 }, { NULL_POINT_VALUE, NULL_POINT_VALUE  } } },
    { { -5, 1 }, { -3, 1 }, { -3, -1 }, { -5, -1 }, { { -4.5, 0.5 }, { -4.5, 0 }, { -4.5, -0.5  }, { -3.5, 0.5 }, { -3.5, 0 }, { -3.5 , -0.5 } } }
};

DiceFace globalDiceFaces[6];


int main(void)
{
    normalizeDiceFaces(defaultDiceFaces);
    memcpy(globalDiceFaces, defaultDiceFaces, sizeof DiceFace * 6);
    runOpenGlWindow();
    return 0;
}

void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Movement Begin
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        moveDiceFaceX(globalDiceFaces, -1);
        return;
    }

    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        moveDiceFaceX(globalDiceFaces, +1);
        return;
    }

    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        moveDiceFaceY(globalDiceFaces, -1);
        return;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        moveDiceFaceY(globalDiceFaces, +1);
        return;
    }
    // Movement End

    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        scaleDice(globalDiceFaces, 0.2, 0, 0);
        return;
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        scaleDice(globalDiceFaces, 0.5, -2, 0);
        return;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        rotateDice(globalDiceFaces, 45);
        return;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        separateDiceFaces(globalDiceFaces);
        return;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        printf("Pressed key: %d \n", key);
        glfwSwapBuffers(window);
        resetDice();
        return;
    }
}

void runOpenGlWindow() {
    GLFWwindow* window;
    if (!glfwInit())
        return;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, handleKeyboard);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // DRAW BEGIN
        drawDice(globalDiceFaces);
        // DRAW END

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void resetDice() {
    memcpy(globalDiceFaces, defaultDiceFaces, sizeof DiceFace * 6);
}

void printDiceFace(DiceFace* diceFaces) {
    for (int i = 0; i < 6; i++) {
        printf(
            "Square (%d) -> Point 1: %f, %f | Point 2: %f, %f | Point 3: %f, %f | Point 4: %f, %f |\n",
            i,
            diceFaces[i].pointA.x, diceFaces[i].pointA.y,
            diceFaces[i].pointB.x, diceFaces[i].pointB.y,
            diceFaces[i].pointC.x, diceFaces[i].pointC.y,
            diceFaces[i].pointD.x, diceFaces[i].pointD.y
       );
        printDiceFaceDots(diceFaces[i].dots, i);
    }
}

void printDiceFaceDots(Point* diceFacePoints, int currentSquare) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFacePoints[i]);
        if (isDotValid) {
            printf(
                "Current Square (%d) -> Dot %d: %f, %f \n",
                currentSquare,
                i,
                diceFacePoints[i].x,
                diceFacePoints[i].y
            );
        }
    }
}

bool checktIfDotIsValid(Point diceFacePoint) {
    if (diceFacePoint.x == NULL_POINT_VALUE || diceFacePoint.y == NULL_POINT_VALUE) {
        return false;
    }

    return true;
}

Point scalePoint(const Point point) {
    /*printf("Limit: MinX: %f MaxX: %f Miny: %f MaxY: %f\n", limits.minX, limits.maxX, limits.minY, limits.maxY);*/
    Point scaledPoint;
    scaledPoint.x = ((2 / (limits.maxX - limits.minX)) * (point.x - limits.minX)) - 1;
    scaledPoint.y = ((2 / (limits.maxY - limits.minY)) * (point.y - limits.minY)) - 1;
    return scaledPoint;
}

float normalizeValue(float value) {
    float normalizedValue = ((2 / (limits.maxX - limits.minX)) * (value - limits.minX)) - 1;

    return normalizedValue;
}

void normalizeDiceFaces(DiceFace* diceFaces) {
    for (int i = 0; i < 6; i++) {
        diceFaces[i].pointA = scalePoint(diceFaces[i].pointA);
        diceFaces[i].pointB = scalePoint(diceFaces[i].pointB);
        diceFaces[i].pointC = scalePoint(diceFaces[i].pointC);
        diceFaces[i].pointD = scalePoint(diceFaces[i].pointD);
        normalizeDiceFaceDots(diceFaces[i].dots);
    }
}

void normalizeDiceFaceDots(Point* diceFaceDots) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFaceDots[i]);
        if (isDotValid) {
            diceFaceDots[i] = scalePoint(diceFaceDots[i]);
        }
    }
}

void drawDice(DiceFace* diceFaces) {
    glColor3f(1.0, 0.0, 0.0);

    for (int i = 0; i < 6; i++) {
        DiceFace* currentDiceFace = &diceFaces[i];

        drawSquare(currentDiceFace);
        drawDiceFaceDots(currentDiceFace->dots);
    }

}

void drawSquare(DiceFace* diceFace) {
    glBegin(GL_LINES);

    glVertex2d(diceFace->pointA.x, diceFace->pointA.y);
    glVertex2d(diceFace->pointB.x, diceFace->pointB.y);


    glVertex2d(diceFace->pointB.x, diceFace->pointB.y);
    glVertex2d(diceFace->pointC.x, diceFace->pointC.y);

    glVertex2d(diceFace->pointC.x, diceFace->pointC.y);
    glVertex2d(diceFace->pointD.x, diceFace->pointD.y);


    glVertex2d(diceFace->pointD.x, diceFace->pointD.y);
    glVertex2d(diceFace->pointA.x, diceFace->pointA.y);

    glEnd();
}

void drawDiceFaceDots(Point* diceFacePoints) {
    bool isDotValid;
    glBegin(GL_POINTS);
    glPointSize(10);
    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFacePoints[i]);
        if (isDotValid) {
            glVertex2d(diceFacePoints[i].x, diceFacePoints[i].y);
        }
    }

    glEnd();
}

void moveDiceFaceX(DiceFace* diceFaces, float amount) {
    for (int i = 0; i < 6; i++) {
        movePointX(&diceFaces[i].pointA, amount);
        movePointX(&diceFaces[i].pointB, amount);
        movePointX(&diceFaces[i].pointC, amount);
        movePointX(&diceFaces[i].pointD, amount);
        moveDiceFaceDotsX(diceFaces[i].dots, amount);
    }
}

void moveDiceFaceDotsX(Point* diceFacePoints, float amount) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFacePoints[i]);
        if (isDotValid) {
            movePointX(&diceFacePoints[i], amount);
        }
    }
}

void movePointX(Point* point, float amount) {
    point->x += normalizeValue(amount);
}

void moveDiceFaceY(DiceFace* diceFaces, float amount) {
    for (int i = 0; i < 6; i++) {
        movePointY(&diceFaces[i].pointA, amount);
        movePointY(&diceFaces[i].pointB, amount);
        movePointY(&diceFaces[i].pointC, amount);
        movePointY(&diceFaces[i].pointD, amount);
        moveDiceFaceDotsY(diceFaces[i].dots, amount);
    }
}

void moveDiceFaceDotsY(Point* diceFacePoints, float amount) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFacePoints[i]);
        if (isDotValid) {
            movePointY(&diceFacePoints[i], amount);
        }
    }
}

void movePointY(Point* point, float amount) {
    point->y += normalizeValue(amount);
}

void scaleDice(DiceFace* diceFaces, float amount, float centerX, float centerY) {
    changeDiceCenter(diceFaces, centerX, centerY);
    scaleDiceFaces(diceFaces, amount);
}

void changeDiceCenter(DiceFace* diceFaces, float centerX, float centerY) {
    for (int i = 0; i < 6; i++) {
        changePointCenter(&diceFaces[i].pointA, centerX, centerY);
        changePointCenter(&diceFaces[i].pointB, centerX, centerY);
        changePointCenter(&diceFaces[i].pointC, centerX, centerY);
        changePointCenter(&diceFaces[i].pointD, centerX, centerY);
        changeDiceFaceDots(diceFaces[i].dots, centerX, centerY);
    }
}

void changeDiceFaceDots(Point* diceFaceDots, float centerX, float centerY) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFaceDots[i]);
        if (isDotValid) {
            changePointCenter(&diceFaceDots[i], centerX, centerY);
        }
    }
}

void changePointCenter(Point* point, float centerX, float centerY) {
    point->x -= normalizeValue(centerX);
    point->y -= normalizeValue(centerY);
}

void scaleDiceFaces(DiceFace* diceFaces, float amount) {
    for (int i = 0; i < 6; i++) {
        scaleDicePoint(&diceFaces[i].pointA, amount);
        scaleDicePoint(&diceFaces[i].pointB, amount);
        scaleDicePoint(&diceFaces[i].pointC, amount);
        scaleDicePoint(&diceFaces[i].pointD, amount);
        scaleDiceFaceDots(diceFaces[i].dots, amount);
    }
}

void scaleDiceFaceDots(Point* diceFaceDots, float amount) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFaceDots[i]);
        if (isDotValid) {
            scaleDicePoint(&diceFaceDots[i], amount);
        }
    }
}

void scaleDicePoint(Point* point, float amount) {
    point->x = (point->x * amount) + point->x;
    point->y = (point->y * amount) + point->y;
}

void rotateDice(DiceFace* diceFaces, int degree) {
    for (int i = 0; i < 6; i++) {
        rotatePoint(&diceFaces[i].pointA, degree);
        rotatePoint(&diceFaces[i].pointB, degree);
        rotatePoint(&diceFaces[i].pointC, degree);
        rotatePoint(&diceFaces[i].pointD, degree);
        rotateDiceFaceDots(diceFaces[i].dots, degree);
    }
}

void rotateDiceFaceDots(Point* diceFaceDots, int degree) {
    bool isDotValid;

    for (int i = 0; i < 6; i++) {
        isDotValid = checktIfDotIsValid(diceFaceDots[i]);
        if (isDotValid) {
            rotatePoint(&diceFaceDots[i], degree);
        }
    }
}

void rotatePoint(Point* point, int degree) {
    float formatedDegree = degree * (PI / 180);
    float tempX = point->x;
    float tempY = point->y;

    point->x = tempX * cos(formatedDegree) - tempY * sin(formatedDegree);
    point->y = tempX * sin(formatedDegree) + tempY * cos(formatedDegree);
}

void separateDiceFaces(DiceFace* diceFaces) {
    for (int i = 0; i < 6; i++) {
        if (i == 1) {
            movePointX(&diceFaces[i].pointA, 1);
            movePointX(&diceFaces[i].pointB, 1);
            movePointX(&diceFaces[i].pointC, 1);
            movePointX(&diceFaces[i].pointD, 1);
            moveDiceFaceDotsX(diceFaces[i].dots, 1);
        }

        if (i == 2) {
            movePointY(&diceFaces[i].pointA, 1);
            movePointY(&diceFaces[i].pointB, 1);
            movePointY(&diceFaces[i].pointC, 1);
            movePointY(&diceFaces[i].pointD, 1);
            moveDiceFaceDotsY(diceFaces[i].dots, 1);
        }

        if (i == 3) {
            movePointY(&diceFaces[i].pointA, -1);
            movePointY(&diceFaces[i].pointB, -1);
            movePointY(&diceFaces[i].pointC, -1);
            movePointY(&diceFaces[i].pointD, -1);
            moveDiceFaceDotsY(diceFaces[i].dots, -1);
        }

        if (i == 4) {
            movePointX(&diceFaces[i].pointA, -1);
            movePointX(&diceFaces[i].pointB, -1);
            movePointX(&diceFaces[i].pointC, -1);
            movePointX(&diceFaces[i].pointD, -1);
            moveDiceFaceDotsX(diceFaces[i].dots, -1);
        }
        if (i == 5) {
            movePointX(&diceFaces[i].pointA, -1);
            movePointX(&diceFaces[i].pointB, -1);
            movePointX(&diceFaces[i].pointC, -1);
            movePointX(&diceFaces[i].pointD, -1);
            moveDiceFaceDotsX(diceFaces[i].dots, -1);
        }
    }
}
