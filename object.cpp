//  object class to store objects' information and methods to projections
//  object.cpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "object.hpp"
#include "utility.hpp"
#include "glm/glm.hpp"

using namespace std;

//default constructor with size 0
object::object(): num_edge(0), num_point(0) {}

object::~object()
{
    //only need to delete point* since line store point*
    for(int i = num_point - 1; i >= 0; i--)
        delete vertices[i];
}

//find the max x
float object::getMaxX()
{
    float xmax = vertices[0]->x;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->x > xmax)
            xmax = vertices[i]->x;
    }
    return xmax;
}

//find the max y
float object::getMaxY()
{
    float ymax = vertices[0]->y;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->y > ymax)
            ymax = vertices[i]->y;
    }
    return ymax;
}

//find the max z
float object::getMaxZ()
{
    float zmax = vertices[0]->z;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->z > zmax)
            zmax = vertices[i]->z;
    }
    return zmax;
}

//find the min x
float object::getMinX()
{
    float xmin = vertices[0]->x;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->x < xmin)
            xmin = vertices[i]->x;
    }
    return xmin;
}

//find the min y
float object::getMinY()
{
    float ymin = vertices[0]->y;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->y < ymin)
            ymin = vertices[i]->y;
    }
    return ymin;
}

//find the min z
float object::getMinZ()
{
    float zmin = vertices[0]->z;
    for(int i = 1; i < num_point; i++)
    {
        if(vertices[i]->z < zmin)
            zmin = vertices[i]->z;
    }
    return zmin;
}

//find the max oblique x
float object::getObMaxX()
{
    float xobmax = vertices[0]->obliqueVector()[0];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[0] > xobmax)
            xobmax = vertices[i]->obliqueVector()[0];
        if(vertices[i]->obliqueVector2()[0] > xobmax)
            xobmax = vertices[i]->obliqueVector2()[0];
        if(vertices[i]->obliqueVector3()[2] > xobmax)
            xobmax = vertices[i]->obliqueVector3()[2];
    }
    return xobmax;
}

//find the max oblique y
float object::getObMaxY()
{
    float yobmax = vertices[0]->obliqueVector()[1];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[1] > yobmax)
            yobmax = vertices[i]->obliqueVector()[1];
        if(vertices[i]->obliqueVector2()[2] > yobmax)
            yobmax = vertices[i]->obliqueVector2()[2];
        if(vertices[i]->obliqueVector3()[0] > yobmax)
            yobmax = vertices[i]->obliqueVector3()[0];
    }
    return yobmax;
}

//find the max oblique z
float object::getObMaxZ()
{
    float zobmax = vertices[0]->obliqueVector2()[1];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[2] > zobmax)
            zobmax = vertices[i]->obliqueVector()[2];
        if(vertices[i]->obliqueVector2()[1] > zobmax)
            zobmax = vertices[i]->obliqueVector2()[1];
        if(vertices[i]->obliqueVector3()[1] > zobmax)
            zobmax = vertices[i]->obliqueVector3()[1];
    }
    return zobmax;
}

//find the min olbique x
float object::getObMinX()
{
    float xobmin = vertices[0]->obliqueVector()[0];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[0] < xobmin)
            xobmin = vertices[i]->obliqueVector()[0];
        if(vertices[i]->obliqueVector2()[0] < xobmin)
            xobmin = vertices[i]->obliqueVector2()[0];
        if(vertices[i]->obliqueVector3()[2] < xobmin)
            xobmin = vertices[i]->obliqueVector3()[2];
    }
    return xobmin;
}

//find the min oblique y
float object::getObMinY()
{
    float yobmin = vertices[0]->obliqueVector()[1];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[1] < yobmin)
            yobmin = vertices[i]->obliqueVector()[1];
        if(vertices[i]->obliqueVector2()[2] < yobmin)
            yobmin = vertices[i]->obliqueVector2()[2];
        if(vertices[i]->obliqueVector3()[0] < yobmin)
            yobmin = vertices[i]->obliqueVector3()[0];
    }
    return yobmin;
}

//find the min oblique z
float object::getObMinZ()
{
    float zobmin = vertices[0]->obliqueVector2()[1];
    for(int i = 0; i < num_point; i++)
    {
        if(vertices[i]->obliqueVector()[2] < zobmin)
            zobmin = vertices[i]->obliqueVector()[2];
        if(vertices[i]->obliqueVector3()[1] < zobmin)
            zobmin = vertices[i]->obliqueVector3()[1];
        if(vertices[i]->obliqueVector2()[1] < zobmin)
            zobmin = vertices[i]->obliqueVector2()[1];
    }
    return zobmin;
}

//orthographic projection
//project in xy plane
void object::orthoXY()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->orthoXY();
}

//project in xz plane
void object::orthoXZ()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->orthoXZ();
}

//project in yz plane
void object::orthoYZ()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->orthoYZ();

}

//oblique projection on xy plane
void object::obliqueXY()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->obliqueXY();
}

//oblique projection on xz plane
void object::obliqueXZ()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->obliqueXZ();
}
//oblique projection on yz plane
void object::obliqueYZ()
{
    for(int i = 0; i < num_edge; i++)
        edges[i]->obliqueYZ();
}

//projection on xy plane
void object::projectXY(int option)
{
    if(option == 1)
        orthoXY();
    else
        obliqueXY();
}

//projection on xz plane
void object::projectXZ(int option)
{
    if(option == 1)
        orthoXZ();
    else
        obliqueXZ();
}

//projection on yz plane
void object::projectYZ(int option)
{
    if(option == 1)
        orthoYZ();
    else
        obliqueYZ();
}

//find the centroid of the object
point object::getCentroid()
{
    float xmean = 0, ymean = 0, zmean = 0;
    
    for(int i = 0; i < num_point; i++)
    {
        xmean = xmean + vertices[i]->x;
        ymean = ymean + vertices[i]->y;
        zmean = zmean + vertices[i]->z;
    }
    
    xmean = xmean / (num_point * 1.0);
    ymean = ymean / (num_point * 1.0);
    zmean = zmean / (num_point * 1.0);
    
    point centroid(xmean, ymean, zmean);
    return centroid;
}

//translate the object with dx dy dz
void object::translate(float dx, float dy, float dz)
{
    glm::mat4 translateM = translateMatrix(dx, dy, dz);
    for(int i = 0; i < num_point; i++)
        vertices[i]->transform(translateM);
}

//scale the object with respect to centroid
void object::scale(float factor)
{
    point centroid = getCentroid();
    glm::mat4 scaleM = scaleMatrix(factor, centroid);
    for(int i = 0; i < num_point; i++)
        vertices[i]->transform(scaleM);
}

//rotate the object with angle around axis formed by start and end
void object::rotate(float angle, point start, point end)
{
    float dx, dy, dz, delta, l;
    delta = sqrt(pow((end.x - start.x), 2) + pow((end.y - start.y), 2) + pow((end.z - start.z), 2));
    dx = (end.x - start.x) / delta;
    dy = (end.y - start.y) / delta;
    dz = (end.z - start.z) / delta;
    l = sqrt(pow(dy, 2) + pow(dz, 2));
    //initializes to 0
    glm::mat4 rotateM = glm::mat4(0);
    
    if(l != 0)
    {
        glm::mat4 M1 = translateMatrix(-1.0 * start.x, -1.0 * start.y, -1.0 * start.z); //translate to origin
        glm::mat4 M21 = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, dz/l, dy/l, 0), glm::vec4(0, -1.0 * dy/l, dz/l, 0), glm::vec4(0, 0, 0, 1)); //rotate to xz plane
        glm::mat4 M22 = glm::mat4(glm::vec4(l, 0, dx, 0), glm::vec4(0, 1, 0, 0), glm::vec4(-1.0 * dx, 0, l, 0), glm::vec4(0, 0, 0, 1)); // rotate to z axis
        glm::mat4 M2 = M22 * M21;
        glm::mat4 M3 = rotateZMatrix(angle); // rotate around z axis
        glm::mat4 M4 = inverse(M2); //inverse of M2
        glm::mat4 M5 = translateMatrix(start.x, start.y, start.z); //translate back
        rotateM = M5 * M4 * M3 * M2 * M1;
    }
    
    //it is an axis parallel to the x axis
    else
    {
        glm::mat4 M1 = translateMatrix(-1.0 * start.x, -1.0 * start.y, -1.0 * start.z); //translate to origin
        glm::mat4 M2 = rotateXMatrix(angle); //rotate around x axis
        glm::mat4 M3 = translateMatrix(start.x, start.y, start.z); //translate back
        rotateM = M3 * M2 * M1;
    }
    
    for(int i = 0; i < num_point; i++)
        vertices[i]->transform(rotateM);
}

//overloaded operator for input the object from file
istream& operator>>(istream& is, object& object)
{
    int numOfPoints, numOfEdges;
    float x, y, z;
    int e1, e2;
    
    is >> numOfPoints;
    object.num_point = numOfPoints;
    
    //read points and store them
    for(int i = 0; i < numOfPoints; i++)
    {
        is >> x >> y >> z;
        
        point* p = new point(x, y, z);
        //add it to the vector vertice
        object.vertices.push_back(p);
    }
    
    is >> numOfEdges;
    object.num_edge = numOfEdges;
    //read the edges and store them
    for(int i = 0; i < numOfEdges; i++)
    {
        is >> e1 >> e2;
        //create a edge
        line* edge = new line(object.vertices[e1 - 1], object.vertices[e2 - 1], e1, e2);
        //add it to the vector edges
        object.edges.push_back(edge);
    }
    return is;
}

//overloaded operator for output the object onto file
ostream& operator<<(ostream& os, const object& object)
{
    //write the number of points
    os << object.num_point << endl;
    
    //write each point in x y z
    for(int i = 0; i < object.num_point; i++)
        os << object.vertices[i]->x << ' ' << object.vertices[i]->y << ' ' << object.vertices[i]->z << endl;
    
    //write edge components
    os << object.num_edge << endl;
    for(int i = 0; i < object.num_edge; i++)
        os << object.edges[i]->e1 <<  ' ' << object.edges[i]->e2 << endl;
  
    return os;
}
