#include<iostream> 
#include<GL/glut.h> 
#include<list> 

using namespace std; 

//view port 

float xmin=220;
float ymin=220;
float xmax=420;
float ymax=420;

enum Edge {LEFT, RIGHT, BOTTOM, TOP};

class Point{
    public: 
        float x; 
        float y;
        
        Point(){};
        Point(float x,float y){
            this->x=x;
            this->y=y;
        }
};

list<Point> polygon;

void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0,0.0);
	glBegin(GL_POLYGON); 
	for (Point point : polygon)
		glVertex2i(point.x,point.y);
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


bool inside(Point a, Edge e){

    switch(e){
        case LEFT:
            if(a.x>xmin) return true; 
            else return false;
        case RIGHT:
            if(a.x<xmax) return true;
            else return false;
        case BOTTOM:
            if(a.y>ymin) return true;
            else return false;
        case TOP:
            if(a.y < ymax) return true;
            else return false;

        default: return false; 
    }

}

Point* compute_intersection(Point a, Point b, Edge e){
    float m;
    float c;

    if(a.x != b.x){
        m = (b.y-a.y)/(b.x-a.x);
    }else{
        m = 0;
    }

    cout<<"LOG::m "<<m<<endl;
    c = a.y - m*(a.x);

    float new_x, new_y;

    switch(e){
        case LEFT:
            if(m == 0)
                return new Point(xmin, b.y);
            new_x = xmin;
            new_y = m*new_x+c;
            return new Point(new_x, new_y);
        case RIGHT:
            if(m==0)
                return new Point(xmax, b.y);
            new_x = xmax;
            new_y = m*new_x+c;
            return new Point(new_x, new_y);
        case BOTTOM:
            if(m==0)
                return new Point(b.x, ymin);
            new_y = ymin;
            new_x = (new_y - c)/m; 
            return new Point(new_x, new_y);
        case TOP:
            if(m==0)
                return new Point(b.x, ymax);
            new_y = ymax;
            new_x = (new_y - c)/m;
            return new Point(new_x, new_y);
    }
}

list<Point> out_list; 

list<Point> clip(list<Point> inList, Edge edge){
    out_list.clear();
    Point s = inList.back();
    for(Point e : inList){
        //check if current point is inside
        cout<<"LOG:: clip - Edge "<<edge<<"-"<<e.x<<","<<e.y<<endl;
        if(inside(e, edge)){
            cout<<"LOG:: clip - Edge "<<edge<<"-"<<e.x<<","<<e.y<<" is inside edge "<<edge<<endl;
            if(!inside(s, edge)){
                out_list.push_back(*compute_intersection(e,s, edge));
                cout<<"LOG::Pushing- "<<(*compute_intersection(e,s, edge)).x<<","<<(*compute_intersection(e,s, edge)).y<<endl;
            }
            out_list.push_back(e);
        }else if(inside(s,edge)){
             cout<<"LOG::S clip - Edge "<<edge<<"-"<<s.x<<","<<s.y<<" is inside edge "<<edge<<endl;
            out_list.push_back(*compute_intersection(e, s, edge));
            cout<<"LOG::Pushing- "<<(*compute_intersection(e,s, edge)).x<<","<<(*compute_intersection(e,s, edge)).y<<endl;
        }
        s = e;
    }
    return out_list;
}

void initializePolygon(){
	// polygon to be clipped
	polygon.push_back(Point(100,100));
	polygon.push_back(Point(100,300));
	polygon.push_back(Point(400,300));
	polygon.push_back(Point(600,150));
	polygon.push_back(Point(400,100));
}

void sutherland_Hodgeman(){
	std::list<Point> outputList = polygon;
	outputList = clip(polygon, LEFT);
	outputList = clip(outputList, RIGHT);
	outputList = clip(outputList, BOTTOM);
	outputList = clip(outputList, TOP);
	polygon = outputList;
    cout<<"LOG::OUTPUT LIST"<<endl;
    for(Point i: outputList){
        cout<<i.x<<","<<i.y<<endl;
    }
	display();
}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  cout<<"Hello";
        sutherland_Hodgeman();
        glFlush();
    }
}
void init(void) { 
	glClearColor(0,0,0,0); 
	glColor3f(1.0f,0.0f,0.0f); 
	glPointSize(4.0); 
	glMatrixMode(GL_PROJECTION); 
	glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
	glLoadIdentity(); 
	gluOrtho2D(0 , 640 , 0 , 640); 
} 

int main(int argc,char * argv[]) { 
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	glutInitWindowSize(800,600); 
	glutInitWindowPosition(100,100); 
	glutCreateWindow("Sutherland Hodgeman Polygon Clipping"); 
	//initialise polygon coordinates
	initializePolygon();
	init(); 
	glutMainLoop(); 
	return 0; 
}
