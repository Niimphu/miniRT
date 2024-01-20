# miniRT (project in progress)

## Overview
miniRT is a graphical project, in which a raytracing program must be written within the limitations of 42's minilibx graphical library. In this project, I worked with @coderkuehne to implement the parsing of the basic text maps that are required to be handled, and the rendering of spheres, planes and cylinders in the correct manner.

## Concepts
### Introduction
In the physics of the world, light leaves light sources, bounces off objects which changes the colour of the light, and then hits our eyes, which detect what the colour of the light is, allowing us to see what is in the world around us. However, in 3D rendering, if we were to simulate every single light ray from a light source to calculate the image that a camera sees, most of the light rays would never hit the camera.

### Raytracing
The core of raytracing is the reverse of how light works in the real world: drawing rays from the camera to each pixel on the screen to see what it hits, and then calculating the colour of each pixel in this manner.

### MSAA
Multi-sample anti-aliasing, or MSAA for short, is where instead of one ray being cast into each pixel, multiple offset rays are cast, and then averaged to find a more accurate colour for the pixel. This improves the image quality by reducing the amount of jagged edges at boundaries that are not completely horizontal or vertical.

### Lighting
Different types of lighting and surfaces can interact with each other in different ways. In this project, different spotlights at different positions with different colours can affect how objects are perceived in a scene. Additionally, the scenes can have an ambient light, which gives a tint to the colours seen, as well as adding a hue to the shadows.


## Gallery

<img src='https://github.com/Niimphu/miniRT/blob/main/pic/spheres.png' width='800'>  
many objects  


<img src='https://github.com/Niimphu/miniRT/blob/main/pic/multispot.png' width='800'>  
multiple light sources with different colours  


<img src='https://github.com/Niimphu/miniRT/blob/main/pic/no_msaa.png' width='800'>  
MSAA disabled  


<img src='https://github.com/Niimphu/miniRT/blob/main/pic/msaa.png' width='800'>  
MSAA enabled (runs much slower)  

