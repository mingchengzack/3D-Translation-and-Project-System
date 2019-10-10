# 3D Translation System
Includes 3D rotation about an arbitrary axis in 3D space(specified by two 3Dpoints and a rotation angle in degrees), and 3D scaling(specified by one scaling factor used in all three directions). The 3D scenes can be orthographic or obliquely projectede in xy, yz and xz planes.

To compile my project, just type make and it will compile a executable called project2.
My project use a external libraries glm for matrix multiplication and storing information.
Make sure it has glm to compile. (I will include glm in my submission folder)

My program will first ask for the name of the file that contains the objects’ information,
then if the file doesn’t exist, it will output a error message and ask for the file again.
My program uses a input file called test.txt and also outputs to the same file(it updates
the vertices of each object). The input and output file format is the same as the example
showed in project 2. 

To run my program, users need to use keyboard and press different keys to interact with the
program. My program used a 500 x 500 window, divided into 4 regions. The top left is used
to display the projections on xy plane (blue), top right for xz plane(green), bottom right 
for yz plane (red), and bottom left for displaying the menu, instructions, objects’ information 
and parameters for each transformation. When the program starts, it displays the objects in 
each plane using orthographic projection by default. It also has a user menu showing that 
“choose one object to manipulate: press a for A, press b for B, press c for C”. As it is 
instructed, user can press a, b, or c on their keyboard to specify one object to do
transformation. On the bottom of the menu, it will always show “Press 1 for orthographic 
mode, Press 2 for oblique(cavalier) mode, and Press esc to exit and save”. As it is instructed,
user can press 1, 2 and esc at any time to switch modes or exit. (Since I implemented both 
orthographic projection and oblique projection, my program provides a option for the user to 
switch between them.

Then After the user press a, b, or c to choose a object to transform. My bottom left will display
the objects’ information (all the vertices’ coordinates) and instructions for each operation.
For example, press t to perform translation, press s to perform scale and press r to perform 
rotation. Also, the user can go back to the main menu to choose another object by pressing q.

After the user choose one operation, for instance, lets say its a rotation. My bottom left will
show that press r to enter the axis and degree using command line or press q to perform a 
different transformation (go back to the previous layer). After the user presses r again,
he needs to enter the starting point for the axis, the end point, and the angle for the rotation
using command line. (Since my program also checks if the input is a float, it will print out
error messages and ask for entering again. For example, it the user enter 2 b b for the starting 
point, it will be consider as wrong format. However, the user needs to enter at least 3
characters/numbers other than whitespace if the program is asking for a point, otherwise it won’t
proceed to the next step.) After getting input, the objects after transformation will be showed.
Then my bottom left will not only print out the objects’ information but also the parameters users
entered such as the rotation axis, the rotation degree, scaling factor and translation vector.
It also provides a option for the user to do the same operation again by pressing r for rotation, 
t for translation and s for scaling. (For rotation, if the user presses r the object will rotate 
the same axis for 1 degree each time the user press r.) Or the user can press q to enter new
parameters for the same transformation. (go back to previous menu layer) For rotation, my program
also draw the axis depending on different projections, but also the user choose to enter new 
axis, the previous axis will disappear. (ATTENTION: Since, I am using a fixed font and position to
print out the information of the objects’ and the menu instructions, when the number of points
of a object is too much, some of the instruction text might not be displayed correctly especially when
the menu is displaying the current axis as well as current angle since there are so many things to print. I believe
9 points are the limit, or the text will overlap with each other. Also, for the axis drawing, I
draw the extension of the axis to fit the renderings area for different planes in case an 
axis is too short for us to see!)

My program implemented every part of the program as well as NDC, scaling bounding box after each
transformation and oblique(cavalier) projection. For bounding box, my program gives a little 
more space than it should be just for viewing. My program computes bounding box and NDC, so
negative coordinates are also applicable in my program. (ATTENTION: since I dynamically scale my
bounding box every time the object is transformed, when a object is enlarged and larger than other 
objects by many times or the object is so far away from each other, the objects will be hard to 
see. Also, since I also put a label (A, B, C) on each object’s center just to help the user to 
choose an object, it will be harder to see when the object showed is too small because the font
I used for labeling doesn’t scale too.) For translation, the user should input the world 
coordinates based vector.

For each implementation:
For translation, line 287 to 293 in object.cpp, and line 145 to 150 to construct the matrix in utility.cpp
For scaling, line 296 to 302 in object.cpp, line 153 to 163 to compute the matrix in utility.cpp
For rotation, line 305 to 339 in object.cpp, line 166 to 187 to compute the matrix in utility.cpp
For orthographic projection ,line 199 to 218 in object.cpp, line 32 to 81 in line.cpp.
For oblique(cavalier) projection, line 221 to 238 in object.cpp, line 84 to 164 in line.cpp
For computing bounding box, line 54 to 132 in utility.cpp
For computing NDC, line 18 to 51 in utility.cpp

