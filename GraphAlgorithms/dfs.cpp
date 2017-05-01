#include<iostream>
#include<GL/glut.h> 
#include<vector>
#include<math.h>
#include <unistd.h>

using namespace std; 

int node_count, edge_count;

class Point; 
vector<Point> node_list;
vector<Point> edge_list;

void display();
void init();
void dfsTraversal();
void dfs(int);
void idle(int);

class Point{
    public:
        float x; 
        float y;
        bool visited;
        vector<float> adj;

        Point() {
            this->x =0;
            this->y =0;
            this->visited = false;
        }

        Point(float x, float y){
            this->x =x;
            this->y =y;
            this->visited = false;
        }
};

void idle(int){
    dfsTraversal();
}

void drawNode(int center_x, int center_y, float color[3]){

    const int mesh_count = 360;
    const int radius =25;
    const int PI = 3.14;

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0; i<mesh_count; i++){
            glVertex2f(center_x + (radius*(sin(i*(2*PI)/mesh_count))), center_y+(radius*(cos(i*(2*PI)/mesh_count))));
        }
    glEnd();
    glColor3f(1,1,1);
    glFlush();

}

void drawEdge(int xs, int ys, int xe, int ye, float color[3]){
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_LINES);
        glVertex2f(xs, ys);
        glVertex2f(xe, ye);
    glEnd();
    glColor3f(1,1,1);
    glFlush();
}

void drawNodes(){
    float white [3] = {1,1,1};
    for(Point p: node_list){
        drawNode(p.x,p.y, white);
    }
}

void drawEdges(){
    float white[3] = {1,1,1};
    Point node1, node2;
    for(int i=0; i<edge_list.size(); i++){
        Point edge = edge_list[i];
        node1 = node_list[edge.x-1];
        node2 = node_list[edge.y-1];
        drawEdge(node1.x, node1.y, node2.x, node2.y, white);
    }
}

void parseInput(){
    string header = "[parseInput] ";
        
    float x, y;
    cin>>node_count>>edge_count;

    for(int i=0; i< node_count; i++){
        cin>>x>>y;
        node_list.push_back(*(new Point(x,y)));
    }

    for(int i=0; i< edge_count; i++){
        cin>>x>>y;
        edge_list.push_back(*(new Point(x,y)));
    }

    cout<<header<<"edge_list"<<endl;
    for(Point p: edge_list){
        cout<<header<<"edge "<<p.x<<" --> "<<p.y<<endl;
        (node_list[p.x-1]).adj.push_back(p.y);
    }

    cout<<header<<"Parsing completed"<<endl;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawNodes();
    drawEdges();
    glFlush();
    glutTimerFunc(1000, idle, 1);
}

void init(){
    //glClearColor(0,0,0,1);
    gluOrtho2D(0,600,0,600);
}

void dfs(int start){
    float green[3] = {0,1,0};
    float red[3] = {1.0,0};
    node_list[start].visited = true;
    drawNode(node_list[start].x, node_list[start].y, green);
    usleep(1000000);
    for(float adj: node_list[start].adj){
        if(node_list[adj-1].visited == false){
            drawEdge(node_list[start].x,node_list[start].y,node_list[adj-1].x, node_list[adj-1].y, red);
            dfs(adj-1);
        }
    }
}

void dfsTraversal(){
    for(int i=0; i< node_count; i++){
        if(node_list[i].visited == false)
            dfs(i);
    }
}

int main(int c, char **v){
    parseInput();
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("DFS");
    init();
    glutDisplayFunc(display); 
    glutMainLoop();
}