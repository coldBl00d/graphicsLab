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
    gluOrtho2D(-300, 300, -300, 300); //ortho2d should be used only after creating the window
    
}

void display(void){
    //render function for bres algorithm
    //draw starting point
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x,y;
    int limit; 
    //store the leftmost point in x and y 
    if(X1<X2){
        x=X1;
        y=Y1;
        limit = round(X2);
    }else{
        x=X2;
        y=Y2;
        limit = round(X1);
    }
 
    float dx = abs(X2-X1);
    float dy = abs(Y2-Y1);
    float twoDy = 2*dy;
    float twoDyMinusDx = 2*(dy-dx); 
    float p = twoDy - dx;
    cout<<"LOG::P:"<<p<<endl;
    cout<<"LOG::limit:"<<limit<<endl;
    cout<<"LOG::x:"<<x<<endl;
    cout<<"LOG::dy--"<<dy<<endl;

    glClear(GL_COLOR_BUFFER_BIT);
    
    glVertex2d(x,y);


    while(x < limit){
        cout<<"LOG::Looping.."<<x<<endl;
        cout<<"LOG::P:"<<p<<endl;
        x++;
        if(p<0){
            p += twoDy;
        }else{
            p = p+(twoDyMinusDx);
            y++;
        }
        cout<<"LOG::Plotting--"<<x<<","<<y<<endl;
        glVertex2d(x,y);
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