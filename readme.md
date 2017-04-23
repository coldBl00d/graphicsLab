compile with 

g++ -o executableName programName.cpp -lGL -lGLU -lglut


Writing the program in openGL 

Step 1 : Initialise GLUT 
glutInit(int* argc , char** argv);
Step 2 : Create a window with glutCreateWindow(char* title);
Step 3 : Specify the size of the window with glutInitWindowSize(int h, int b);
Step 4 : Bind the drawing function with the window glutDisplayFunc(void function);
Step 5 : Perform Your init 
Step 6 : Start event processing loop with glutMainLoop()


**********************************************************************************************
APIs 

glClearColor(r, g, b, o)
    r - red 
    g - green 
    b - blue 
    o - opacity 

    sets the background colo1r for the window, call this initially for clearing your screen. 
    For black glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

gluOrtho2D(left, right, bottom, top)

    left and right of vertical clipping plane 
    bottom and top of horizontal clipping plane

