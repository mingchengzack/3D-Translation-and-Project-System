//  contains method to compute bounding box and ndc coordinates, draw string and setting transformation matrices (manually enter entry, using glm to store it and multiplication)
//  utility.hpp
//  Project 2
//
//  Created by Ming Cheng on 10/25/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#include <cstdio>
#include <vector>
#include "object.hpp"
#include "point.hpp"
#include <GL/glut.h>

extern vector<object*> objects; //make it global to compute the bounding box
extern float xmax, ymax, zmax, xmin, ymin, zmin, delta; //bounding box
extern float xobmax, yobmax, zobmax, xobmin, yobmin, zobmin, obdelta; //oblique bounding box
extern GLvoid *font_style; //font style

float getXNDC(float x); //get the x ndc for ortho projection
float getYNDC(float y); //get the y ndc for ortho projection
float getZNDC(float z); //get the z ndc for ortho project
float getXoblique(float x); //get the x ndc for oblique projection
float getYoblique(float y); //get the y ndc for oblique projection
float getZoblique(float z); //ge the z ndc for oblique proejction

void drawstr(float x, float y, const char* format, size_t length);
void computeBox(); //compute the bounding box
void computeObliqueBox(); //compute the oblique bounding box
glm::mat4 translateMatrix(float dx, float dy, float dz); //return the translation matrix
glm::mat4 scaleMatrix(float factor, point centroid); //return the scaling matrix with respect to centroid
glm::mat4 rotateXMatrix(float angle); //return the rotation matrix around x axis;
glm::mat4 rotateYMatrix(float angle); //return the rotation matrix around y axis;
glm::mat4 rotateZMatrix(float angle); //return the rotation matrix around z axis;
glm::mat4 obliqueMatrix(); //return the oblique matrix with 45 degrees on xy plane

#endif /* utility_hpp */
