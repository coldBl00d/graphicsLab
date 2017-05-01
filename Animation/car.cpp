#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<math.h>
#define pi 3.14
using namespace std;

// Point class, for x and y
struct Point
{
    int x, y;
    Point(int a=0, int b=0){x=a; y=b;}
};

// Wheel class, has a radius and a center
class Wheel {
public:
    Point center;
    int radius;
    Wheel(){}
    Wheel(int x, int y, int r)
    {
        center=Point(x,y);
        radius=r;
    }

    // Draw the weel
    void draw(Point translate)
    {
        //simple way to get how much the wheel has rotated, - is the clockwise direction
        int rotation=-translate.x - translate.y; 
        // push matrix is used so that only the wheel is rotated and none of the others are affected
        // push means save what all have been drawn till now so that they wont be affected.
        glPushMatrix();
        int newX = center.x + translate.x;
        int newY = center.y + translate.y;
        // rotate about center, TRT', The order needs to be reversed for it to work
        glTranslatef(newX, newY, 0);
        glRotatef(rotation, 0, 0, 1);
        glTranslatef(-newX, -newY, 0);

        glBegin(GL_LINE_LOOP);
            glVertex2f(newX,newY);
            for(int i=0;i<360;++i)
            {
                float theta = i * pi / 180;
                int x = newX + radius * cos(theta);
                int y = newY + radius * sin(theta);
                glVertex2f(x, y);
            }
        glEnd();
        glPopMatrix();
    }
};
// Car class, has body and wheels
class Car
{
public:
    // body of the car
    vector<Point> body;
    Wheel a,b;
    Point translate;
    Car(int y=0)
    {
        // start the car at the left edge
        translate.y=y;
        translate.x=-200;
        a=Wheel(0,0,20);
        b=Wheel(50,0,20);
        // A shitty body for the car
        body.push_back(Point(-30,0));
        body.push_back(Point(80,0));
        body.push_back(Point(80,50));
        body.push_back(Point(-30,50));
        body.push_back(Point(-30,0));
    }

    void step(int k=0)
    {
        // increasing translate is the step
        translate.x+=k;
    }

    void draw()
    {
        // Clear previous screen
        glColor3f(0,0,0);
        a.draw(translate);
        b.draw(translate);
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<body.size();++i)
            {
                glVertex2f(body[i].x + translate.x, body[i].y + translate.y);
            }
        glEnd();
        glFlush();
    }
}car, car2(100);

// idle function is called with a timer so that the animation is slowed down
void idle(int)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    car.draw();
    car2.draw();
    // randomly increase stepping
    car.step(random()%10);
    car2.step(random()%10);
    // glutTimerFunc(delay, function, parameter to pass as int)
    glutTimerFunc(50, idle, 1);
}


// Dummy display
void display()
{
}

void init()
{
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("glLab");
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutTimerFunc(0, idle, 1);
    gluOrtho2D(-250,250,-250,250);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
}