#include "main.h"
#include "timer.h"
#include "ball1.h"
#include "magnet.h"
#include "floor.h"
#include "trampoline.h"
#include "pond.h"
#include "ball.h"
#include "porcupine.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

char buff[100];
int cindex;
int level=1;
double cangle;
int lflag=0,rflag=0,uflag=0;
// int ball.score=0;
int mtime=0,ptime=0;
Floor floor1;
Pond pond;
Porcupine porc;
Magnet magnet;
Trampoline tramp;
Ball balls[100];
Ball1 ball;
int collide=-1;
int ticks=0;
int maxi=10,cur=10,i;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);
Timer t1sec(0.4);

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(ball.mflag==1)
        magnet.draw(VP);
    for(i=0;i<cur;i++)
        balls[i].draw(VP);
    floor1.draw(VP);
    pond.draw(VP);
    tramp.draw(VP);
    ball.draw(VP);
    if(ball.porcflag==1)
        porc.draw(VP);
    // ball1.draw(VP);
    // ball2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_S);
    if (left) {
        lflag=1;rflag=0;
        ball.speedx = ball.backvar;
        ball.speedx = abs(ball.speedx);
        ball.position.x -= ball.speedx; 
    }
    else if(right)
    {
        lflag=0;rflag=1;
        ball.speedx = ball.backvar;
        ball.speedx = -abs(ball.speedx);
        ball.position.x -= ball.speedx;
    }
    else if(up && ball.flag ==0 && (ball.position.x<=-3 || ball.position.x>=-1))
    {
        ball.speedx=0;
        ball.speedy=0.19;
        ball.flag=1;
    }
    else if (up && ball.position.y<=-3+ball.radius)
    {
        ball.speedy=0.12;
        ball.position.y+=ball.speedy;
        ball.wflag=1;
    }
    else 
    {
        if(ticks% 3 == 0)
        {
            lflag=0;
            rflag=0;
        }
    }
}

void tick_elements() {
    // srand(time(NULL));
    // double posx,posy;
    sprintf(buff,"Level :- %d        Score:- %d ",level, ball.score);
    glfwSetWindowTitle(window, buff);
    for(i=0;i<cur;i++)
        balls[i].tick();
    if(ball.porcflag==1 && porc.speed>0)
    {
        if(porc.position.x>1)
            porc.position.x-=0.01;
        else if(porc.position.x<=1)
        {
            porc.position.x=1;
            porc.speed=-1;
        }
    }
    else if(ball.porcflag==1 && porc.speed<0)
    {
        if(porc.position.x<1.8)
            porc.position.x+=0.01;
        else if (porc.position.x>=1.8)
        {
            porc.position.x=1.8;
            porc.speed=1;
        }

    }
    if(detect_collision())
    {
        if(balls[cindex].pflag==0)
        {
            if(balls[cindex].cnum==0)
                ball.score+=20;
            else if (balls[cindex].cnum==1)
                ball.score+=40;
            else if(balls[cindex].cnum==2)
                ball.score+=60;
            ball.speedx=0;
            ball.speedy = 0.21;
        }
        else 
        {
            ball.score+=100;
            double s1=ball.speedx,s2=ball.speedy;
            // ball.speedy=0.21;
            // ball.speedx=-s1;
            // ball.speedy=(cos((3.14*cangle)/180)*cos((3.14*cangle)/180))*(s1+s2)+(sin((6.28*cangle)/180)/2)*(s2-s1);
            ball.speedx = (s1*cos((6.28*cangle)/180) + s2*sin((6.28*cangle)/180));
            if((s1*sin((6.28*cangle)/180) - s2*cos((6.28*cangle)/180))<0)
                ball.speedy = (s1*sin((6.28*cangle)/180) - s2*cos((6.28*cangle)/180)); 
            else
                ball.speedy = (s1*sin((6.28*cangle)/180) - s2*cos((6.28*cangle)/180))+0.04; 
            // ball.speedx=-abs(ball.speedy*sin((6.28*cangle)/180)/2);
            // ball.speedy=ball.speedy*(cos((3.14*cangle)/180)*cos((3.14*cangle)/180));
        }
        double posy1=(rand()%21-10)*0.1;// -10
        double speed = (rand()%3 + 2)*0.01;
        double pflag=rand()%2;
        balls[i]=Ball(-4,posy1,COLOR_YELLOW, speed, pflag);
        balls[i].speedx = -balls[i].speedx;
    }
    ball.tick();
    // if(ball.position)

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */

    double posx,posy,pflag,speed;
    color_t color;
    int cnum;
    for(i=0;i<10;i++)
    {
        posy=(rand()%21-10)*0.1;   
        posx=(rand()%81-40)*0.1;
        speed = (rand()%3 + 2)*0.01;
        pflag = rand()%2;
        cnum = rand()%3;
        if(cnum==0)
            color=COLOR_YELLOW;
        else if (cnum==1)
            color=COLOR_PINK;
        else if(cnum ==2) 
            color = COLOR_OCRE;

        // printf("\n%f\n",posx);
        balls[i]=Ball(posx, posy, color, speed, pflag);
        balls[i].cnum=cnum;
        balls[i].speedx=-balls[i].speedx;
    }
    magnet = Magnet(COLOR_GRAY);
    floor1 = Floor(COLOR_GREEN);
    pond = Pond(COLOR_WATER);
    speed = rand()%3-1;
    if(speed>=0)
        speed=1;
    else 
        speed=-1;
    porc = Porcupine(1,-2,COLOR_BLACK,speed);
    tramp = Trampoline(COLOR_BROWN);
    speed = (rand()%3 + 4)*0.01;
    ball = Ball1(-3.8, -1.75, COLOR_BLUE, speed);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    int width  = 600;
    int height = 600;
    double posx,posy1,posy2,pflag; 
    window = initGLFW(width, height);
    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            ticks++;
            if(ticks % 1500 ==0 && ball.score<400)
                quit(window);
            if(ticks% 3600==0 && ball.score<1200)
                quit(window);
            if(ball.score>=400 && level <2)
                level=2;
            if(ball.score>=1200)
                level=3;
            if(ticks%600==0 && ball.score>=400)
            {
                ball.mflag=1;
                mtime=ticks;
            }
            if(ball.mflag==1 && ticks-mtime==360)
            {
                ball.mflag=0;
                // mtime/
            }
            if(ticks%900==0 && ball.score>=1200 && ball.porcflag==0)
            {
                level=3;
                ball.porcflag=1;
            }
            if(ball.position.x>=porc.position.x && ball.porcflag==1 && ball.position.x<=porc.position.x+1.2 && fabs(ball.position.y-ball.origin)<0.03)
            {
                ball.score-=40;
                ball.porcflag=0;
            }
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            // }
        }
        if(t1sec.processTick())
        {
            // printf("%d\n",ball.score);
            // printf("speed-> %f\n",ball.speedx);
            // printf("x-> %f y-> %f radius-> %f\n",ball.position.x,ball.position.y,ball.radius);
            // printf("\n%f\n",fabs(ball.position.y+2+ball.radius));
            int flag=0;
            color_t color;
            for(i=0;i<cur;i++)
            {
                if(balls[i].position.x >=3.8)
                {
                    int cnum;
                        // posx=(rand()%41)*0.1;
                    posy1=(rand()%21-10)*0.1; // -10
                    double speed = (rand()%3 + 2)*0.01;
                    pflag = rand()%2;
                    cnum = rand()%3;
                    if(cnum==0)
                        color=COLOR_YELLOW;
                    else if (cnum==1)
                        color=COLOR_PINK;
                    else if(cnum ==2) 
                        color = COLOR_OCRE;
                    balls[i]=Ball(-4,posy1,color, speed, pflag);
                    balls[i].cnum=cnum;
                    balls[i].speedx = -balls[i].speedx;
                    flag =1;
                    // collide = -1;
                }
                if(flag)
                    break;
            }
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision() {
    double posy1;
    for(i=0;i<cur;i++)
    {
        if((abs(balls[i].position.x-ball.position.x)<= balls[i].radius + ball.radius && abs(balls[i].position.y-ball.position.y)<= balls[i].radius + ball.radius) && 
            ball.speedy <= 0 && abs(balls[i].position.y-ball.position.y)>= ball.radius + balls[i].radius/3 && ball.position.y > balls[i].position.y)
        {
            cangle=balls[i].angle;
            cindex=i;
            // posy1=(rand()%11 - 10)*0.1;
            // double speed = (rand()%3 + 4)*0.01;
            // double pflag=rand()%2;
            // balls[i]=Ball(-4,posy1,COLOR_YELLOW, speed, pflag);
            // balls[i].speedx = -balls[i].speedx;
            // collide = i;
            return 1;
        }
    }
    return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}