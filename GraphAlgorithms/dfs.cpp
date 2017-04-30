#include<iostream>
#include<GL/glut.h> 
#include<vector>
#include<math.h>
using namespace std; 

class Point; 
vector<Point> node_list;
vector<Point> edge_list;

class Point{
    public:
        float x; 
        float y;

        Point() {
            this->x =0;
            this->y =0;
        }

        Point(float x, float y){
            this->x =x;
            this->y =y;
        }
};



void drawNode(int center_x, int center_y, float color[3]){

    const int mesh_count = 25;
    const int radius =25;
    const int PI = 3.14;

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0; i<mesh_count; i++){
            glVertex2f(center_x + (radius*(sin(i*2*PI/mesh_count))), center_y+(radius*(cos(i*2*PI/mesh_count))));
        }
    glEnd();
    glColor3f(1,1,1);

}

void drawEdge(int xs, int ys, int xe, int ye, float color[3]){
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_LINES);
        glVertex2f(xs, ys);
        glVertex2f(xe, ye);
    glEnd();
    glColor3f(1,1,1);
}

void drawNodes(vector<Point> node_list){
    float white [3] = {1,1,1};
    for(Point p: node_list){
        drawNode(p.x,p.y, white);
    }
}

void drawEdges(vector<Point> edge_list){
    float white[3] = {1,1,1};
    Point node1, node2;
    for(int i=0; i<edge_list.size()-1; i++){
        node1 = node_list[i];
        node2 = node_list[i+1];
        drawEdge(node1.x, node1.y, node2.x, node2.y, white);
    }
}

void parseInput(){
    string header = "[parseInput] ";
    

    int node_count, edge_count; 
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

    cout<<header<<"node_list"<<endl;
    for(Point p: node_list){
        cout<<header<<"node ("<<p.x<<","<<p.y<<")"<<endl;
    }

    cout<<header<<"edge_list"<<endl;
    for(Point p: edge_list){
        cout<<header<<"edge "<<p.x<<" --> "<<p.y<<endl;
    }

    cout<<header<<"Parsing completed"<<endl;
}

int main(int c, char **v){
    parseInput();
    
}