# WebcamParticles
This project is intended to be a tutorial for myself on the use of shaders and FBOs in Open Frameworks applied both as post-effects and as update shaders to control a particle system.

## Description
The processing pipeline works as follows:
- An image is retrieved from the webcam
- An edge detection shader is used on the image
- The resulting image is fed into the update shader of the particle system to modify their trajectory

The resulting video has a rain-like quality where particles tend to stay on the horizontal flat edges and flow sideways in corrispondence of slopes.

Here a video is presented to show the program in action both with a webcam as input and also as a post-processing effect on a previously made video

[https://youtu.be/lFImnMZY1ZU](https://www.youtube.com/watch?v=lFImnMZY1ZU)

## Libraries
This project uses [FuseFactory's great ofxFastParticleSystem](https://github.com/fusefactory/ofxFastParticleSystem?tab=readme-ov-file) library for the particle system 

## Credit
The edge detection shader code has been adapted from Gijs' implementation on [ Shadertoy](https://www.shadertoy.com/view/td2yDm)  

## To do
- Automatically resize the window size according to the webcam in use
- Allow to switch between webcams while the application is running

## Notes
Tested on a M1 Macbook Air with 16GB of RAM
