# CS595Group12
## Midi Visualizer
This is a project for the class CS595 at the University of Milwaukee, Fall 2021. 
The final video presentation for this project can be found at https://www.youtube.com/watch?v=RJJTx2vnhn8
(Please excuse the video latency, my interface / PC isn't the best).

This project compiles in Visual Studio 2019 (you'll need to install the VC distribution of SDL2)
Or, if you'd just like to run the .exe for windows, https://drive.google.com/file/d/1Z7eze3ubdD4ODV74ARYhTCrw1aX4K1a_/view

Group Members and Roles:
Hal Crossno: Product Owner and Juce Midi Implementation.
Grant Adams: GUI
Quinlan Walters: Translational Layer
Noah Ratzburg: SDL2 Layer / Graphics engine
Sai Indukuri: Report Writer


### Primary Problem
Musicians with electronic instruments for live shows are getting more and more common. The vast majority of events and venues have some sort of Audio/Visual component to them these days, and the software available for creating synced Visuals to music is all either very expensive, or very complicated. 

### Target Users
Musicians using digital instruments (Synthesizers, drum machines, samplers, effects units, or DJ controllers) 

### Scope and Main functionality
A gui that lets musicians take information that is already coming out of their digital instruments, and use it to control visuals on a screen, creating an audio visual experience for live performance. Minimum Viable Product will allow users to upload multiple image file, and control the location, size, and rotation of that image with Midi CCs, or Midi Notes, which will be assigned by the user. 

### Prior Knowledge 
The majority of group members have experience making desktop apps in C based languages, 
The supplementary Info shouldn't be too hard to pick up. Hal has an understanding of all aspects of this proposed 
application. 

### Stretch Goals
- "Scenes" tied to Midi program changes, or bank changes so that Users can change the current visual to a different visual (partially implemented)
- Simple colored shapes as options instead of images
- Text that can be controlled the same way as images
- Envelopes, LFOs, and constraints for controlling various parameters of the image / shape.
- 3D Model Support 
    
### Proposed Stack
- SDL2 for Graphics and user input. Can be either C++ or C, https://www.libsdl.org/
- SDL2 Image https://www.libsdl.org/projects/SDL_image/
- SDL2 TTF for Fonts https://www.libsdl.org/projects/SDL_ttf/
- Kiss SDL2 GUI Library, with example code https://github.com/actsl/kiss_sdl2
- Juce Library for C++ https://juce.com/