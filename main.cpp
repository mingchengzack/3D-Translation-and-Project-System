//  main program
//  main.cpp
//  Project 2
//
//  Created by Ming Cheng on 10/6/18.
//  Copyright © 2018 Ming Cheng. All rights reserved.
//

#include <GL/glut.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "object.hpp"
#include "utility.hpp"
#include "glm/glm.hpp"

using namespace std;

//status for the program menu
#define MENU 0
#define OBJECT 1
#define TRANSLATION 2
#define TWAIT 3
#define TSET 4
#define SCALE 5
#define SWAIT 6
#define SSET 7
#define ROTATION 8
#define RWAIT 9
#define RSET 10

bool axis = false;
int which = 0;
int status = 0;
float xaxis1, yaxis1, zaxis1, xaxis2, yaxis2, zaxis2, angle, xvector, yvector, zvector, factor;
static int MainWindow; //the main window
int option = 1;; //option between two projections
string filename;
int numOfObjects;
vector<object*> objects; //make it global to compute the bounding box
float xmax, ymax, zmax, xmin, ymin, zmin, delta; //bounding box
float xobmax, yobmax, zobmax, xobmin, yobmin, zobmin, obdelta; //bounding box for oblique projection
GLvoid *font_style = GLUT_BITMAP_HELVETICA_12; //font style

//the keyboard function
void KeyBoardFunc(unsigned char key, int x, int y);

//show the main menu
void showMenu();

//show the object information
void showObject();

//show translation menu
void showTranslation();

//show scaling menu
void showScale();

//show rotation menu
void showRotation();

//when the axis is parellel to the object it needs to update the bounding box
void updateBox();

//draw axis on xy plane
void drawaxisXY();

//draw axis on xz plane
void drawaxisXZ();

//draw axis on xy plane
void drawaxisYZ();

void display();

float getInput();

//get the float input and check if the input is valid
float getInput()
{
    float input;
    //if input is not a float
    while(!(cin >> input))
    {
        cout << "format is wrong" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter again: ";
    }
    return input;
}

void KeyBoardFunc(unsigned char key, int x, int y)
{
    switch(key)
    {
        //press q to go back
        case 'q':
        {
            //going back different transformation
            if(status == ROTATION || status == TRANSLATION || status == SCALE)
                status = OBJECT;
            
            //going back for another object
            else if(status == OBJECT)
                status = MENU;
            
            //setting new parameter for translation
            else if(status == TSET)
                status = TRANSLATION;
            
            //setting new parameter for scale
            else if(status == SSET)
                status = SCALE;
            
            //setting new parameter for rotation
            else if(status == RSET)
            {
                axis = false;
                status = ROTATION;
            }
            glutPostRedisplay();
            break;
        }
            
        //press r to rotate 1 degree
        case 'r':
        {
            //in object menu and choose r to enter rotation menu
            if(status == OBJECT)
                status = ROTATION;

            //in rotation menu
            else if(status == ROTATION)
            {
                //waiting for user to enter input
                status = RWAIT;
                cout << "Please enter the starting point for the axis (x y z) : ";
                //get input
                while(!(cin >> xaxis1 >> yaxis1 >> zaxis1))
                {
                    cout << "format is wrong" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter again (x y z): ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Please enter the end point for the axis (x y z) : ";
                while(!(cin >> xaxis2 >> yaxis2 >> zaxis2))
                {
                    cout << "format is wrong" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter again (x y z): ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Please enter the angle: ";
                angle = getInput();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                point p1(xaxis1, yaxis1, zaxis1);
                point p2(xaxis2, yaxis2, zaxis2);
                axis = true;
                //rotating
                objects[which - 1]->rotate(angle, p1, p2);
                
                //the first rotation is set
                status = RSET;
            }
            //continue to rotate using the same axis
            else if(status == RSET)
            {
                point p1(xaxis1, yaxis1, zaxis1);
                point p2(xaxis2, yaxis2, zaxis2);
                objects[which - 1]->rotate(1, p1, p2);
                angle++;
                if(angle >= 360)
                    angle = 0;
            }
            
            glutPostRedisplay();
            break;
        }
        
        //press t to translate
        case 't':
        {
            //in object menu and choose t to enter translation menu
            if(status == OBJECT)
                status = TRANSLATION;
            
            //in rotation menu
            else if(status == TRANSLATION)
            {
                //waiting for user to enter input
                status = TWAIT;
                cout << "Please enter the translation vector (x y z) in world coordinates: ";
                while(!(cin >> xvector >> yvector >> zvector))
                {
                    cout << "format is wrong" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter again (x y z): ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                objects[which - 1]->translate(xvector, yvector, zvector);
                //the first translation is set
                status = TSET;
            }
            //continue to rotate using the same axis
            else if(status == TSET)
                objects[which - 1]->translate(xvector, yvector, zvector);
            
            glutPostRedisplay();
            break;

        }
            
        //press s to scale
        case 's':
        {
            //in object menu and choose t to enter translation menu
            if(status == OBJECT)
                status = SCALE;
            
            //in rotation menu
            else if(status == SCALE)
            {
                //waiting for user to enter input
                status = SWAIT;
                cout << "Please enter the scaling factor: ";
                factor = getInput();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                objects[which - 1]->scale(factor);
                //the first translation is set
                status = SSET;
            }
            //continue to rotate using the same axis
            else if(status == SSET)
                objects[which - 1]->scale(factor);
            
            glutPostRedisplay();
            break;
        }
           
        //set mode to orthographic
        case '1':
        {
            option = 1;
            glutPostRedisplay();
            break;
        }
            
        //set mode to oblique
        case '2':
        {
            option = 2;
            glutPostRedisplay();
            break;
        }
            
        //select A to show information
        case 'a':
        {
            if(status == MENU)
            {
                status = OBJECT;
                which = 1;
                glutPostRedisplay();
            }
            break;
        }
           
        //select B to show information
        case 'b':
        {
            if(status == MENU)
            {
                status = OBJECT;
                which = 2;
                glutPostRedisplay();
            }
            break;
        }

        //select B to show information
        case 'c':
        {
            if(status == MENU)
            {
                status = OBJECT;
                which = 3;
                glutPostRedisplay();
            }
            break;
        }
            
        //escape key to exit
        case 27:
        {
            glutDestroyWindow(MainWindow);
            
            //output file
            ofstream outf;
            outf.open(filename, ios::out);
            
            outf << numOfObjects << endl;
            outf << '\n';
            
            for(unsigned int i = 0; i < objects.size(); i++)
                outf << *objects[i];
            
            outf.close();
            exit(0);
        }
    }
}

void updateBox()
{
    //update bouding box
    if(xaxis1 >= xmax)
        xmax = (float) (xaxis1 + 0.2);
    if(xaxis2 >= xmax)
        xmax = (float) (xaxis2 + 0.2);
    if(xaxis1 <= xmin)
        xmin = (float) (xaxis1 - 0.2);
    if(xaxis2 <= xmin)
        xmin = (float) (xaxis2 - 0.2);
    if(yaxis1 >= ymax)
        ymax = (float) (yaxis1 + 0.2);
    if(yaxis2 >= ymax)
        ymax = (float) (yaxis2 + 0.2);
    if(yaxis1 <= ymin)
        ymin = (float) (yaxis1 - 0.2);
    if(yaxis2 <= ymin)
        ymin = (float) (yaxis2 - 0.2);
    if(zaxis1 >= zmax)
        zmax = (float) (zaxis1 + 0.2);
    if(zaxis2 >= zmax)
        zmax = (float) (zaxis2 + 0.2);
    if(zaxis1 <= zmin)
        zmin = (float) (zaxis1 - 0.2);
    if(zaxis2 <= zmin)
        zmin = (float) (zaxis2 - 0.2);
    delta = max(xmax - xmin, ymax - ymin);
    delta = max(delta, zmax - zmin);

    
    if(xaxis1 >= xobmax)
        xobmax = (float) (xaxis1 + 0.2);
    if(xaxis2 >= xobmax)
        xobmax = (float) (xaxis2 + 0.2);
    if(xaxis1 <= xobmin)
        xobmin = (float) (xaxis1 - 0.2);
    if(xaxis2 <= xobmin)
        xobmin = (float) (xaxis2 - 0.2);
    if(yaxis1 >= yobmax)
        yobmax = (float) (yaxis1 + 0.2);
    if(yaxis2 >= yobmax)
        yobmax = (float) (yaxis2 + 0.2);
    if(yaxis1 <= yobmin)
        yobmin = (float) (yaxis1 - 0.2);
    if(yaxis2 <= yobmin)
        yobmin = (float) (yaxis2 - 0.2);
    if(zaxis1 >= zobmax)
        zobmax = (float) (zaxis1 + 0.2);
    if(zaxis2 >= zobmax)
        zobmax = (float) (zaxis2 + 0.2);
    if(zaxis1 <= zobmin)
        zobmin = (float) (zaxis1 - 0.2);
    if(zaxis2 <= zobmin)
        zobmin = (float) (zaxis2 - 0.2); 
    obdelta = max(xobmax - xobmin, yobmax - yobmin);
    obdelta = max(obdelta, zobmax - zobmin);

}

//draw axis on xy plane
void drawaxisXY()
{
    if(axis)
    {
        float xndc1, xndc2, yndc1, yndc2;
        if(option == 1)
        {
            xndc1 = xaxis1, xndc2 = xaxis2;
            yndc1 = yaxis1, yndc2 = yaxis2;
        }
        else
        {
            //draw the axis in oblique projection
            point p1(xaxis1, yaxis1, zaxis1), p2(xaxis2, yaxis2, zaxis2);
            glm::vec4 vector1 = p1.obliqueVector(), vector2 = p2.obliqueVector();
            //get x z in oblique projection
            //normalize using oblique bounding box
            xndc1 = vector1[0], xndc2 = vector2[0];
            yndc1 = vector1[1], yndc2 = vector2[1];
        }
        
        //draw the axis
        if(xndc2 - xndc1 != 0)
        {
            //find slope
            float slope = (yndc2 - yndc1 ) / (xndc2 - xndc1);
            //find b in y = kx + b
            float b = yndc2 - slope * xndc2;
            //calculate boundry y values
            float y1 = xmin * slope + b;
            float y2 = xmax * slope + b;
            if(y1 > ymax || y1 < ymin || y2 > ymax || y2 < ymin)
            {
                float x1 = (ymin - b) / slope;
                float x2 = (ymax - b) / slope;
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    x1 = getXNDC(x1), x2 = getXNDC(x2);
                }
                else
                {
                    x1 = getXoblique(x1), x2 = getXoblique(x1);
                }
                glBegin(GL_LINES);
                glColor3f(0, 0, 1);
                glVertex2f(x1, -1);
                glVertex2f(x2, 1);
                glEnd();
            }
            else
            {
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    y1 = getYNDC(y1), y2 = getYNDC(y2);
                }
                else
                {
                    y1 = getYoblique(y1), y2 = getYoblique(y1);
                }
                glBegin(GL_LINES);
                glColor3f(0, 0, 1);
                glVertex2f(-1, y1);
                glVertex2f(1, y2);
                glEnd();
            }
        }
        else if(xndc2 - xndc1 == 0 && yndc2 - yndc1 != 0)
        {
            if(option == 1)
            {
                //draw the axis in orthographic projection
                //normalize x
                xndc1 = getXNDC(xndc1), xndc2 = getXNDC(xndc2);
            }
            else
            {
                xndc1 = getXoblique(xndc1), xndc2 = getXoblique(xndc2);
            }
            //it is a vertical axis
            glBegin(GL_LINES);
            glColor3f(0, 0, 1);
            glVertex2f(xndc1, -1);
            glVertex2f(xndc2, 1);
            glEnd();
        }
    }
}

//draw axis on xz plane
void drawaxisXZ()
{
    //draw axis for xz plane
    if(axis)
    {
        float xndc1, xndc2, zndc1, zndc2;
        if(option == 1)
        {
            xndc1 = xaxis1, xndc2 = xaxis2;
            zndc1 = zaxis1, zndc2 = zaxis2;
        }
        else
        {
            //draw the axis in oblique projection
            point p1(xaxis1, yaxis1, zaxis1), p2(xaxis2, yaxis2, zaxis2);
            glm::vec4 vector1 = p1.obliqueVector2(), vector2 = p2.obliqueVector2();
            //get x z in oblique projection
            //normalize using oblique bounding box
            xndc1 = vector1[0], xndc2 = vector2[0];
            zndc1 = vector1[1], zndc2 = vector2[1];
        }
        
        if(xndc2 - xndc1 != 0)
        {
            //find slope
            float slope = (zndc2 - zndc1 ) / (xndc2 - xndc1);
            //find b in y = kx + b
            float b = zndc2 - slope * xndc2;
            //calculate boundry y values
            float z1 = xmin * slope + b;
            float z2 = xmax * slope + b;
            if(z1 > zmax || z1 < zmin || z2 > zmax || z2 < zmin)
            {
                float x1 = (zmin - b) / slope;
                float x2 = (zmax - b) / slope;
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    x1 = getXNDC(x1), x2 = getXNDC(x2);
                }
                else
                {
                    x1 = getXoblique(x1), x2 = getXoblique(x1);
                }
                //draw the axis
                glBegin(GL_LINES);
                glColor3f(0, 1, 0);
                glVertex2f(x1, -1);
                glVertex2f(x2, 1);
                glEnd();
            }
            else
            {
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    z1 = getZNDC(z1), z2 = getZNDC(z2);
                }
                else
                {
                    z1 = getZoblique(z1), z2 = getZoblique(z1);
                }
                //draw the axis
                glBegin(GL_LINES);
                glColor3f(0, 1, 0);
                glVertex2f(-1, z1);
                glVertex2f(1, z2);
                glEnd();
            }
        }
        else if(xndc2 - xndc1 == 0 && zndc2 - zndc1 != 0)
        {
            if(option == 1)
            {
                //draw the axis in orthographic projection
                //normalize x
                xndc1 = getXNDC(xndc1), xndc2 = getXNDC(xndc2);
            }
            else
            {
                xndc1 = getXoblique(xndc1), xndc2 = getXoblique(xndc2);
            }
            //it is a vertical axis
            //draw the axis
            glBegin(GL_LINES);
            glColor3f(0, 1, 0);
            glVertex2f(xndc1, -1);
            glVertex2f(xndc2, 1);
            glEnd();
        }
    }
}

//draw axis on yz plane
void drawaxisYZ()
{
    //draw axis for yz plane
    if(axis)
    {
        //parallel and vertical line, check if it is outside the box
        float yndc1, yndc2, zndc1, zndc2;
        if(option == 1)
        {
            yndc1 = yaxis1, yndc2 = yaxis2;
            zndc1 = zaxis1, zndc2 = zaxis2;
        }
        else
        {
            //draw the axis in oblique projection
            point p1(xaxis1, yaxis1, zaxis1), p2(xaxis2, yaxis2, zaxis2);
            glm::vec4 vector1 = p1.obliqueVector3(), vector2 = p2.obliqueVector3();
            //get x z in oblique projection
            //normalize using oblique bounding box
            yndc1 = vector1[0], yndc2 = vector2[0];
            zndc1 = vector1[1], zndc2 = vector2[1];
        }
        
        if(yndc2 - yndc1 != 0)
        {
            //find slope
            float slope = (zndc2 - zndc1 ) / (yndc2 - yndc1);
            //find b in y = kx + b
            float b = zndc2 - slope * yndc2;
            //calculate boundry y values
            float z1 = ymin * slope + b;
            float z2 = ymax * slope + b;
            if(z1 > zmax || z1 < zmin || z2 > zmax || z2 < zmin)
            {
                float y1 = (zmin - b) / slope;
                float y2 = (zmax - b) / slope;
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    y1 = getYNDC(y1), y2 = getYNDC(y2);
                }
                else
                {
                    y1 = getYoblique(y1), y2 = getYoblique(y1);
                }
                //draw the axis
                glBegin(GL_LINES);
                glColor3f(1, 0, 0);
                glVertex2f(y1, -1);
                glVertex2f(y2, 1);
                glEnd();
            }
            else
            {
                if(option == 1)
                {
                    //draw the axis in orthographic projection
                    //normalize x
                    z1 = getZNDC(z1), z2 = getZNDC(z2);
                }
                else
                {
                    z1 = getZoblique(z1), z2 = getZoblique(z1);
                }
                //draw the axis
                glBegin(GL_LINES);
                glColor3f(1, 0, 0);
                glVertex2f(-1, z1);
                glVertex2f(1, z2);
                glEnd();
            }
        }
        else if(yndc2 - yndc1 == 0 && zndc2 - zndc1 != 0)
        {
            if(option == 1)
            {
                //draw the axis in orthographic projection
                //normalize x
                yndc1 = getYNDC(yndc1), yndc2 = getYNDC(yndc2);
            }
            else
            {
                yndc1 = getYoblique(yndc1), yndc2 = getYoblique(yndc2);
            }
            //it is a vertical axis
            //draw the axis
            glBegin(GL_LINES);
            glColor3f(1, 0, 0);
            glVertex2f(yndc1, -1);
            glVertex2f(yndc2, 1);
            glEnd();
        }
    }
}


//the call back display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //DRAW GRID ON SCREEN
    //creates a rendering area across the window
    glViewport(0, 0, 500, 500);
    
    //draw grid
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(0, -1);
    glVertex2f(0, 1);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glEnd();
    
    //compute new bounding box
    computeBox();
    
    //compute new oblique bounding box
    computeObliqueBox();

    //check if axis is outside the box and update the box
    if(axis)
        updateBox();
    
    //render xy projection in top left
    //creates a rendering area across teh top quad of the screen
    glViewport(0, 250, 250, 250);
    string str = "XY Plane";
    
    for(int i = 0; i < numOfObjects; i++)
    {
        objects[i]->projectXY(option);
        drawstr(-0.2, 0.9, str.c_str(), str.length());
        //label the object
        point p = objects[i]->getCentroid();
        if(option == 1)
            glRasterPos3f(getXNDC(p.x), getYNDC(p.y) , 0);
        else
        {
            glm::vec4 v = p.obliqueVector();
            glRasterPos3f(getXoblique(v[0]), getYoblique(v[1]), 0);
        }
        glutBitmapCharacter(font_style, 'A' + i);
        glEnd();
    }
    drawaxisXY();
    
    //render xz projection in top right
    //xz porjection viewport
    glViewport(250, 250, 250, 250);
    str = "XZ Plane";
    
    for(int i = 0; i < numOfObjects; i++)
    {
        objects[i]->projectXZ(option);
        drawstr(-0.2, 0.9, str.c_str(), str.length());
        //label the object
        point p = objects[i]->getCentroid();
        if(option == 1)
            glRasterPos3f(getXNDC(p.x), getZNDC(p.z) , 0);
        else
        {
            glm::vec4 v = p.obliqueVector2();
            glRasterPos3f(getXoblique(v[0]), getZoblique(v[1]), 0);
        }
        glutBitmapCharacter(font_style, 'A' + i);
        glEnd();
    }
    drawaxisXZ();
    
    //render yz projection in bottom left
    //yz projection viewport
    glViewport(0, 0, 250, 250);
    str = "YZ Plane";
    
    for(int i = 0; i < numOfObjects; i++)
    {
        objects[i]->projectYZ(option);
        drawstr(-0.2, 0.9, str.c_str(), str.length());
        //label the object
        point p = objects[i]->getCentroid();
        if(option == 1)
            glRasterPos3f(getYNDC(p.y), getZNDC(p.z) , 0);
        else
        {
            glm::vec4 v = p.obliqueVector3();
            glRasterPos3f(getYoblique(v[0]), getZoblique(v[1]), 0);
        }
        glutBitmapCharacter(font_style, 'A' + i);
        glEnd();
    }
    drawaxisYZ();
    
    //TEXT MENU!!
    if(status == MENU)
        showMenu();
   
    //if user press key for A or B or C object
    else if(status == OBJECT)
        showObject();
    
    //if user is in translation mode
    else if(status == TRANSLATION || status == TWAIT || status == TSET)
        showTranslation();
    
    //if user is in scale mode
    else if(status == SCALE || status == SWAIT || status == SSET)
        showScale();
    
    //if user is in rotation mode
    else if(status == ROTATION || status == RWAIT || status == RSET)
        showRotation();
    
    glutSwapBuffers();
    glFlush();
}

//show the text menu
void showMenu()
{
    glViewport(250, 0, 250, 250);
    glColor3f(0, 0, 0);
    string str;
    str = "User Menu";
    drawstr(-0.2, 0.9, str.c_str(), str.length());
    str = "Choose one object to manipulate: ";
    drawstr(-0.9, 0.7, str.c_str(), str.length());
    str = "Press a for A";
    drawstr(-0.9, 0.6, str.c_str(), str.length());
    str = "Press b for B";
    drawstr(-0.9, 0.5, str.c_str(), str.length());
    str = "Press c for C";
    drawstr(-0.9, 0.4, str.c_str(), str.length());
    str = "Press 1 for orthographic mode";
    drawstr(-0.9, -0.7, str.c_str(), str.length());
    str = "Press 2 for oblique(cavalier) mode";
    drawstr(-0.9, -0.8, str.c_str(), str.length());
    str = "Press esc to exit and save";
    drawstr(-0.9, -0.9, str.c_str(), str.length());
}

//show the information
void showObject()
{
    if (which != 0)
    {
        int j;
        //render objects information in bottom right
        glViewport(250, 0, 250, 250);
        glColor3f(0, 0, 0);
        string str;
        str = 'A' + which - 1;
        drawstr(-0.9, 0.9, str.c_str(), str.length());
        for(j = 0; j < objects[which - 1]->num_point; j++)
        {
            //get vertice's string
            str = objects[which - 1]->vertices[j]->tostring();
            drawstr(-0.9, 0.8 - j * 0.1, str.c_str(), str.length());
        }
        
        str = "press t to perform translation";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        
        str = "press s to perform scale";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        
        str = "press r to perform rotation";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
        
        str = "Press q to choose another object";
        drawstr(-0.9, -0.6, str.c_str(), str.length());
        str = "Press 1 for orthographic mode";
        drawstr(-0.9, -0.7, str.c_str(), str.length());
        str = "Press 2 for oblique(cavalier) mode";
        drawstr(-0.9, -0.8, str.c_str(), str.length());
        str = "Press esc to exit and save";
        drawstr(-0.9, -0.9, str.c_str(), str.length());
    }
}

//show translation mode
void showTranslation()
{
    glViewport(250, 0, 250, 250);
    glColor3f(0, 0, 0);
    string str;
    int j;
    str = 'A' + which - 1;
    drawstr(-0.9, 0.9, str.c_str(), str.length());
    
    //print out object's information
    for(j = 0; j < objects[which - 1]->num_point; j++)
    {
        //get vertice's string
        str = objects[which - 1]->vertices[j]->tostring();
        drawstr(-0.9, 0.8 - j * 0.1, str.c_str(), str.length());
    }
    if(status == TRANSLATION)
    {
        //print out guide
        str = "Press t to enter the translation vector";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "using command line";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "Press q to perform different transformation";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
    }
    
    else if(status == TSET)
    {
        str = "Current translation vector: ";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "(" + to_string(xvector) + ", "  + to_string(yvector) + ", " + to_string(zvector) + ")";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "Press t to translate the same vector";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
        str = "Press q to enter new parameter";
        drawstr(-0.9, 0.8 - (j + 4) * 0.1, str.c_str(), str.length());
    }
    str = "Press 1 for orthographic mode";
    drawstr(-0.9, -0.7, str.c_str(), str.length());
    str = "Press 2 for oblique(cavalier) mode";
    drawstr(-0.9, -0.8, str.c_str(), str.length());
    str = "Press esc to exit and save";
    drawstr(-0.9, -0.9, str.c_str(), str.length());

}

//show scaling mode
void showScale()
{
    glViewport(250, 0, 250, 250);
    glColor3f(0, 0, 0);
    string str;
    int j;
    str = 'A' + which - 1;
    drawstr(-0.9, 0.9, str.c_str(), str.length());
    
    //print out object's information
    for(j = 0; j < objects[which - 1]->num_point; j++)
    {
        //get vertice's string
        str = objects[which - 1]->vertices[j]->tostring();
        drawstr(-0.9, 0.8 - j * 0.1, str.c_str(), str.length());
    }
    
    if(status == SCALE)
    {
        //print out guide
        str = "Press s to enter the scale factor";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "using command line";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "Press q to perform different transformation";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());

    }
    
    else if(status == SSET)
    {
        str = "Current scale factor: " + to_string(factor);
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "Press s to scale the same factor";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "Press q to enter new parameter";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
    }
    str = "Press 1 for orthographic mode";
    drawstr(-0.9, -0.7, str.c_str(), str.length());
    str = "Press 2 for oblique(cavalier) mode";
    drawstr(-0.9, -0.8, str.c_str(), str.length());
    str = "Press esc to exit and save";
    drawstr(-0.9, -0.9, str.c_str(), str.length());
}

//show rotation mode
void showRotation()
{
    glViewport(250, 0, 250, 250);
    glColor3f(0, 0, 0);
    string str;
    int j;
    str = 'A' + which - 1;
    drawstr(-0.9, 0.9, str.c_str(), str.length());
    
    //print out object's information
    for(j = 0; j < objects[which - 1]->num_point; j++)
    {
        //get vertice's string
        str = objects[which - 1]->vertices[j]->tostring();
        drawstr(-0.9, 0.8 - j * 0.1, str.c_str(), str.length());
    }
    
    if(status == ROTATION)
    {
        //print out guide
        str = "Press r to enter the axis and degree";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "using command line";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "Press q to perform different transformation";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
    }
    else if(status == RSET)
    {
        str = "Current axis: ";
        drawstr(-0.9, 0.8 - (j + 1) * 0.1, str.c_str(), str.length());
        str = "(" + to_string(xaxis1) + ", " + to_string(yaxis1) + ", " + to_string(zaxis1) + ")";
        drawstr(-0.9, 0.8 - (j + 2) * 0.1, str.c_str(), str.length());
        str = "(" + to_string(xaxis2) + ", " + to_string(yaxis2) + ", " + to_string(zaxis2) + ")";
        drawstr(-0.9, 0.8 - (j + 3) * 0.1, str.c_str(), str.length());
        str = "Current angle: " + to_string(angle);
        drawstr(-0.9, 0.8 - (j + 4) * 0.1, str.c_str(), str.length());
        str = "Press r to rotate 1 using same axis";
        drawstr(-0.9, 0.8 - (j + 5) * 0.1, str.c_str(), str.length());
        str = "Press q to enter new parameter";
        drawstr(-0.9, 0.8 - (j + 6) * 0.1, str.c_str(), str.length());
     }
    str = "Press 1 for orthographic mode";
    drawstr(-0.9, -0.7, str.c_str(), str.length());
    str = "Press 2 for oblique(cavalier) mode";
    drawstr(-0.9, -0.8, str.c_str(), str.length());
    str = "Press esc to exit and save";
    drawstr(-0.9, -0.9, str.c_str(), str.length());
}

int main(int argc, char *argv[])
{
    int WinW = 500;
    int WinH = 500;
    
    cout << "Enter the file name containing the objects: ";
    cin >> filename;

    ifstream inf;
    inf.open(filename);
    
    while(inf.fail())
    {
        cout << "File doesn't exist, please enter again: ";
        cin >> filename;
        inf.open(filename);
    }
    
    inf >> numOfObjects;
    
    for (int i = 0; i < numOfObjects; i++)
    {
        object *obj = new object();;
        
        inf >> *obj;
        objects.push_back(obj);
    }
    
    inf.close();
    
    glutInit(&argc, argv); //Initialize Glut
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA); // inits display mode, GLUT_DOUBLE - allows for display on the double buffer window(Depth & RGBA), GLUT_RGBA - shows color (Red, green, blue) and an alpha, GLUT_DEPTH - allows for depth buffer
    
    
    glutInitWindowSize(WinW, WinH); //set window size to 500*500
    glutInitWindowPosition(100, 100); //set window position
    
    MainWindow = glutCreateWindow("Project 2!"); //create and set main window title
    glClearColor (1,1,1,0); //clears the buffer of OpenGL
    
    glutKeyboardFunc(KeyBoardFunc); //keyboard function
    
    //sets display function
    glutDisplayFunc(display);
    
    glutMainLoop();//main display loop, will display until terminate
    return 1;
}


