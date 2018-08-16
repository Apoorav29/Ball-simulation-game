#include "ball.h"
#include "main.h"
#include "time.h"
#include "pond.h"

Pond::Pond(color_t color) {
    GLfloat g_vertex_buffer_data[10000];  
    this->position = glm::vec3(-2, -2, 0);
    this->rotation = 0;
    int i;
    float n=180,k=180;
    for(i=0;i<n*9;i+=9)
    {
        g_vertex_buffer_data[i]=(float)cos((k*3.14159)/180);
        g_vertex_buffer_data[i+1]=(float)sin((k*3.14159)/180);
        g_vertex_buffer_data[i+2]=0.0f;

        g_vertex_buffer_data[i+3]=(float)cos(((k+1)*3.14159)/180);
        g_vertex_buffer_data[i+4]=(float)sin(((k+1)*3.14159)/180);
        g_vertex_buffer_data[i+5]=0.0f;

        g_vertex_buffer_data[i+6]=0.0f;
        g_vertex_buffer_data[i+7]=0.0f;
        g_vertex_buffer_data[i+8]=0.0f;
        k++;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*n , g_vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= translate ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
