//  contains method to compute bounding box and ndc coordinates, draw string and setting transformation matrices (manually enter entry, using glm to store it and multiplication)
//  utility.cpp
//  Project 2
//
//  Created by Ming Cheng on 10/25/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "utility.hpp"

using namespace std;

#define PI 3.14159265

//compute the xndc for line drawing using vertex2f
float getXNDC(float x)
{
    return ((((x - xmin) / delta) * 2) - 1);
}

//compute the yndc for line drawing using vertex2f
float getYNDC(float y)
{
    return ((((y - ymin) / delta) * 2) - 1);
}

//compute the zndc for line drawing using vertex2f
float getZNDC(float z)
{
    return ((((z - zmin) / delta) * 2) - 1);
}

//compute the ndc s for x in oblique projection
float getXoblique(float x)
{
    return ((((x - xobmin) / obdelta) * 2) - 1);
}

//compute the ndc for y in oblique projection
float getYoblique(float y)
{
    return ((((y - yobmin) / obdelta) * 2) - 1);
}

//compute the ndc for z in oblique projection
float getZoblique(float z)
{
    return ((((z - zobmin) / obdelta) * 2) - 1);
}

//used to update the bounding box
void computeBox()
{
    //initializes bounding box
    xmax = objects[0]->getMaxX();
    ymax = objects[0]->getMaxY();
    zmax = objects[0]->getMaxZ();
    xmin = objects[0]->getMinX();
    ymin = objects[0]->getMinY();
    zmin = objects[0]->getMinZ();

    for(unsigned int i = 1; i < objects.size(); i++)
    {
        //update
        if(objects[i]->getMaxX() > xmax)
            xmax = objects[i]->getMaxX();
        if(objects[i]->getMaxY() > ymax)
            ymax = objects[i]->getMaxY();
        if(objects[i]->getMaxZ() > zmax)
            zmax = objects[i]->getMaxZ();
        if(objects[i]->getMinX() < xmin)
            xmin = objects[i]->getMinX();
        if(objects[i]->getMinY() < ymin)
            ymin = objects[i]->getMinY();
        if(objects[i]->getMinZ() < zmin)
            zmin = objects[i]->getMinZ();
    }
    //add a little more space for the bounding box

    xmax = (float) (fabs(xmax) > 1) ? ((xmax > 0) ? (1.2 * xmax) : (0.8 * xmax)) : xmax + 0.2;
    ymax = (float) (fabs(ymax) > 1) ? ((ymax > 0) ? (1.2 * ymax) : (0.8 * ymax)) : ymax + 0.2;
    zmax = (float) (fabs(zmax) > 1) ? ((zmax > 0) ? (1.2 * zmax) : (0.8 * zmax)) : zmax + 0.2;
    xmin = (float) (fabs(xmin) > 1) ? ((xmin > 0) ? (0.8 * xmin) : (1.2 * xmin)) : xmin - 0.2;
    ymin = (float) (fabs(ymin) > 1) ? ((ymin > 0) ? (0.8 * ymin) : (1.2 * ymin)) : ymin - 0.2;
    zmin = (float) (fabs(zmin) > 1) ? ((zmin > 0) ? (0.8 * zmin) : (1.2 * zmin)) : zmin - 0.2;
    //find the delta, max of xmax, ymax and zmax
    delta = max(xmax - xmin, ymax - ymin);
    delta = max(delta, zmax - zmin);
}

//used to update the oblique projection bounding box
void computeObliqueBox()
{
    //initializes oblique bounding box
    xobmax = objects[0]->getObMaxX();
    yobmax = objects[0]->getObMaxY();
    zobmax = objects[0]->getObMaxZ();
    xobmin = objects[0]->getObMinX();
    yobmin = objects[0]->getObMinY();
    zobmin = objects[0]->getObMinZ();
    
    for(unsigned int i = 1; i < objects.size(); i++)
    {
        //update
        if(objects[i]->getObMaxX() > xobmax)
            xobmax = objects[i]->getObMaxX();
        if(objects[i]->getObMaxY() > yobmax)
            yobmax = objects[i]->getObMaxY();
        if(objects[i]->getObMaxZ() > zobmax)
            zobmax = objects[i]->getObMaxZ();
        if(objects[i]->getObMinX() < xobmin)
            xobmin = objects[i]->getObMinX();
        if(objects[i]->getObMinY() < yobmin)
            yobmin = objects[i]->getObMinY();
        if(objects[i]->getObMinZ() < zobmin)
            zobmin = objects[i]->getObMinZ();
    }
    //add a little more space for the bounding box
    
    xobmax = (float) (fabs(xobmax) > 1) ? (xobmax > 0) ? (1.1 * xobmax) : (0.9 * xobmax) : xobmax + 0.1;
    yobmax = (float) (fabs(yobmax) > 1) ? (yobmax > 0) ? (1.1 * yobmax) : (0.9 * yobmax) : yobmax + 0.1;
    zobmax = (float) (fabs(zobmax) > 1) ? (zobmax > 0) ? (1.1 * zobmax) : (0.9 * zobmax) : zobmax + 0.1;
    xobmin = (float) (fabs(xobmin) > 1) ? (xobmin > 0) ? (0.9 * xobmin) : (1.1 * xobmin) : xobmin - 0.1;
    yobmin = (float) (fabs(yobmin) > 1) ? (yobmin > 0) ? (0.9 * yobmin) : (1.1 * yobmin) : yobmin - 0.1;
    zobmin = (float) (fabs(zobmin) > 1) ? (zobmin > 0) ? (0.9 * zobmin) : (1.1 * zobmin) : zobmin - 0.1;
    //find the delta, max of xmax, ymax and zmax
    obdelta = max(xobmax - xobmin, yobmax - yobmin);
    obdelta = max(obdelta, zobmax - zobmin);

}

//draw the string at x, y
void drawstr(float x, float y, const char* format, size_t length)
{
    glRasterPos3f(x, y, 0);
    for(unsigned int i = 0; i < length; i++)
        glutBitmapCharacter(font_style, format[i]);
    glEnd();
}


//return the translation matrix
glm::mat4 translateMatrix(float dx, float dy, float dz)
{
    //get the translation matrix
    glm::mat4 translateM = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(dx, dy, dz, 1));
    return translateM;
}

//return the scaling matrix
glm::mat4 scaleMatrix(float factor, point centroid)
{
    float xc, yc, zc;
    xc = centroid.x;
    yc = centroid.y;
    zc = centroid.z;
    glm::mat4 M1 = translateMatrix(-xc, -yc, -zc); //matrix with translate(-xc, -yc, -zc)
    glm::mat4 M2 = glm::mat4(glm::vec4(factor, 0, 0, 0), glm::vec4(0, factor, 0, 0), glm::vec4(0, 0, factor, 0), glm::vec4(0, 0, 0, 1)); //matrix with scaling with center
    glm::mat4 M3 = translateMatrix(xc, yc, zc); //matrix with translate(xc, yc, zc)
    return M3 * M2 * M1;
}

//return the rotation matrix around x axis
glm::mat4 rotateXMatrix(float angle)
{
    float radian = angle * PI / 180.0;
    glm::mat4 rotateM = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, cos(radian), sin(radian), 0), glm::vec4(0, -sin(radian), cos(radian), 0), glm::vec4(0, 0, 0, 1));
    return rotateM;
}

//return the rotation matrix around y axis
glm::mat4 rotateYMatrix(float angle)
{
    float radian = angle * PI / 180.0;
    glm::mat4 rotateM = glm::mat4(glm::vec4(cos(radian), 0, -sin(radian), 0), glm::vec4(0, 1, 0, 0), glm::vec4(sin(radian), 0, cos(radian), 0), glm::vec4(0, 0, 0, 1));
    return rotateM;
}

//return the rotation matrix around z axis
glm::mat4 rotateZMatrix(float angle)
{
    float radian = angle * PI / 180.0;
    glm::mat4 rotateM = glm::mat4(glm::vec4(cos(radian), sin(radian), 0, 0), glm::vec4(-sin(radian), cos(radian), 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));
    return rotateM;
}

//return the oblique projection matrix on xy plane
glm::mat4 obliqueMatrix()
{
    float root2 = sqrt(2.0);
    glm::mat4 obliqueM = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(-1.0 * root2 / 2.0 , -1.0 * root2 / 2.0, 0, 0), glm::vec4(0, 0, 0, 1));
    return obliqueM;
}

