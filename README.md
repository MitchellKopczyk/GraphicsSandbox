# GraphicsSandbox
A DirectX project to render models, simulate lighting and much more.
Get started by downloading the SDK below!<br>
https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk

<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/TestTextureRender2.png">
<br>
<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/Windmill.png">
<br>
<img height="435" width="900" src="https://raw.githubusercontent.com/MitchellKopczyk/GraphicsSandbox/master/samples/TestWireFrameRender.png">


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
