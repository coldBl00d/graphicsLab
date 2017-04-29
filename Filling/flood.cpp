#include<iostream>
#include<GL/glut.h> 
#include<list> 
#include<queue>

using namespace std;

class Point {
    public:
        float x;
        float y;

        Point() {
            this->x =0; 
            this->y =0;
        }

        Point(float x, float y){
            this->x = x;
            this->y = y;
        }

        void identify(){
            cout<<"Point : "<< 
                "("<<this->x<<","<<this->y<<")"<<endl;
        }
};

list<Point> polygon; 
float target_color[3] = {1.0f,0.0f,0.0f};
float replacement_color[3] ={0.0f,0.0f,1.0f};
float pixelData[3];

void setPixel(Point p, float color[3]){
    glBegin(GL_POINTS);
        glColor3f(color[0],color[1],color[2]);
        glVertex2f(p.x,p.y);
    glEnd();
    glFlush();
}

void readPixel(Point p, float data[3]){
    
    glReadPixels((int)p.x,(int)p.y,2.0,2.0,GL_RGB,GL_FLOAT,data);
    cout<<"[readPixel] "; p.identify();
    cout<<"[readPixel] "<<data[0]<<"-"<<data[1]<<"-"<<data[2]<<endl;
}

bool isEqual(float colorA[3], float colorB[3]){
    if(colorA[0] == colorB[0] && colorA[1] == colorB[1] && colorA[2] == colorB[2])
        return true;
    else 
        return false;
}

void floodFill(Point startPoint){
    string header = "[floodFill]";
    
    readPixel(startPoint, pixelData);
    if(isEqual(pixelData, replacement_color)) {
        cout<<"[Flood Fill] "<<"Start point match replacement color"<<endl;
        return;
    }
    if(!isEqual(pixelData, target_color)){
        cout<<"[Flood Fill] "<<"Start point does not match target color"<<endl;
        return;
    }


    queue<Point> queue;
    queue.push(startPoint);

    
    while(!queue.empty()){
        Point seed = queue.front();
        queue.pop();
        Point west(seed.x-1, seed.y); 
        Point east(seed.x+1, seed.y);

        cout<<header<<"Current point :";seed.identify();
        west.identify();
        east.identify();
        float seedColor[3];
        float westColor[3];
        float eastColor[3];

        readPixel(seed, seedColor);
        
        readPixel(west, westColor);
        readPixel(east, eastColor);

        

        while(isEqual(westColor, target_color)){  
            cout<<header<<"Going west..."<<endl; 
            west.x--;
            readPixel(west, westColor);
        }
        cout<<header<<"West till :"; west.identify();

        while(isEqual(eastColor, target_color)){
            east.x++;
            readPixel(east, eastColor);
        }

        cout<<header<<"East till :"; east.identify();


        for(int i = west.x+1; i<east.x; i++){
            setPixel(*(new Point(i, west.y)), replacement_color);
            readPixel(*(new Point(i, west.y + 1)), pixelData);
            if(isEqual(pixelData, target_color))
                queue.push(*new Point(i, west.y + 1));
            readPixel(*(new Point(i, west.y - 1)), pixelData);
            if(isEqual(pixelData, target_color))
                queue.push(*new Point(i, west.y - 1));
        } 
    }
}

void mouseListener(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //call floodFill here;
        cout<<"[Mouse Listener] Calling flood fill at ("<<x<<","<<y<<")"<<endl;
        floodFill(*(new Point(x,800-y)));
    }
}

void init(){
    glViewport(0,0,800,800);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,800,0.0,800);
      glMatrixMode(GL_MODELVIEW);
    
}

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

void display(void){
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    drawPolygon(100, 100, 200, 200);
    glEnd();
    glFlush();
}



void initPolygon() {
    int n,x,y;
    cout<<"[Prompt] Enter the number of vertices of the polygon: ";
    cin>>n;
    while(n--){
        cin>>x>>y;
        Point p(x,y);
        polygon.push_back(p);
        cout<<"[Prompt] Next"<<endl;
    }
    return;
}

int main(int argc, char **argv){
   // initPolygon();
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Flood-Fill-Recursive");
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouseListener);
    glutMainLoop();
    return 0;

}