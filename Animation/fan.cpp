#include<iostream> 
#include<GL/glut.h> 
#include<list>

using namespace std; 

class Point{
    public:
        float x;
        float y;

        Point() {

        }

        Point(float x, float y){
            this->x = x;
            this->y = y;
        }
};

list<Point> fan; 


void initFanCoordinates(){
    fan.push_back(*(new Point(0,0)));
    fan.push_back(*(new Point(60,60)));
    fan.push_back(*(new Point(0,0)));
    fan.push_back(*(new Point(60,40)));
    fan.push_back(*(new Point(60,60)));

    fan.push_back(*(new Point(0,0)));
    fan.push_back(*(new Point(-60,-60)));
    fan.push_back(*(new Point(0,0)));
    fan.push_back(*(new Point(-60,-40)));
    fan.push_back(*(new Point(-60,-60)));
}

void glInit(){
    glClearColor(0,0,0,1);
    gluOrtho2D(-300,300,-300,300);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
        for(Point p: fan){
            glVertex2f(p.x,p.y);
        }
    glEnd();
    glFlush();
}

int speed =1;

void idle(int){
    glRotatef(speed,0,0,1); //core shit !!
    glutPostRedisplay();
    glutTimerFunc(1000/60, idle, 1);
}

void keyboard(unsigned char c, int x, int y){
    if(c=='q')
        speed ++;
    else
        speed --;
}

int main(int c, char **v){
    initFanCoordinates();
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Fan");
    glInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, idle, 1); //new shit 
    glutMainLoop();
}