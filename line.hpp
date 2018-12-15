//  line class to store a 3D line and method to draw projected line
//  line.hpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#ifndef line_hpp
#define line_hpp

#include <cstdio>
#include "point.hpp"

using namespace std;

//class of line with start point and end point
class line
{
public:
    point* start;
    point* end;
    
    //used for outputing files
    int e1; //label the starting point used for the edge
    int e2;  //label the end point
    
    line(point* s, point* e, int e1, int e2); //constructor
    ~line();  //destructor
    void orthoXY(); //ortho project the x y line
    void orthoXZ(); //ortho project the x z line
    void orthoYZ(); //ortho project the y z line
    void obliqueXY(); //oblique projection on xy plane
    void obliqueXZ(); //oblique projection on xz plane
    void obliqueYZ(); //oblique projection on xz plane
};

#endif /* line_hpp */
