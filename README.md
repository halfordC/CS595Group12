# CS595Group12
This is where are Group 12 project will Live. Soon to be decided what it is. 
We can probably add some pros and cons sections to each of these Ideas, or whatever categories we need for the 3 ideas assignment. 

# Project Ideas:
## Midi Visualizer

### Primary Problem
Musicians with electronic instruments for live shows are getting more and more common. The vast majority of events and venues have some sort of Audio/Visual component to them these days, and the software available for creating synced Visuals to music is all either very expensive, or very complicated. 

### Target Users
Musicians using digital instruments (Synthesizers, drum machines, samplers, effects units, or DJ controllers) 

### Scope and Main functionality
A gui that lets musicians take information that is already coming out of their digital instruments, and use it to control visuals on a screen, creating an audio visual experience for live performance. Minimum Viable Product will allow users to upload multiple image file, and control the location, size, rotation, and alpha value/opacity of that image with Midi CCs, or Midi Notes, which will be assigned by the user. 

### Prior Knowledge 
The majority of group members have experience making desktop apps in C based languages, 
The supplementary Info shouldn't be too hard to pick up. Hal has an understanding of all aspects of this proposed 
application. 

### Stretch Goals
- "Scenes" tied to Midi program changes, or bank changes so that Users can change the current visual to a different visual 
- Simple colored shapes as options instead of images
- Text that can be controlled the same way as images
- Envelopes, LFOs, and constraints for controlling various parameters of the image / shape.
- 3D Model Support 
    
### Proposed Stack
- SDL2 for Graphics and user input. Can be either C++ or C, https://www.libsdl.org/
- GUI Library, with example code https://github.com/actsl/kiss_sdl2
- RTMidi library for C++ https://www.music.mcgill.ca/~gary/rtmidi/index.html#intro

### Supplemental Info
- What is Midi Exactly? https://youtu.be/faZIkN_e_1s
- Quick Overview on the Midi Spec https://youtu.be/2BccxWkUgaU
- Detailed overview of Midi Spec https://ccrma.stanford.edu/~craig/articles/linuxmidi/misc/essenmidi.html
- SDL2 setup with sublime text, as well as some quick tutorials (C++) https://youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS 