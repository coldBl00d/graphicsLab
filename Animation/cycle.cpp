#include<iostream>
#include<GL/glut.h> 
#include<math.h> 

using namespace std;

const int cycle_start = 30;
const int cycle_end = 100;
const int cycle_height = 40;
const int wheel_center_y = cycle_height/2;
const int wheel_radius = cycle_height/2;

int displacement_xs = 50;
int displacement_ys = 0;
int displacement_xe = 50;
int displacement_ye = 0;

void drawCycle(int, int, int, int);
void drawRoad();
void display();

void intervalCallback(int){
    string header = "[intervalCallback]";
    displacement_xs++;
    displacement_xe++;

    if(displacement_xs+cycle_start<=200){
        displacement_ys = 1;
    }else if(displacement_xs+cycle_start >200 && displacement_xs+cycle_start <= 300){
        //(300,1) (400,100)
        const float slope = 1;
        const float c = -200;
        displacement_ys = slope*(displacement_xs+cycle_start) + c;
    }else if(displacement_xs+cycle_start > 300 && displacement_xs+cycle_start <=400){
        displacement_ys=100;
    }else if(displacement_xs+cycle_start >400 && displacement_xs+cycle_start <500){
        //(500,100), (600,0)
        const float slope = -1;
        const float c = 500;
        displacement_ys = slope*(displacement_xs+cycle_start) + c;
    }else{
        displacement_ys = 1;
    }

    if(displacement_xe+cycle_end<=200){
        displacement_ye = 1;
    }else if(displacement_xe+cycle_end >200 && displacement_xe+cycle_end <= 300){
        //(200,1) (300,100)
        const float slope = 1;
        const float c = -200;
        displacement_ye = slope*(displacement_xe+cycle_end) + c;
    }else if(displacement_xe+cycle_end > 300 && displacement_xe+cycle_end <=400){
        displacement_ye=100;
    }else if(displacement_xe+cycle_end >400 && displacement_xe+cycle_end <=500){
        //(400,100), (500,0)
        const float slope = -1;
        const float c = 500;
        displacement_ye = slope*(displacement_xe+cycle_end) + c;
    }else if(displacement_xe+cycle_end>500 && displacement_xs+cycle_start<600){
        displacement_ye = 1;
    }else if (displacement_xs+cycle_start >=600){
        displacement_xe =0;
        displacement_xs =0;
        displacement_ys =0;
        displacement_ye =0;
    }

    cout<<header<<" displacement_xs: "<<displacement_xs+cycle_start<<endl;
    cout<<header<<" displacement_xe: "<<displacement_xe+cycle_end<<endl;
    glutTimerFunc(1000/900, intervalCallback, 1);
    display();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawCycle(displacement_xs,displacement_ys,displacement_xe,displacement_ye);
    drawRoad();
    glFlush();
}

void drawCycle(int xds, int yds, int xde, int yde){
    glBegin(GL_LINES);
        glVertex2f(cycle_start+xds,cycle_height+yds);
        glVertex2f(cycle_end+xde,cycle_height+yde);
    glEnd();

    glBegin(GL_POINTS);
        for(int i=0; i<=360; i++){
            glVertex2f(wheel_radius*(sin(i*3.14/180))+cycle_start+xds , wheel_radius*(cos(i*3.14/180))+wheel_center_y+yds);
        }
    glEnd();

     glBegin(GL_POINTS);
        for(int i=0; i<=360; i++){
            glVertex2f(wheel_radius*(sin(i*3.14/180))+cycle_end+xde , wheel_radius*(cos(i*3.14/180))+wheel_center_y+yde);
        }
    glEnd();
}

void drawRoad(){

    glBegin(GL_LINES);
        glVertex2f(0,1);
        glVertex2f(200,1);
        glVertex2f(200,1);
        glVertex2f(300, 100);
        glVertex2f(300, 100);
        glVertex2f(400, 100);
        glVertex2f(400, 100);
        glVertex2f(500, 1);
        glVertex2f(500, 1);
        glVertex2f(600,1);
    glEnd();    
}

void glInit(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,600,0,600);
}

int main(int c, char** v){
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Cycle");
    glInit();
    glutDisplayFunc(display); 
    glutTimerFunc(1000/30,intervalCallback,1); 
    glutMainLoop();
}