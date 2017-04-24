#include<iostream>
#include<GL/glut.h> 

//bits for setting up code for line endpoints 
#define LEFT 0X1
#define RIGHT 0X2
#define BOTTOM 0x4
#define TOP 0x8

/*
    If both endpoints of a line has code 0000
    then they are within the view port. 
        if !(a|b) then inside 
    If any bits in the same posistion has the same
    value then they are completly outside the view port 
        if(a&b) then line is outside 
*/

#define INSIDE(a) (!a)
#define ACCEPT(a,b) (!(a|b))
#define REJECT(a,b) (a&b)

using namespace std;

/* 
    The view port will be a quad with vertexes
    (220,220), (420,220)
    (420,220), (420,220)
    The boundaries are as folows
*/
float xmin= -220;
float ymin= -220;
float xmax= 220;
float ymax= 220;
float X1, Y1, X2, Y2; 
void display(void);
void keyHandler(unsigned char ,int ,int );


void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("DDA LINE");
    glutKeyboardFunc(keyHandler);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-300, 300, -300, 300); //ortho2d should be used only after creating the window
    
}

/* Generating the code for every endpoint, 
    we need only 4 bits so using char for storing
    to minimize wastage.
    encodeEndPoint 
    input: 
    x - x coord of line, 
    y - y coord of line
*/

unsigned char encodeEndPoint(float x, float y){

    unsigned char code = 0;
    if(x<xmin) code|=LEFT;
    if(x>xmax) code|=RIGHT;
    if(y<ymin) code|=BOTTOM;
    if(y>ymax) code|=TOP;

    return code;
}

/* Function to swap point and code point1 is 
    inside the view port. If that is within the view port 
    the other will be outside and so will be switched    
*/

void swapPoints(float *X1, float *Y1, float *X2, float *Y2, unsigned char *code1 , unsigned char *code2){
    unsigned char temp = *code2;
    *code2 = *code1;
    *code1 = temp;

    float temp2 = *X1;
    *X1 = *X2;
    *X2 = temp2;

    float temp1 = *Y1;
    *Y1 = *Y2;
    *Y2 = temp1;
}

void clipper(){
    cout<<"LOG::Called"<<endl;
    bool done = false; 
    bool draw = false;
    float m; //slope

    while(!done){
        unsigned char code1 = encodeEndPoint(X1,Y1);
        unsigned char code2 = encodeEndPoint(X2,Y2);
        if(ACCEPT(code1, code2)){
            //line is within the viewPort 
            done = true;
            draw = true;
        }else{
            //line is not completly within the view port 
            //could be outside or partially inside
            if(REJECT(code1, code2)){
                //line is outside 
                done = true; 
            }else{
                //line is partially inside
                if(INSIDE(code1)){
                    //not interested in this point
                    //swap the X1, Y1 as the interested point, that is the point outside
                    //this makes sure that X1, Y1 will be the point outside.
                    swapPoints(&X1, &Y1, &X2, &Y2, &code1, &code2);     
                }else{
                    //find intersection of the point and the boundary 
                    if(X1!=X2)
                        m = (Y2-Y1)/(X2-X1);
                    else{
                        cout<<"LOG::Cant find slope"<<endl;
                        break;
                    }

                    if(code1 & LEFT){
                        Y1 += (xmin - X1)*m;
                        X1= xmin;
                    }else if(code1 & RIGHT){
                        Y1 += (xmax -X1)*m;
                        X1 = xmax;
                    }else if(code1 & BOTTOM){
                        Y1 = ymin;
                        X1 += (ymin - Y1)*m;
                    }else if(code1 & TOP){
                        Y1 = ymax;
                        X1 += (ymax - Y1)*m;
                    }else{
                        cout<<"LOG::Unhandled condition, the line does not seem to intersect with any boundary"<<endl;
                        break;
                    }
                }
            }
        }

        if(draw){
            display();
        }
    }
}

void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();

    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINES);
    glVertex2f(X1, Y1);
    glVertex2f(X2,Y2);
    glEnd();

    glFlush();

}

void keyHandler(unsigned char key,int x,int y){
    if(key=='c'){
        clipper();
        glFlush();
    }
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