
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
- Some Midi library, depending on the proposed language / compiler
- SDL2 C# wrapper https://github.com/flibitijibibo/SDL2-CS (looking at this, this may not be the best choice? less support, most SDL2 documentation is for C++. Though there are a fair few example projects in C#. This is something to talk about.)
- 
### Supplemental Info
- What is Midi Exactly? https://youtu.be/faZIkN_e_1s
- Quick Overview on the Midi Spec https://youtu.be/2BccxWkUgaU
- Detailed overview of Midi Spec https://ccrma.stanford.edu/~craig/articles/linuxmidi/misc/essenmidi.html
- SDL2 setup with sublime text, as well as some quick tutorials (C++) https://youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS 


## Music Video Jackbox Game
### Primary Problem
Are you ever up really late with a friend or two, and your night just devolves into looking up different Music videos and other content on YouTube? This app aims to help you determine who is quantifiably the best at knowing what everyone would like to listen to and watch, as well as get to know your friend's music taste's.

### Target Users
Groups of friends, college students, family get-togethers, or twitch streamers.  

### Scope and Main functionality
A real-time multiplayer game that lets its users share videos, and have their friends vote on whether they like them or not. Using the "Jackbox" style, users will log into the game on their phones, while watching one main screen, either in person or on a live stream. Users will be prompted with questions like "What's a song that You think is annoying, but everyone else likes?" or "What's a song that you think player X listens to in the shower?". After all, players answer two or 3 of these prompts with YouTube links, a playlist of their choices will be compiled into a playlist. Players will be able to vote whether they like the video or not, and whoever posted the video will earn points based on how everyone votes. For example, in our first question, the player that submitted the video that they think is annoying but everyone else likes will get a point for everyone that likes the video, and for the second question, if player X ends up liking the video, then the player that submitted it might get 5 points as a bonus for guessing correctly. The prompt for the video will be shown after everyone has voted, sort of like what VH1 used to do with their music video facts. (if anyone else is old enough to remember VH1).

### Prior Knowledge
All members of the team have made WebApps in intro to software Engineering, this could be run on a similar system. 

### Proposed Stack
- Websockets https://www.html5rocks.com/en/tutorials/websockets/basics/
- We could do this through a WebApp, or we could make a dedicated Desktop app. With our knowledge, a Desktop app would probably make the most sense.

### Supplemental Info
- an example of a jackbox game. This just shows the main screen, while the 6 players are submitting answers on their phones https://youtu.be/qmgqZr_eazc 


## Inventory Management software
### Description
A piece of software to manage the inventory of an establishment. This could be a warehouse, senior home, retail store, etc. The software would have the ability to check physical inventory and the non-physical (scheduled shipments to the establishment with estimated dates of arrival). Depending on what we would be simulating we could also include where the items are stocked (retail sections, warehouse pallet/storeroom numbers, etc.)
### Problem
Small companies are becoming increasingly common with the internet. Having a business often necessitates keeping track of goods flowing in, out, and what's on your shelves. Inventory management software however is often expensive and requires you to pay for hosting remotely.
### Stretch Goals
- Ability to run reports to track patterns and analyze inflow and outflow data.
### Proposed Stack
- Node.js (to manage frontend, backend, and webapp)
- MongoDB (more difficult) JSONdb(very simple)
- WPF Application(C#)
### Supplemental Info
- Web App and/or Desktop App with on premise database and webserver hosting.
- Should be packaged well and easily deployed to different businesses.
### Relevant Skills
- Noah has experience in both MongoDB and Node.JS for a web app and its database
- Quinlan has experience with C#(specifically WPF) and SQL for a desktop app and its database from previous and current job.
- Sai has a experience with working with dealing with database managament and dealing with C and javascript for managing the backend/frontend
- Data structures and organization will be the main skill needed which all team members have from their schooling at a minimum.


> Written with [StackEdit](https://stackedit.io/).
