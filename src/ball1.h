#include "main.h"

#ifndef BALL1_H
#define BALL1_H


class Ball1 {
public:
    Ball1() {}
    Ball1(float x, float y, color_t color, float speed);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double backvar;
    float radius;
    int porcflag;
    int score;
    int mflag;
    int flag;
    int wflag;
    double speedy;
    float origin;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
