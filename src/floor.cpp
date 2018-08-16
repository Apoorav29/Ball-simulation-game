#include "ball.h"
#include "main.h"
#include "time.h"
#include "floor.h"

Floor::Floor(color_t color) {
    static const GLfloat g_vertex_buffer_data[]={
        -4, -4, 0.0,
        -4, -2, 0.0,
        4, -2, 0.0, 

        -4, -4, 0.0,
        4, -4, 0.0,
        4, -2, 0.0, 

    };  
    // int i;
    // int randNum;
    // randNum = rand()%(3) + 4;
    // float n=360,k=0;
    // // for(i=0;i<n*9;i+=9)
    // {
    //     g_vertex_buffer_data[i]=(float)cos(k)/randNum;
    //     g_vertex_buffer_data[i+1]=(float)sin(k)/randNum;
    //     g_vertex_buffer_data[i+2]=0.0f;

    //     g_vertex_buffer_data[i+3]=(float)cos(k+1)/randNum;
    //     g_vertex_buffer_data[i+4]=(float)sin(k+1)/randNum;
    //     g_vertex_buffer_data[i+5]=0.0f;

    //     g_vertex_buffer_data[i+6]=0.0f;
    //     g_vertex_buffer_data[i+7]=0.0f;
    //     g_vertex_buffer_data[i+8]=0.0f;
    //     k++;
    // }
    this->object = create3DObject(GL_TRIANGLES, 6 , g_vertex_buffer_data, color, GL_FILL);
}

void Floor::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    // Matrices.model *= translate ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
