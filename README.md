# GraphicsSandbox
Welcome friends, I'm using this project for the purpose of learning graphics programming. I have so far been able to create a 3D scene
with a free floating camera that's controlable using keyboard and mouse via DirectInput. I've have for the most part loaded in Wavefront OBJ models successfully via the Open Asset Importer libary as well. However though, I have noticed the lack of quality of OBJ files on the web has given me problems at times due to some of them being poorly exported too the format. I've uploaded a few renders below demonstrating the model loading capabilities. As for texture loading I decided go WICTextureLoader since it's lightweight and simple to use. For the most part I've written this code from scratch with a few books that I own to help me along the way. This is personal project. I have no prior knowlege or have taken any course work in this subject so if you use my source for learning don't be afraid to question things.

Tips For The Beginner:<br>
I have written my own Wavefront OBJ model loader before. For the most part it's not that bad too code yourself. I highly recommend trying it out but probally switching too a proper model loading libary for the long run.

The Math is not that bad. The DirectXMath libary is your friend and will help with some of the heavy lifting when needed. You should however have a basic understanding of Vectors, Matricies, Geometry, and Trignometry to some degree. If you don't I could still see you getting by, but you probally won't understand as much of what you are doing.

When first starting out you don't need to write in object oriented style but switch over at some time for you sanity. 
Microsoft does a phenomenal job with documenting and showing examples of this stuff so go look for it when you need it.

As always put the time and effort in. This stuff is pretty cool. Also build your own structures and algorithms there's nothing wrong about playing around and having some fun ;)

Get started by downloading the SDK below!<br>
https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk

<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/TestWireFrameRender.png">
<br>
<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/Windmill.png">
<br>
<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/TestTextureRender2.png">


Assimp Including and Linking via Visual Stuido
-------------------------------------------------------------------
The Assimp folder I have uploaded is already built for Windows.
Warning I have ran into issues with prebuilds before
so it's best to build your own to be on the safe side and prevent 
headaches. 

VC++ Directories -->  Include Directories  
Assimp\include\assimp

VC++ Directories -->  Library Directories
Assimp\lib\x86
or 
Assimp\lib\x64

Linker --> Input --> Additional Dependencies
assimp.lib

You will also need to be sure copy the Assimp DLL in the same directory as your exe
