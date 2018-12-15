//  point class to store 3D points and do transformation with points
//  point.hpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <cstdio>
#include <string>
#include "glm/glm.hpp"

using namespace std;

//class for a 3D point
class point
{
public:
    float x;
    float y;
    float z;
    point(float x, float y, float z); //constructor
    void transform(glm::mat4 transformMatrix); //perform transformation with the point
    glm::vec4 vectorP(); //get the vector for 3D point in homogeneous coordinates using glm
    glm::vec4 vectorP2(); //get vector in x z y order
    glm::vec4 vectorP3(); //get vector in y z x order
    glm::vec4 obliqueVector(); //get the oblique vector of the point(x y z)
    glm::vec4 obliqueVector2(); //get the oblique vector of the point(x z y)
    glm::vec4 obliqueVector3(); //get the oblique vector of the point(y z x)
    
    string tostring(); //return the string constructed by the point
};

#endif /* point_hpp */
