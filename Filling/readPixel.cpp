#include<iostream> 
#include<GL/glut.h> 
#include<string>

using namespace std;



void drawPolygon(int x1, int y1, int x2, int y2){
       glColor3f(1.0, 0.0, 0.0);
       glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);
       glEnd();
       glFlush();
}

void display()
{
        string header = "[display]";
        
       glClearColor(0.0,0.0,0.0,1.0);
       glClear(GL_COLOR_BUFFER_BIT);
       drawPolygon(100,100,200,200);
       glFlush();
        float data[3];
       glReadPixels(105, 105, 1,1, GL_RGB, GL_FLOAT, data);
       

}

void getPixel(int x, int y, float data[3])
{
    string header = "[getPixel]";    
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,data);
    cout<<"["<<header <<"] data[0] "<<data[0]<<endl;
    cout<<"["<<header <<"] data[1] "<<data[1]<<endl;
    cout<<"["<<header <<"] data[2] "<<data[2]<<endl;
    
}

void mouseListener(int button, int state, int x, int y){
    string header = "[mouseListener]";
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        float data[3];
        getPixel(x,800-y, data);
        //glReadPixels(x,y,1.0,1.0,GL_RGB, GL_FLOAT, data );
        
    }
}

void myinit()
{
      glViewport(0,0,800,800);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,(GLdouble)800,0.0,(GLdouble)800);
      glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
       glutInit(&argc,argv);
       glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(800,800);
       glutCreateWindow("Flood-Fill-Recursive");
       glutDisplayFunc(display);
       myinit();
       glutMouseFunc(mouseListener);
       glutMainLoop();
       return 0;
}
