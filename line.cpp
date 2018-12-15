//  line class to store a 3D line and method to draw projected line
//  line.cpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "line.hpp"
#include "utility.hpp"

using namespace std;

//constructor for a line
line::line(point* s, point* e, int e1, int e2): e1(e1), e2(e2)
{
    start = s;
    end = e;
}

//destructor
line::~line()
{
   delete start;
   delete end;
}

//draw a line using xy coordinates
void line::orthoXY()
{
    float x1, y1, x2, y2;
    
    //convert to ndc coordinates
    x1 = getXNDC(start->x);
    y1 = getYNDC(start->y);
    x2 = getXNDC(end->x);
    y2 = getYNDC(end->y);
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

//draw a line using xz coordinates
void line::orthoXZ()
{
    float x1, z1, x2, z2;
    
    //convert to ndc coordinates
    x1 = getXNDC(start->x);
    z1 = getZNDC(start->z);
    x2 = getXNDC(end->x);
    z2 = getZNDC(end->z);
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex2f(x1, z1);
    glVertex2f(x2, z2);
    glEnd();
    
}

//draw a line uisng yz coordinates
void line::orthoYZ()
{
    float y1, z1, y2, z2;
    
    //convert to ndc coordinates
    y1 = getYNDC(start->y);
    z1 = getZNDC(start->z);
    y2 = getYNDC(end->y);
    z2 = getZNDC(end->z);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(y1, z1);
    glVertex2f(y2, z2);
    glEnd();
}

//oblique project on xy plane
void line::obliqueXY()
{
    float x1, y1, x2, y2;
    glm::vec4 p1 = start->vectorP();
    glm::vec4 p2 = end->vectorP();
    glm::mat4 obliqueM = obliqueMatrix();
    p1 = obliqueM * p1;
    p2 = obliqueM * p2;
    x1 = p1[0];
    y1 = p1[1];
    x2 = p2[0];
    y2 = p2[1];

    //conver to ndc coordinates
    x1 = getXoblique(x1);
    x2 = getXoblique(x2);
    y1 = getYoblique(y1);
    y2 = getYoblique(y2);

    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    
}

//oblique project on xz plane
void line::obliqueXZ()
{
    float x1, z1, x2, z2;
    glm::vec4 p1 = start->vectorP2();
    glm::vec4 p2 = end->vectorP2();
    glm::mat4 obliqueM = obliqueMatrix();
    p1 = obliqueM * p1;
    p2 = obliqueM * p2;
    x1 = p1[0];
    z1 = p1[1];
    x2 = p2[0];
    z2 = p2[1];
    
    //conver to ndc coordinates
    x1 = getXoblique(x1);
    x2 = getXoblique(x2);
    z1 = getZoblique(z1);
    z2 = getZoblique(z2);
    
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex2f(x1, z1);
    glVertex2f(x2, z2);
    glEnd();
    
}

//oblique project on xz plane
void line::obliqueYZ()
{
    float y1, z1, y2, z2;
    glm::vec4 p1 = start->vectorP3();
    glm::vec4 p2 = end->vectorP3();
    glm::mat4 obliqueM = obliqueMatrix();
    p1 = obliqueM * p1;
    p2 = obliqueM * p2;
    y1 = p1[0];
    z1 = p1[1];
    y2 = p2[0];
    z2 = p2[1];
    
    //conver to ndc coordinates
    y1 = getYoblique(y1);
    y2 = getYoblique(y2);
    z1 = getZoblique(z1);
    z2 = getZoblique(z2);
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(y1, z1);
    glVertex2f(y2, z2);
    glEnd();
}

