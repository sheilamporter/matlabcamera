% the 'build' script i wrote will compile the C++ code i wrote
% run that script every time you get updated code from me.
% you can add it at the beginning of your other scripts like this to be paranoid,
% but it takes a good couple seconds so you might find that annoying.
build

% you'll have to determine the output folder name in matlab,
% because every time you call a C++ function it's starting from scratch
% and can't remember what it did last time.
% i recommend including the timestamp like this so you don't accidentally
% overwrite output from a previous run.
timestamp = datestr(now);
outputfolder = strcat('cameraoutput_', timestamp);

% other variables
camerahandle = 1; % camera handle. ID number of some sort? idk
quality = 80; % i have no idea what units "quality" is but 80 was the example
frame = 0; % used to generate image filenames

% call this once when you set up your program.
% it will start up the camera and create the folder for captured images.
camera_startup(camerahandle, outputfolder);

% call this every time you want to capture an image.
% make sure you pass in a unique frame # every time, since that's what i use
% to generate filenames, and you don't want to overwite images.
% presumably you will have this in like a loop or something for real,
% but this demonstrates taking 3 pictures in a row.
camera_capture(camerahandle, quality, frame, outputfolder);
frame = frame + 1;
camera_capture(camerahandle, quality, frame, outputfolder);
frame = frame + 1;
camera_capture(camerahandle, quality, frame, outputfolder);

% call this once when you're done taking pictures.
% it shuts down the camera - if we don't do that, it might get cranky if
% you try to run the script again and want a restart or something.
camera_teardown(camerahandle);