#include<iostream>
#include<GL/glut.h> 
#include<math.h>

using namespace std; 

void drawLine(int, int, int, int);
void drawCircle(int, int, int);
int x2, y2;
int currentAngle = 180;
int minAngle = 120;
int maxAngle = 240;
bool toLeft= true;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(0,0,200,currentAngle);
    drawCircle(30, x2, y2);
    glFlush();
    
}

void idle(int){
    if(toLeft){
        if(currentAngle+1 > maxAngle){
            toLeft = false;
            currentAngle -= 1;
        }else{
            currentAngle +=1;
        }
    }else{
        if(currentAngle+1 < minAngle){
            toLeft = true;
            currentAngle+=1;
        }else{
            currentAngle-=1;
        }
    }
    string header = "[idle]";
    cout<<header<<"currentAngle :"<<currentAngle<<endl;
    glutPostRedisplay();
    glutTimerFunc(1000/60, idle, 1);
}

void drawLine(int x, int y, int length, int angle){
    x2 = length*(sin(angle*3.14/180))+x;
    y2 = length*(cos(angle*3.14/180))+y;
    string header = "[drawLine]";
    cout<<header<<"x2- "<<x2<<endl;
    cout<<header<<"y2 - "<<y2<<endl;

    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(x2,y2);
    glEnd();
    glFlush();

}

void drawCircle(int r, int xc, int yc){
    glBegin(GL_POINTS);
        for(int i=0; i<=360; i++){
            glVertex2f(r*(sin(i*3.14/180))+xc , r*(cos(i*3.14/180))+yc);
        }
    glEnd();
}

void glInit(){
    glClearColor(0,0,0,1);
    gluOrtho2D(-300,300,-300,300);
}

int main(int c, char** v){
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Fan");
    glInit();
    glutDisplayFunc(display);  
    glutTimerFunc(0, idle, 1);
    glutMainLoop();
}