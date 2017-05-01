#include<iostream> 
#include<GL/glut.h>
#include<math.h> 
#include<vector>

using namespace std;

class Point{
    public:
        float x; 
        float y;

        Point(){};
        
        Point(float x, float y){
            this->x = x;
            this->y = y;
        }
};

class Wheel{
    public: 
        float xc, yc;
        float radius; 

        Wheel(){};
        Wheel(float xc, float yc, float radius){
            this->xc =xc;
            this->yc =yc;
            this->radius = radius;
        }

        void draw(Point translate){
            int rotation = translate.y - translate.x;
            glPushMatrix();
            int newxc = xc + translate.x;
            int newyc = yc + translate.y;
        
            glTranslatef(newxc, newyc, 0);
            glRotatef(rotation,0,0,1);
            glTranslatef(-newxc, -newyc, 0);

            float pi = 3.14;

            glBegin(GL_LINE_LOOP);
                glVertex2f(newxc, newyc);
                for(int i=0;i<360;++i){
                    float theta = i * pi / 180;
                    int x = newxc + radius * cos(theta);
                    int y = newyc + radius * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glPopMatrix();
        }
};

class Car {
    public:

    Wheel wheel_a, wheel_b; 
    vector<Point> body;
    Point translate;

    Car(int y=0){
        translate.y=y;
        translate.x=-200;
        wheel_a = Wheel(0,0,20);
        wheel_b = Wheel(50,0,20);
        body.push_back(Point(-30,0));
        body.push_back(Point(80,0));
        body.push_back(Point(80,50));
        body.push_back(Point(-30,50));
        body.push_back(Point(-30,0));
    }

    void move(int k=0){
        translate.x +=k;
    }

    void draw(){
         glColor3f(0,0,0);
         wheel_a.draw(translate);
         wheel_b.draw(translate);
         glBegin(GL_LINE_STRIP);
            for(int i=0;i<body.size();++i)
            {
                glVertex2f(body[i].x + translate.x, body[i].y + translate.y);
            }
        glEnd();
        glFlush();
    }

}car, car2(100);

void idle(int)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    car.draw();
    car2.draw();
    // randomly increase stepping
    car.move(random()%10);
    car2.move(random()%10);
    // glutTimerFunc(delay, function, parameter to pass as int)
    glutTimerFunc(50, idle, 1);
}

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