//
// Created by jakub on 01.03.2026.
//

#ifndef GLOBALLIGHT_H
#define GLOBALLIGHT_H
#include <glm/vec3.hpp>


class GlobalLight {
public:
    GlobalLight();
    glm::vec3 dir, color;

};



#endif //GLOBALLIGHT_H
