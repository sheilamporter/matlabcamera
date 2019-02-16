# TESTING CALLING C++ FROM MATLAB

okay so in theory this is how it should work. i'm basing this off of https://www.mathworks.com/help/matlab/ref/mex.html some of this is matlab jargon that i'm assuming you know, or at least know how to google, because i have no idea what it means.

1. create a writeable folder on your path and set it as the current folder. i'm assuming you can call it whatever you want. example:

```
[s,msg,msgid] = mkdir('c:\work');
if (isempty(msgid))
    mkdir('c:\work')
end
cd c:\work
```

2. download the file CameraThing/CameraThing.cpp from github to this folder you just created.

3. build a 'MEX' file from this .cpp file using the `mex` command:

```
mex CameraThing.cpp
```

if it works, it should apparently say something like:

```
Building with 'MinGW64 Compiler  C '.
MEX completed successfully.
```

if it doesn't work, idek. text me and i'll try to help you debug.

4. test it out in your matlab code. somewhere - doesn't matter where - add this line:

```
testCallingFromMatlab("ohai.txt", "sheila is the best sister ever")
```

if this works, somewhere on your computer (probably in your working directory?) should be a file called `ohai.txt` that says something extremely true. if so, HOORAY, we have confirmed we can call C++ code from matlab! yay! feel free to experiment with generating other files and whatever.

i will continue working on code to actually, like, do things with a camera! but this is sort of prerequisite numero uno, so i figured you can work on that bit while i'm doing other stuff. efficiency! heck yeah!

# CALLING ACTUAL CAMERA CODE

oh god this probably won't work. it probably won't even compile. whatever #yolo

1. ok so first thing is at the beginning of your program you're gonna want to call

```
startupCamera(1, 80)
```

where 1 is the "camera handle" (should be an integer) and 80 is the "quality" you want (should also be an integer, i have no idea what units it's using')

2. ok now every time you wanna take a picture you're gonna want to call

```
captureImage()
```

this will probably block while it's capturing/saving the image so uh. you might notice things slow down. sorry

3. and then when you're done you're gonna want to clean everything up all nice like

```
teardownCamera()
```

what does this do? idk lol

LET'S SEE WHAT FUCKIN HAPPENS BRO