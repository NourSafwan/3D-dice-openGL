#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Rotation angles
float rotationX = 0.0f;
float rotationY = 0.0f;

// Function to handle keyboard input
void processInput(GLFWwindow* window, float& rotationX, float& rotationY) {
    const float rotationSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        rotationX -= rotationSpeed; // Rotate upward
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        rotationX += rotationSpeed; // Rotate downward
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationY -= rotationSpeed; // Rotate left
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationY += rotationSpeed; // Rotate right
    }
}

// Function to draw a circle (used for the dice dots)
void drawCircle(float x, float y, float radius, int segments = 100) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float dx = cos(angle) * radius;
        float dy = sin(angle) * radius;
        glVertex3f(x + dx, y + dy, 0.0f);
    }
    glEnd();
}

// Function to draw a single face of the dice with dots
void drawDiceFace(int face, float size) {
    float radius = size / 10.0f; // Dot radius
    float offset = 0.02f;       // Small offset to prevent z-fighting
    glColor3f(0.0f, 0.0f, 0.0f); // Black dots

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, offset); // Slightly offset dots forward

    switch (face) {
        case 1:
            drawCircle(0.0f, 0.0f, radius);
            break;
        case 2:
            drawCircle(-0.3f * size, -0.3f * size, radius);
            drawCircle(0.3f * size, 0.3f * size, radius);
            break;
        case 3:
            drawCircle(-0.3f * size, -0.3f * size, radius);
            drawCircle(0.0f, 0.0f, radius);
            drawCircle(0.3f * size, 0.3f * size, radius);
            break;
        case 4:
            drawCircle(-0.3f * size, -0.3f * size, radius);
            drawCircle(-0.3f * size, 0.3f * size, radius);
            drawCircle(0.3f * size, -0.3f * size, radius);
            drawCircle(0.3f * size, 0.3f * size, radius);
            break;
        case 5:
            drawCircle(-0.3f * size, -0.3f * size, radius);
            drawCircle(-0.3f * size, 0.3f * size, radius);
            drawCircle(0.3f * size, -0.3f * size, radius);
            drawCircle(0.3f * size, 0.3f * size, radius);
            drawCircle(0.0f, 0.0f, radius);
            break;
        case 6:
            drawCircle(-0.3f * size, -0.3f * size, radius);
            drawCircle(-0.3f * size, 0.0f, radius);
            drawCircle(-0.3f * size, 0.3f * size, radius);
            drawCircle(0.3f * size, -0.3f * size, radius);
            drawCircle(0.3f * size, 0.0f, radius);
            drawCircle(0.3f * size, 0.3f * size, radius);
            break;
    }

    glPopMatrix();
}

// Function to draw the dice
void drawDice(float size) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_QUADS);

    // Front face (1)
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    // Back face (6)
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);

    // Left face (4)
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, -size, size);

    // Right face (3)
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(size, -size, size);

    // Top face (5)
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    // Bottom face (2)
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    glEnd();

    // Draw dots
    float zOffset = 0.01f; // Offset to prevent z-fighting

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, size + zOffset); // Front face
    drawDiceFace(1, size);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1.0f, 0.0f, 0.0f); // Back face
    glTranslatef(0.0f, 0.0f, size + zOffset);
    drawDiceFace(2, size);
    glPopMatrix();


    glPushMatrix();
    glRotatef(-90, 0.0f, 1.0f, 0.0f); // Left face
    glTranslatef(0.0f, 0.0f, size + zOffset);
    drawDiceFace(4, size);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f); // Right face
    glTranslatef(0.0f, 0.0f, size + zOffset);
    drawDiceFace(3, size);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f); // Top face
    glTranslatef(0.0f, 0.0f, size + zOffset);
    drawDiceFace(5, size);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Bottom face
    glTranslatef(0.0f, 0.0f, size + zOffset); 
    drawDiceFace(6, size);
    glPopMatrix();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    GLFWwindow* window = glfwCreateWindow(800, 600, "CG Project", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);

        processInput(window, rotationX, rotationY);

        glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

        drawDice(1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
