#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

const float PI = 3.14159265f;

//DDA Line Algorithm for house edges and poles
void drawLineDDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float steps = fmaxf(fabsf(dx), fabsf(dy)) * 1000.0f;
    float xInc = dx / steps, yInc = dy / steps;
    float x = x1, y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= (int)steps; ++i)
    {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Bresenham Line Algorithm for road details
void drawLineBresenham(float x1, float y1, float x2, float y2)
{
    const int SCALE = 800;
    int ix1 = (int)(x1 * SCALE), iy1 = (int)(y1 * SCALE), ix2 = (int)(x2 * SCALE), iy2 = (int)(y2 * SCALE);
    int dx = abs(ix2 - ix1), dy = abs(iy2 - iy1), sx = (ix1 < ix2) ? 1 : -1, sy = (iy1 < iy2) ? 1 : -1, err = dx - dy;
    glBegin(GL_POINTS);
    while (true)
    {
        glVertex2f((float)ix1 / SCALE, (float)iy1 / SCALE);
        if (ix1 == ix2 && iy1 == iy2) break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            ix1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            iy1 += sy;
        }
    }
    glEnd();
}

// Helper circle function
void drawFilledCircle(float xc, float yc, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i)
    {
        float theta = 2.0f * PI * i / 100.0f;
        glVertex2f(xc + r * cosf(theta), yc + r * sinf(theta));
    }
    glEnd();
}

// Village Elements logic
void drawTree(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.015f, 0.00f);
    glVertex2f(0.015f, 0.00f);
    glVertex2f(0.010f, 0.18f);
    glVertex2f(-0.010f, 0.18f);
    glEnd();
    glColor3f(0.1f, 0.55f, 0.1f);
    drawFilledCircle(0.00f, 0.22f, 0.08f);
    drawFilledCircle(-0.06f, 0.18f, 0.06f);
    drawFilledCircle(0.06f, 0.18f, 0.06f);
    glPopMatrix();
}

void drawHouse(float x, float y, float r, float g, float b, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(0.20f, 0.00f);
    glVertex2f(0.20f, 0.15f);
    glVertex2f(0.00f, 0.15f);
    glEnd();
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.15f);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.10f, 0.28f);
    glEnd();
    glColor3f(0.2f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.07f, 0.00f);
    glVertex2f(0.13f, 0.00f);
    glVertex2f(0.13f, 0.08f);
    glVertex2f(0.07f, 0.08f);
    glEnd();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // Grass
    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.20f);
    glVertex2f(1.0f, -0.20f);
    glVertex2f(1.0f, -0.65f);
    glVertex2f(-1.0f, -0.65f);
    glEnd();
    // Render Village
    drawTree(-0.95f, -0.32f, 1.00f);
    drawHouse(-0.85f, -0.52f, 0.70f, 0.10f, 0.10f, 1.00f);
    drawTree(-0.62f, -0.28f, 0.75f);
    drawHouse(-0.52f, -0.42f, 0.20f, 0.40f, 0.80f, 0.70f);
    drawTree(-0.32f, -0.22f, 0.55f);
    drawTree(0.32f, -0.22f, 0.55f);
    drawHouse(0.42f, -0.42f, 0.50f, 0.20f, 0.10f, 0.70f);
    drawTree(0.68f, -0.28f, 0.75f);
    drawHouse(0.78f, -0.52f, 0.10f, 0.50f, 0.20f, 1.00f);
    drawTree(0.98f, -0.32f, 1.00f);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Village Foundation");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
