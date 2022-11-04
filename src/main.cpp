#include <GL/glut.h>
#include "obj.hpp"
#include <math.h>

// globals
GLuint escena;
GLuint nave;

// other functions and main
// wavefront .obj loader code begins

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = -1;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 4.0f;

// wavefront .obj loader code ends here
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    // glOrtho(-25,25,-2,2,0.1,100);
    // glMatrixMode(GL_MODELVIEW);
}

void drawScene()
{
    glPushMatrix();
    glScalef(1, 1, 1);
    glRotatef(180, 0, 1, 0);
    glCallList(escena);
    glPopMatrix();
}
void drawUfo()
{
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(x,y-1,z);
    glCallList(nave);
    glPopMatrix();
}

float i = 0;

void display(void)
{
    glClearColor(1, 0.57254, 0.28235,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawScene();
    drawUfo();

    glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy)
{

    float factor = 0.9f;

    switch (key)
    {
    case 'q':
        y -= 1;
        break;
    case 'e':
        y += 1;
        break;
    case 'a':
        angle -= 0.1f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case 'd':
        angle += 0.1f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case 'w':
        ly += 0.1f;
        break;
    case 's':
        ly -= 0.1f;
        break;
    }
}
void processSpecialKeys(int key, int xx, int yy)
{

    float factor = 0.1f;

    switch (key)
    {

    case GLUT_KEY_UP:
        if (lx > lz)
        {
            z -= 1;
        }
        else
        {
            z += 1;
        }
        break;
    case GLUT_KEY_DOWN:
        if (lx < lz)
        {
            z -= 1;
        }
        else
        {
            z += 1;
        }
        break;
    case GLUT_KEY_LEFT:
        if (lx > lz)
        {
            x -= 1;
        }
        else
        {
            x += 1;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (lx < lz)
        {
            x -= 1;
        }
        else
        {
            x += 1;
        }
        break;
    }
}

void idle()
{
    i += 0.01;
    glutPostRedisplay();
}

void init()
{
    // glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);

    glutCreateWindow("ObjLoader");

    init();
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);

    escena = loadObj("data\\calle.obj",
                       "data\\calle.mtl");
    nave = loadObj("data\\ufo.obj",
                       "data\\ufo.mtl");
    glutMainLoop();
    return 0;
}
