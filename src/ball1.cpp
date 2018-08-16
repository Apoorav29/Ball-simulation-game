#include "ball1.h"
#include "stdlib.h"
#include "main.h"
#include "bits/stdc++.h"
#include "time.h"

Ball1::Ball1(float x, float y, color_t color, float speed) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->mflag=0;
    this->score=0;
    // this->speedx = 0.04;
    this->radius = 0.25;
    // this->speedx = (rand()%3 + 4)*0.01;
    this->speedx = speed;
    this->backvar = speed;
    // this->speedy = 0.99;
    this->origin = y;
    this->porcflag=0;
    this->flag=0;
    this->wflag=0;
    GLfloat g_vertex_buffer_data[100000];  
    int i;
    // int randNum;
    // randNum = rand()%(3) + 4;
    float n=360,k=0;
    for(i=0;i<n*9;i+=9)
    {
        g_vertex_buffer_data[i]=(float)cos(k)/4;
        g_vertex_buffer_data[i+1]=(float)sin(k)/4;
        g_vertex_buffer_data[i+2]=0.0f;

        g_vertex_buffer_data[i+3]=(float)cos(k+1)/4;
        g_vertex_buffer_data[i+4]=(float)sin(k+1)/4;
        g_vertex_buffer_data[i+5]=0.0f;

        g_vertex_buffer_data[i+6]=0.0f;
        g_vertex_buffer_data[i+7]=0.0f;
        g_vertex_buffer_data[i+8]=0.0f;
        k++;
    }
    this->object = create3DObject(GL_TRIANGLES, 9*n, g_vertex_buffer_data, color, GL_FILL);
}

void Ball1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball1::tick() {
    if(this->position.y <= this->origin && (this->position.x<=-1 && this->position.x>=-3) && this->speedy<0)
    {
        this->wflag=0;
        this->speedy=0;
        this->speedx=0;
    }//
    if(this->position.y>=4-this->radius)
    {
        this->position.y = 4-this->radius;
        this->speedx=0;
    }
    if(this->position.x >=4-this->radius)
    {
        this->position.x=4-this->radius;
        this->speedx=0;
    }
    if(this->position.x <=-4+this->radius)
    {
        this->position.x=-4+this->radius;
        this->speedx=0;
    }

    if( this->position.y<=this->origin 
        && this->position.x< -1-this->radius && this->position.x>-3+this->radius)
    {
        if(wflag==0)
        {
        if(this->speedy>=-0.002)
        {
            if(this->position.y <= -3 + this->radius)
            {
                if(this->speedx>0)
                {
                    this->position.y+=0.002;
                    // this->position.x-=0.006;
                }
                else if (this->speedx<=0)
                {
                    this->position.y+=0.002;
                    // this->position.x+=0.006;
                }
            }
            if(this->position.x +2 <=0 && this->position.y>-3+this->radius)
            {
                if(this->speedx <=0)
                {
                    double rad = 1-this->radius;
                    double posy = -2-sqrt(pow(rad,2)-pow(this->position.x+2,2));    
                    if(this->position.y-posy<0.03 && this->position.y-posy>0)
                    {
                        this->position.y=posy;
                    }
                    else if(this->position.y-posy>=0.03 && this->position.y-posy>0)
                        this->position.y-=0.04;
                    else if(this->position.y<=posy)
                    {
                        this->position.y=posy;
                    }                
                    this->position.x+=0.005;
                }
                else if(this->speedx>0)
                {
                    this->position.y+=0.007;
                    double rad = 1-this->radius;
                    double posx = -2-sqrt(pow(rad,2)-pow(this->position.y+2,2));    
                    if(this->position.x>posx)
                    {
                        this->speedx=0.04;
                        this->position.x-=this->speedx;
                    }
                    else if(this->position.x<=posx)
                    {
                        this->position.x=posx;
                        this->speedy=0;this->speedx=0;    
                    }                
                }
            }
            else if(this->position.x +2 > 0 && this->position.y>-3+this->radius)
            {
                if(this->speedx>=0)
                {
                    this->position.x-=0.001;
                    double rad = 1-this->radius;
                    double posy = -2-sqrt(pow(rad,2)-pow(this->position.x+2,2));    
                    if(this->position.y-posy<0.03 && this->position.y-posy>0)
                    {
                        this->position.y=posy;
                    }
                    else if(this->position.y-posy>=0.03 && this->position.y-posy>0)
                        this->position.y-=0.04;
                    // if(this->position.y>posy)
                    // {
                    //     this->position.y=posy;
                    // }
                    else if(this->position.y<=posy)
                    {
                        this->position.y=posy;
                    }                
                }
                else if(this->speedx<0)
                {
                    this->position.y+=0.007;
                    double rad = 1-this->radius;
                    double posx = -2+sqrt(pow(rad,2)-pow(this->position.y+2,2));    
                    if(this->position.x<posx)
                    {
                        this->speedx=0.04;
                        this->position.x=posx;
                    }
                    else if(this->position.x>=posx)
                    {
                        this->position.x=posx;
                        this->speedy=0;
                        this->speedx=0;    
                    }                
                }
            }
        }
        if(fabs(this->position.y+2+this->radius)<0.06 && fabs(this->position.x+1+this->radius)<0.05 && this->speedx==0)
        {
            this->position.y=-2+this->radius;
            this->position.x=-1+this->radius-0.5;
        }
        if(fabs(this->position.y+2+this->radius)<0.06 && fabs(this->position.x+3-this->radius)<0.05 && this->speedx==0)
        {
            this->position.y=-2+this->radius;
            this->position.x=-3+this->radius;
        }
    }
    else 
    {
        if(this->position.y<=-3+this->radius)
            wflag=0;
        this->speedy=0.12;
        this->position.y+=this->speedy;
    }
    }    
    if(this->position.x>=2.5 && this->position.x<=3.5 && fabs(this->position.y+1)<0.1 && this->speedy<=0)
    {
        this->speedy=0.29;
        this->position.y +=speedy;
    }
    if(this->position.y <= this->origin && (this->position.x>= -1 || this->position.x<=-3))
    {
        this->speedx =0;
        this->position.x -= this->speedx;
    }
    // else 
    //     this->position.x -= this->speedx;
    if(this->position.y > this->origin || this->flag ==1 || this->wflag ==1)
    {
        if(fabs(this->speedy)<0.05)
            wflag=0;
        if(fabs(this->position.y-this->origin)<0.02 && this->position.y>this->origin)
            this->speedx=0;
        this->speedy -= 0.01;
        this->position.x-=this->speedx;
        this->position.y +=speedy;
        if(this->position.y <= this->origin)
        {
            this->flag=0;
            // this->speedy=0;
        }
        if(this->position.y <= this->origin && (this->position.x>=-1 || this->position.x<=-3))
        {
            this->wflag=0;
            this->speedy=0;
            this->position.y=this->origin;
        }
        if(this->position.y <= this->origin && (this->position.x<=-1 || this->position.x>=-3) && this->speedy<0)
        {
            this->wflag=0;
            this->speedy=0;
            this->speedx=0;
        }
    }
    // if(this->position.y <= this->origin)
    // {
    //     this->flag=0;
    //     this->speedy=0;
    // }
    if(((this->position.x<=-3 || this->position.x>=-1) || (fabs(this->position.y-this->origin)<0.02 
        && this->position.y >=this->origin && this->position.x<=-3 && this->position.x<=-1) )&& this->mflag==1)
    {
        this->position.x-=0.009;
    }

}

bounding_box_t Ball1::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
