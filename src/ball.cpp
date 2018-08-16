#include "ball.h"
#include "main.h"
#include "time.h"

Ball::Ball(float x, float y, color_t color, float speed, int pflag) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->pflag=pflag;
    // this->speedx = 0.04;
    // this->speedx = (rand()%3 + 4)*0.01;
    this->speedx = speed;
    this->speedy = 0.59;
    this->origin = y;
    this->flag=0;
    GLfloat g_vertex_buffer_data[100000];  
    int i;
    int randNum;
    randNum = rand()%(3) + 3;
    this->radius = (float)1/randNum;
    float n=360,k=0;
    for(i=0;i<n*9;i+=9)
    {
        g_vertex_buffer_data[i]=(float)cos((k*3.14)/180)/randNum;
        g_vertex_buffer_data[i+1]=(float)sin((k*3.14)/180)/randNum;
        g_vertex_buffer_data[i+2]=0.0f;

        g_vertex_buffer_data[i+3]=(float)cos(((k+1)*3.14)/180)/randNum;
        g_vertex_buffer_data[i+4]=(float)sin(((k+1)*3.14)/180)/randNum;
        g_vertex_buffer_data[i+5]=0.0f;

        g_vertex_buffer_data[i+6]=0.0f;
        g_vertex_buffer_data[i+7]=0.0f;
        g_vertex_buffer_data[i+8]=0.0f;
        k++;
    }
    // double randangle*3.14/180 = 1.57;
    double randangle = (rand()%601)*0.1;
    this->angle=randangle;
    // if(pflag ==1)
    // {
        GLfloat g_vertex_buffer_data2[]={
            this->radius*sin(randangle*3.14/180) + 0.3* cos(randangle*3.14/180),this->radius*cos(randangle*3.14/180) - 0.3* sin(randangle*3.14/180), 0.0f,

            this->radius*sin(randangle*3.14/180) - 0.3* cos(randangle*3.14/180),this->radius*cos(randangle*3.14/180) + 0.3* sin(randangle*3.14/180), 0.0f,

            this->radius*sin(randangle*3.14/180) - 0.3* cos(randangle*3.14/180) + 0.1 * sin(randangle*3.14/180),this->radius*cos(randangle*3.14/180) + 0.3* sin(randangle*3.14/180) + 0.1 * cos(randangle*3.14/180), 0.0f,

            this->radius*sin(randangle*3.14/180) + 0.3* cos(randangle*3.14/180),this->radius*cos(randangle*3.14/180) - 0.3* sin(randangle*3.14/180), 0.0f,

            this->radius*sin(randangle*3.14/180) - 0.3* cos(randangle*3.14/180) + 0.1 * sin(randangle*3.14/180), this->radius*cos(randangle*3.14/180) + 0.3* sin(randangle*3.14/180) + 0.1 * cos(randangle*3.14/180), 0.0f,

            this->radius*sin(randangle*3.14/180) + 0.3* cos(randangle*3.14/180) + 0.1 * sin(randangle*3.14/180), this->radius*cos(randangle*3.14/180) - 0.3* sin(randangle*3.14/180) + 0.1 * cos(randangle*3.14/180), 0.0f,
        };
    // }
    this->object1 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
    if(pflag ==1 )
        this->object2 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data2, COLOR_RED, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= rotate*translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    if(pflag ==1)
        draw3DObject(this->object2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= this->speedx;
    if(this->position.y > this->origin || this->flag ==1)
    {
        this->speedy -= 0.01;
        this->position.y +=speedy;
        if(this->position.y <= this->origin)
            this->flag=0;
    }
    //this->position.y -= speedy;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
