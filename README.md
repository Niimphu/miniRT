# miniRT

## Overview
miniRT is a graphical project, in which a raytracing program must be written from scratch in C within the limitations of 42's minilibx graphical library on the CPU. In this project, I worked with @coderkuehne to implement the parsing of the basic text maps that are required to be handled, and the rendering of spheres, planes and cylinders in the correct manner.

## Concepts
### Introduction
In the physics of the world, light leaves light sources, bounces off objects which changes the colour of the light, and then hits our eyes, which detect what the colour of the light is, allowing us to see what is in the world around us. However, in 3D rendering, if we were to simulate every single light ray from a light source to calculate the image that a camera sees, most of the light rays would never hit the camera.

### Raytracing
The core of raytracing is the reverse of how light works in the real world: drawing rays from the camera to each pixel on the screen to see what it hits, and then calculating the colour of each pixel in this manner.

### 3D intersections
To calculate whether or not the ray intersects with different shapes, a lot of 3D vector maths is necessary. For shapes such as the cylinder and cone, the calculations are made simpler by transforming them to have their axes aligned with the y-axis, and their centres to be at the origin (0,0,0).

### MSAA
Multi-sample anti-aliasing, or MSAA for short, is where instead of one ray being cast into each pixel, multiple offset rays are cast, and then averaged to find a more accurate colour for the pixel. This improves the image quality by reducing the amount of jagged edges at boundaries that are not completely horizontal or vertical.

### Lighting
Different types of lighting and surfaces can interact with each other in different ways. In this project, different spotlights at different positions with different colours can affect how objects are perceived in a scene. Additionally, the scenes can have an ambient light, which gives a tint to the colours seen, as well as adding a hue to the shadows.

### Multithreading
By using the pthread.h library, we can increase the rendering speed of more complex scenes. The screen is divided into the horizontal bands, and each band is handled by a separate core. Mutexes are required to prevent multiple threads drawing to the window at the same time.


## Gallery

Example scene    
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Sample.png' width='800'>

Spheres
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Spheres.png' width='800'>  

Handling multiple light sources with different colours 
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Multispot.png' width='800'>  

Cylinders
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Cylinders.png' width='800'>  

Using triangles to draw a simpel model
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Venus.png' width='800'>  

Handling recursive reflections
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Reflections.png' width='800'>  
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Metal.png' width='800'>
With and without MSAA enabled
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/MSAAon.png' width='800'><img src='https://github.com/Niimphu/miniRT/blob/main/pic/MSAAoff.png' width='800'>  


Specular lighting
<img src='https://github.com/Niimphu/miniRT/blob/main/pic/Specular.png' width='800'>  

