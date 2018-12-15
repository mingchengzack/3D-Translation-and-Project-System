//  point class to store 3D points and do transformation with points
//  point.cpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#include "utility.hpp"
#include "point.hpp"
#include <iostream>
#include <cmath>

using namespace std;

//constructor for a point
point::point(float x, float y, float z): x(x), y(y), z(z) {}

//perform transformation on the point
void point::transform(glm::mat4 transformMatrix)
{
    //create a vector of the point
    glm::vec4 P = vectorP();
    //calculate the translated vector
    P = transformMatrix * P;
    x = P[0];
    y = P[1];
    z = P[2];
}

//return the vector for 3D point using glm
glm::vec4 point::vectorP()
{
    glm::vec4 P = glm::vec4(x, y, z, 1);
    return P;
}

//return the vector in x z y order
glm::vec4 point::vectorP2()
{
    glm::vec4 P = glm::vec4(x, z, y, 1);
    return P;
}

//return the vector in y z x order
glm::vec4 point::vectorP3()
{
    glm::vec4 P = glm::vec4(y, z, x, 1);
    return P;
}

//return the oblique projection vector of the point
glm::vec4 point::obliqueVector()
{
    glm::vec4 p = vectorP();
    glm::mat4 obliqueM = obliqueMatrix();
    p = obliqueM * p;
    return p;
}

//return the oblique projection vector of the point
glm::vec4 point::obliqueVector2()
{
    glm::vec4 p = vectorP2();
    glm::mat4 obliqueM = obliqueMatrix();
    p = obliqueM * p;
    return p;
}

//return the oblique projection vector of the point
glm::vec4 point::obliqueVector3()
{
    glm::vec4 p = vectorP3();
    glm::mat4 obliqueM = obliqueMatrix();
    p = obliqueM * p;
    return p;
}

//return the string (x, y, z)
string point::tostring()
{
    string str;
    str = "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    return str;
}