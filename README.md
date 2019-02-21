# HOW TO USE THIS CODE IN MATLAB

## 1. Get all your files in order

You're gonna need the following files in whatever folder you're working in:

* `build.m`
* `camera_capture.cpp`
* `camera_startup.cpp`
* `camera_teardown.cpp`
* `uEye.h`
* `uEye_api_64.lib`
* `utils.h`

## 2. Compile the C++ code

Use Matlab to run `build.m` to build all the C++ files into a format Matlab can work with. You'll need to run this once each time the C++ code changes.

If it works correctly, you should see output like this:

```
>>>Building camera_startup.cpp
Building with 'MinGW64 Compiler (C++)'.
MEX completed successfully.
>>>Building camera_capture.cpp
Building with 'MinGW64 Compiler (C++)'.
MEX completed successfully.
>>>Building camera_teardown.cpp
Building with 'MinGW64 Compiler (C++)'.
MEX completed successfully.
```

If you don't see this and get a bunch of scary errors in red, text me. I'll fix it.

This should generate three files (or update them, if they already exist):

* `camera_capture.mexw64`
* `camera_startup.mexw64`
* `camera_teardown.mexw64`

You'll need these too.

## 3. Write your Matlab code

You can now call the C++ functions in your Matlab code as if they were normal Matlab functions. Check `demo.m` for more details and examples.

## 4. Run your Matlab code as usual.

Note that by default, the camera code spits a bunch of stuff out to the Matlab command window. I did this to make it easier for me to diagnose issues in my code, but once we get all this working you might find this annoying. You can quiet it down by changing line 16 in `utils.h` to read `bool LOG = false;` and running `build.m` again. It'll still print errors, but it will stop yelling every time something works the way it's supposed to.