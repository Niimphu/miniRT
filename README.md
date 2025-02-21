# miniRT
miniRT is a graphical project, in which a raytracing program must be written from scratch in C within the limitations of 42's minilibx graphical library on the CPU. In this project, I worked with @coderkuehne to implement the parsing of the basic text maps that are required to be handled, and the rendering of spheres, planes and cylinders in the correct manner.

# Contents

- [Concepts](#concepts)

- [Usage](#usage)

- [Gallery](#gallery)

- [Reading and editing map files](#reading-and-editing-map-files)


# Concepts
## Introduction
In the physics of the world, light leaves light sources, bounces off objects which changes the colour of the light, and then hits our eyes, which detect what the colour of the light is, allowing us to see what is in the world around us. However, in 3D rendering, if we were to simulate every single light ray from a light source to calculate the image that a camera sees, most of the light rays would never hit the camera.

## Raytracing
The core of raytracing is the reverse of how light works in the real world: drawing rays from the camera to each pixel on the screen to see what it hits, and then calculating the colour of each pixel in this manner.

## 3D intersections
To calculate whether or not the ray intersects with different shapes, a lot of 3D vector maths is necessary. For shapes such as the cylinder and cone, the calculations are made simpler by transforming them to have their axes aligned with the y-axis, and their centres to be at the origin (0,0,0).

## MSAA
Multi-sample anti-aliasing, or MSAA for short, is where instead of one ray being cast into each pixel, multiple offset rays are cast, and then averaged to find a more accurate colour for the pixel. This improves the image quality by reducing the amount of jagged edges at boundaries that are not completely horizontal or vertical.

## Lighting
Different types of lighting and surfaces can interact with each other in different ways. In this project, different spotlights at different positions with different colours can affect how objects are perceived in a scene. Additionally, the scenes can have an ambient light, which gives a tint to the colours seen, as well as adding a hue to the shadows.

## Multithreading
By using the pthread.h library, we can increase the rendering speed of more complex scenes. The screen is divided into the horizontal bands, and each band is handled by a separate core. Mutexes are required to prevent multiple threads drawing to the window at the same time.


# Usage
## Prerequisites
MiniLibX for Linux requires xorg, x11 and zlib. These dependencies can be installed with:
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

## Installation
1. Clone this repository `git clone https://github.com/Niimphu/miniRT.git`.
2. Navigate to the project directory `cd miniRT`.
3. Compile with `make`, or `make bonus` to compile with multi-threading.


## Launch
1. Select a map from the maps/ sub-directory
2. Run the program with `./miniRT path/to/map`, or `./miniRT -a path/to/map` to run with anti-aliasing. (The program uses 4x MSAA, and will render 4x slower).


Example:
```
git clone https://github.com/Niimphu/miniRT.git
cd miniRT
make bonus
./miniRT maps/metal.rt
```



## Gallery

Example scene    
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Sample.png' width='800'>

Spheres
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Spheres.png' width='800'>  

Handling multiple light sources with different colours 
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Multispot.png' width='800'>  

Cylinders
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Cylinders.png' width='800'>  

Using triangles to draw a simple model
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Venus.png' width='800'>  

Handling recursive reflections
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Reflections.png' width='800'>  
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Metal.png' width='800'>
With and without MSAA enabled
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/MSAAon.png' width='800'><img src='https://github.com/Niimphu/miniRT/blob/main/pic/MSAAoff.png' width='800'>  


Specular lighting
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Specular.png' width='800'>  

# Reading and editing map files
The project requires our maps to be text files with the .rt ending.
The formatting for each map element starts with a letter which identifies the element, and is followed by specific information for that element.

The information required with examples are as follows:

### Ambient lightning:

`A 0.2 255,255,255`

* identifier: `A`

* ambient lighting ratio in range [0.0,1.0]: `0.2`

* R,G,B colors in range [0-255]: `255, 255, 255`

### Camera:

`C -50.0,0,20 0,0,1 70`

* identifier: `C`

* x,y,z coordinates of the view point: `-50.0,0,20`

* 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: `0.0,0.0,1.0`

* FOV : Horizontal field of view in degrees in range [0,180]: `70`

### Light:

`L -40.0,50.0,0.0 0.6 10,0,255`

* identifier: `L`

* x,y,z coordinates of the light point: `-40.0,50.0,0.0`

* the light brightness ratio in range [0.0,1.0]: `0.6`

* (unused in mandatory part)R,G,B colors in range [0-255]: `10, 0, 255`

### Sphere:

`sp 0.0,0.0,20.6 12.6 10,0,255`

* identifier: `sp`

* x,y,z coordinates of the sphere center: 0.0,0.0,20.6

* the sphere diameter: `12.6`

* R,G,B colors in range [0-255]: `10, 0, 255`

### Plane:

`pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`

* identifier: `pl`

* x,y,z coordinates of a point in the plane: `0.0,0.0,-10.0`

* 3d normalized normal vector. In range [-1,1] for each x,y,z axis: `0.0,1.0,0.0`

* R,G,B colors in range [0-255]: `0,0,225`

### Cylinder:

`cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`

* identifier: `cy`

* x,y,z coordinates of the center of the cylinder: `50.0,0.0,20.6`

* 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis: `0.0,0.0,1.0`

* the cylinder diameter: `14.2`

* the cylinder height: `21.42`

* R,G,B colors in range [0,255]: `10, 0, 255`

### Cone:

`co     0.0,5.0,0.0      0.0,1.0,0.0     4     7      10, 0, 255`

* identifier: `co`

* x,y,z coordinates of the tip of the cone `0.0,5.0,0.0  `

* 3d normalized vector of axis of cone. In range [-1,1] for each x,y,z axis: `0.0,1.0,0.0`

* the cone diameter: `4`

* the cone height: `7`

* R,G,B colors in range [0,255]: `10, 0, 255`

### Triangle:

`tr  0,0,0  0,2,0  0,1,3  200,190,190`

* identifier: `tr`

* x,y,z coordinates of the three corners `0,0,0  0,2,0  0,1,3`

* R,G,B colors in range [0,255]: `200,190,190`

### Material:

Optionally, material information can be appended to an object element to define its specular/reflective properties:

`sp 0.0,0.0,20.6 12.6 10,0,255             0.4  10 0`

The three requires properties are appened to this sphere, and are:

* Specular coefficient: [0,1]

* Shininess: [1,inf]

* Reflectivity in the range [0,1]


