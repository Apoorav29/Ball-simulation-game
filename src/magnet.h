#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object1;
    VAO *object2;
};

#endif // BALL_H
