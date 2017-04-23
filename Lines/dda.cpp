#include<iostream>
#include<GL/glut.h> 
#include<math.h>
#include<stdio.h>

using namespace std;

double X1, Y1, X2, Y2;

float round(float v){
  return floor(v + 0.5);
}


void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("DDA LINE");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-300, 300, -300, 300);
}

void display(void){
    //render function for dda algorithm

    //calculate the delta between the starting and the end point along both the axis 
    float dx = X2-X1;
    float dy = Y2-Y1;
    //decide through which axis to step 
    int step = (abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
    //set up the increments through each of the axis; 
    float incX = dx/float(step);
    float incY = dy/float(step);
    //starting point for drawing
    float x = X1;
    float y = Y1;

    //draw starting point
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(round(x), round(y));

    for(int k=0; k<step ; k++){
        x += incX;
        y += incY;

        glVertex2d(round(x), round(y));

    }

    glEnd();
    glFlush();

}

int main(int argc, char **argv){
    cout<< "Enter the start point"<<endl;
    cin>>X1>>Y1;
    cout<< "Enter the end point"<<endl;
    cin>>X2>>Y2;
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}