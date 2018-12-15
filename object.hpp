//  object class to store objects' information and methods to projections
//  object.hpp
//  Project 2
//
//  Created by Ming Cheng on 10/24/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include <cstdio>
#include <vector>
#include <fstream>
#include "point.hpp"
#include "line.hpp"

using namespace std;

//the class to store the objects
class object
{
public:
    vector<point*> vertices; //use vector to store the vertices
    vector<line*> edges; //use vector to store edges
    int num_point; //number of points
    int num_edge; //number of edges
    
    object(); //default constructors;
    ~object(); //destructor
    
    float getMaxX(); //find the max x among vertices
    float getMaxY(); //find the max y among vertices
    float getMaxZ(); //find the max z among vertices
    float getMinX(); //find the min x among vertices
    float getMinY(); //find the min y among vertices
    float getMinZ(); //find the min z among vertices
    float getObMaxX(); //find the max oblique x among vertices
    float getObMaxY(); //find the max oblique y among vertices
    float getObMaxZ(); //find the max oblique z among vertices
    float getObMinX(); //find the min oblique x among vertices
    float getObMinY(); //find the min oblqiue y among vertices
    float getObMinZ(); //find the min oblique z among vertices
    void orthoXY(); //orthographic projection on xy plane
    void orthoXZ(); //orthographic projection on xz plane
    void orthoYZ(); //orthographic projection on yz plane
    void obliqueXY(); //oblique projection on xy plane
    void obliqueXZ(); //oblique projection on xz plane
    void obliqueYZ(); //oblique projection on yz plane
    void projectXY(int option); //projection on xy plane
    void projectXZ(int option); //projection on xz plane
    void projectYZ(int option); //projection on yz plane
    
    point getCentroid(); //find the centroid of the object
    
    void translate(float dx, float dy, float dz); //translate the object with dx dy dz
    void scale(float factor); //scale the object with dx dy dz with respect to centroid
    void rotate(float angle, point start, point end); //rotate the object around axis (defined by two points)
    
    friend istream& operator>>(istream& is, object& object); //operator for reading input file
    friend ostream& operator<<(ostream& os, const object& object); //opeartor for output file
};

#endif /* object_hpp */
