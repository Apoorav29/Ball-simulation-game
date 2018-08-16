#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, float speed, int pflag);
    glm::vec3 position;
    float rotation;
    float radius;
    float angle;
    int pflag;
    int cnum;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    int flag;
    double speedy;
    float origin;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};

#endif // BALL_H
