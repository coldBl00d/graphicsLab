compile with 

g++ -o executableName programName.cpp -lGL -lGLU -lglut


Writing the program in openGL 

Step 1 : Initialise GLUT 
glutInit(int* argc , char** argv);
Step 2 : Create a window with glutCreateWindow(char* title);

APIs 

glClearColor(r, g, b, o)
    r - red 
    g - green 
    b - blue 
    o - opacity 

    sets the background color for the window, call this initially for clearing your screen. 
    For black glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

