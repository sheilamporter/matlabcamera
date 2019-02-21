disp("building camera_startup.cpp")
mex camera_startup.cpp uEye_api_64.lib
disp("building camera_capture.cpp")
mex camera_capture.cpp uEye_api_64.lib
disp("building camera_teardown.cpp")
mex camera_teardown.cpp uEye_api_64.lib
