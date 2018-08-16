#include "ball.h"
#include "main.h"
#include "time.h"
#include "magnet.h"

Magnet::Magnet(color_t color) {
    GLfloat g_vertex_buffer_data1[10000];  
    GLfloat g_vertex_buffer_data2[10000];
    this->position = glm::vec3(-2, 3, 0);
    this->rotation = 0;
    int i;
    float n=180,k=90;
    for(i=0;i<n*9;i+=9)
    {
        g_vertex_buffer_data1[i]=(float)cos((k*3.14159)/180)/2;
        g_vertex_buffer_data1[i+1]=(float)sin((k*3.14159)/180)/2;
        g_vertex_buffer_data1[i+2]=0.0f;

        g_vertex_buffer_data1[i+3]=(float)cos(((k+1)*3.14159)/180)/2;
        g_vertex_buffer_data1[i+4]=(float)sin(((k+1)*3.14159)/180)/2;
        g_vertex_buffer_data1[i+5]=0.0f;

        g_vertex_buffer_data1[i+6]=0.0f;
        g_vertex_buffer_data1[i+7]=0.0f;
        g_vertex_buffer_data1[i+8]=0.0f;
        k++;
    }
    k=90;
    for(i=0;i<n*9;i+=9)
    {
        g_vertex_buffer_data2[i]=(float)cos((k*3.14159)/180)/3;
        g_vertex_buffer_data2[i+1]=(float)sin((k*3.14159)/180)/3;
        g_vertex_buffer_data2[i+2]=0.0f;

        g_vertex_buffer_data2[i+3]=(float)cos(((k+1)*3.14159)/180)/3;
        g_vertex_buffer_data2[i+4]=(float)sin(((k+1)*3.14159)/180)/3;
        g_vertex_buffer_data2[i+5]=0.0f;

        g_vertex_buffer_data2[i+6]=0.0f;
        g_vertex_buffer_data2[i+7]=0.0f;
        g_vertex_buffer_data2[i+8]=0.0f;
        k++;
    }
    this->object1 = create3DObject(GL_TRIANGLES, 3*n , g_vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n , g_vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= translate ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);

}
