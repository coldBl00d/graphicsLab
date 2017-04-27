#include<iostream> 
#include<GL/glut.h> 
#include<list> 

using namespace std; 

//view port
float xmin=220;
float ymin=220;
float xmax=420;
float ymax=420;

enum Edge{LEFT, RIGHT, BOTTOM, TOP};

class Point{
    public: 
        float x; 
        float y; 

        Point() {
            this->x = 0; 
            this->y = 0;
        }

        Point(float x, float y){
            this->x = x; 
            this->y = y;
        }
};

list<Point> output_list; 
list<Point> polygon; 

void initializePolygon(){
	polygon.push_back(Point(100,100));
	polygon.push_back(Point(100,300));
	polygon.push_back(Point(400,300));
	polygon.push_back(Point(600,150));
	polygon.push_back(Point(400,100));
}

bool inside_edge(Point p, Edge e){
    switch(e){
        case LEFT:
            if(p.x > xmin) return true;
            else return false;
        case RIGHT:
            if(p.x < xmax) return true;
            else return false;
        case BOTTOM:
            if(p.y>ymin) return true;
            else return false;
        case TOP: 
            if(p.y<ymax) return true;
            else return false;
    }
}

Point* find_intersection(Point a, Point b, Edge e){
    float m, c;
    float x_new, y_new;

    if(a.x != b.x){
        m = (b.y-a.y)/(b.x-a.x);
    }else{
        m = 0;
    }

    c = a.y - m*(a.x);
    
    switch(e){
        case LEFT:
            if(m == 0) //watch out for these if statements.
                return new Point(xmin, b.y);
            x_new = xmin; 
            y_new = m*x_new + c;
            return new Point(x_new, y_new);        
        case RIGHT:
            if(m==0)
                return new Point(xmax, b.y);
            x_new = xmax; 
            y_new = m*x_new + c;
            return new Point(x_new, y_new);
        case BOTTOM:
            if(m==0)
                return new Point(b.x, ymin);
            y_new = ymin;
            x_new = (y_new - c)/m;
            return new Point(x_new, y_new);
        case TOP:
            if(m==0)
                return new Point(b.x, ymax);
            y_new = ymax; 
            x_new = (y_new - c)/m;
            return new Point(x_new, y_new);
    }
}


void display(void){
    cout<<"LOG::display called"<<endl;
    glClear(GL_COLOR_BUFFER_BIT); //put this or else it wont update
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        for(Point p : polygon){
            glVertex2i(p.x,p.y);
        }
    glEnd();

    glColor3f(0.0,1.0,0.0);
   	glBegin(GL_LINE_LOOP);
        glVertex2i(xmin,ymin);
        glVertex2i(xmin,ymax);
        glVertex2i(xmax,ymax);
        glVertex2i(xmax,ymin);
   	glEnd(); 
    glFlush();
}

void clip(Edge e){
    list<Point> working_list = polygon; 
    polygon.clear();
    Point prev = working_list.back();
    for(Point current: working_list){
        if(inside_edge(current, e)){
            if(!inside_edge(prev, e)){
                polygon.push_back(*find_intersection(current, prev, e));
            }
            polygon.push_back(current);
        }else if(inside_edge(prev, e)){
            polygon.push_back(*find_intersection(current, prev, e));
        }
        prev = current;
    }
}

void sutherHodge(){
    clip(LEFT);
    clip(RIGHT);
    clip(BOTTOM);
    clip(TOP);
    display();   
}

void keyboardListener(unsigned char key, int x, int y){
    if(key == 'c'){
        sutherHodge();
    }
}

void init(){
    initializePolygon();
    glClearColor(0,0,0,0); 
	glColor3f(1.0f,0.0f,0.0f);  
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboardListener);
	gluOrtho2D(0 , 640 , 0 , 640);  //put this or else nothing will show up 
} 


int main(int argc, char **argv){
    glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	glutInitWindowSize(800,600); 
	glutCreateWindow("Polygon Clipping");
	init(); 
	glutMainLoop(); 
	return 0; 
}

