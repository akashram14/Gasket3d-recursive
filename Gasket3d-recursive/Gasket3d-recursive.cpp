#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef GLfloat point3[3];

void triangle(point3 a, point3 b, point3 c) {
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void divide(point3 a, point3 b, point3 c, point3 d, int k) {
    if (k > 0) {
        point3 ab, bc, ac, ad, bd, cd;
        for (int i = 0; i < 3; i++) ab[i] = (a[i] + b[i]) / 2;
        for (int i = 0; i < 3; i++) ac[i] = (a[i] + c[i]) / 2;
        for (int i = 0; i < 3; i++) bc[i] = (b[i] + c[i]) / 2;
        for (int i = 0; i < 3; i++) ad[i] = (a[i] + d[i]) / 2;
        for (int i = 0; i < 3; i++) bd[i] = (b[i] + d[i]) / 2;
        for (int i = 0; i < 3; i++) cd[i] = (c[i] + d[i]) / 2;
            
        divide(a, ab, ac, ad,k-1);
        divide(b, ab, bc, bd,k-1);
        divide(c, ac, bc, cd,k-1);
        divide(d, ad, bd, cd,k-1);
        
    }
    else {
        glColor3f(1.0, 0.0, 0.0);
        triangle(a, b, c);
        glColor3f(0.0, 0.0, 1.0);
        triangle(a, c, d);
        glColor3f(0.0, 1.0, 0.0);
        triangle(a, b, d);
        glColor3f(0.0, 0.0, 0.0);
        triangle(b, c, d);
    }

}

void myInit()
{
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    point3 a = { 0.0,0.0,1.0 };
    point3 b = { 0.0,0.942809,-0.333333 };
    point3 c = { -0.816497,-0.471405,-0.333333 };
    point3 d = { 0.816497,-0.471405,-0.333333 };
    int n = 1;

    divide(a, b, c, d, n);

    glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);  //to get exact aspect ratio
    else
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}


int32_t main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);


    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("3D Sirepinski Gasket");
    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);


    glutMainLoop();

}