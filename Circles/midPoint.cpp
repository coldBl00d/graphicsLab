#include<iostream>
#include<GL/glut.h>

using namespace std; 

double R,YO,XO;

void init(){
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Mid point circle");
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    gluOrtho2D(-300,300,-300,300);
}


void setPoints(double x, double y){
    glBegin(GL_POINTS);

        glVertex2d(XO + x, YO +y);
        glVertex2d(XO + x, YO - y);
        glVertex2d(XO - x, YO + y);
        glVertex2d(XO - x, YO - y);

        glVertex2d(XO + y, YO + x);
        glVertex2d(XO + y, YO - x);
        glVertex2d(XO - y, YO + x);
        glVertex2d(XO - y, YO - x);
        
    glEnd();
}

void display(void){
    //midpoint algorithm
    double p = 1-R;
    double twoXKPlusOne, twoYKPlusOne;
    double x =0, y = R;

    setPoints(x,y);
    while(x<y){
        x++;
        if(p<0){
            p+= 2*x+1;
        }else{
            --y;
            p+= 2*(x-y)+1;
        }

        setPoints(x,y);
    }   

    glFlush();
}

int main(int argc, char **argv) {
    cout<< "Enter the center"<<endl;
    cin>>XO>>YO;
    cout<< "Enter the radius"<<endl;
    cin>>R;
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}