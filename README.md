# CS595Group12
This is where are Group 12 project will Live. Soon to be decided what it is. 
We can probably add some pros and cons sections to each of these Ideas, or whatever categories we need for the 3 ideas assignment. 

# Project Ideas:
## Midi Editor

### Primary Problem

### target Users

### Scope and Main functionality
A gui that lets musicians take information that is already coming out of their digital instruments, and use it to control visuals on a screen, creating an audio visual experience for live performance. Minimum Viable Product will allow users to upload multiple image file, and control the location, size, rotation, and alpha value/opacity of that image with Midi CCs, or Midi Notes, which will be assigned by the user. 
### Prior Knowledge 
The majority of group members have experience making desktop apps in C based languages, 
The suplamentary Info shouldn't be too hard to pick up. Hal has an understanding of all aspects of this proposed 
application. 

### Description
A gui that lets musicians take information that is already coming out of their digital instruments, and use it to control visuals on a screen, creating an audio visual experience for live performance. Minimum Viable Product will allow users to upload multiple image file, and control the location, size, rotation, and alpha value/opacity of that image with Midi CCs, or Midi Notes, which will be assigned by the user. 

Stretch goals: 
- "Scenes" tied to Midi program changes, or bank changes so that Users can change the current visual to a different visual 
- Simple colored shapes as options instead of images
- Text that can be controlled the same way as images
- Envelopes, LFOs, and constraints for controlling various parameters of the image / shape.
- 3D Model Support 
    
### Proposed Stack
- SDL2 for Graphics and user input. Can be either C++ or C, https://www.libsdl.org/
- Some Midi library, depending on the proposed language / compiler
- SDL2 C# wrapper https://github.com/flibitijibibo/SDL2-CS (looking at this, this may not be the best choice? less support, most SDL2 documentation is for C++. Though there are a fair few example projects in C#. This is something to talk about.)
### Supplemental Info
- What is Midi Exactly? https://youtu.be/faZIkN_e_1s
- Quick Overview on the Midi Spec https://youtu.be/2BccxWkUgaU
- Detailed overview of Midi Spec https://ccrma.stanford.edu/~craig/articles/linuxmidi/misc/essenmidi.html
- SDL2 setup with sublime text, as well as some quick tutorials (C++) https://youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS 


## Music Video Jackbox Game
### Description
A game realtime multiplayer game that lets it's users share videos, and have their friends vote on whether they like them or not. Using the "Jackbox" style, users will log into the game on their phones, while watching one main screen, either in person, or on a live stream. Users will be propted with questions like "What's a song that You think is annoying, but everyone else likes?" or "What's a song that you think player X listens to in the shower?". After all players answer two or 3 of these prompts with youtube links, a playlist of their choices will be compiled into a playlist. Players will be able to vote whether they like the video or not, and whoever posted the video will earn points based on how everyone votes. For example, in our first question, the player that submitted the video that they think is annoying but everyone else likes will get a point for everyone that likes the video, and for the second question, if player X ends up liking the video, then the player that submitted it might get 5 points as a bonus for guessing correctly. The prompt for the video will be shown after everyone has voted, sort of like what VH1 used to do with their music video facts. (if anyone else is old enough to remember VH1).
### Proposed Stack
- Websockets https://www.html5rocks.com/en/tutorials/websockets/basics/
- We could do this through a WebApp, or we could make a dedicated Desktop app. With our knowledge, a Desktop app would probably make the most sense.
### Supplemental Info
- an example of a jackbox game. This just shows the main screen, while the 6 players are submitting answers on their phones https://youtu.be/qmgqZr_eazc 


## Inventory Management software
### Description
A piece of software to manage the inventory of an establishment. This could be a warehouse, senior home, retail store, etc. The software would have the ability to check physical inventory and the non-physical (scheduled shipments to the establishment with estimated dates of arrival). Depending on what we would be simulating we could also include where the items are stocked (retail sections, warehouse pallet/storeroom numbers, etc.)
### Proposed Stack
- Node.js (to manage frontend, backend, and webapp)
- MongoDB (more difficult) JSONdb(very simple)
- WPF Application(C#)
### Supplemental Info
- Web App and/or Desktop App with on premise database and webserver hosting.
### Relevant Skills
- Noah has experience in both MongoDB and Node.JS for a web app and its database
- Quinlan has experience with C#(specifically WPF) and SQL for a desktop app and its databasefrom previous and current job.


> Written with [StackEdit](https://stackedit.io/).
