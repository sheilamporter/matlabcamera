// CameraThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>
#include <Windows.h>

#include "mex.h"
//#include "uEye.h"

using namespace std;

// change this to false if you don't want this to output log files.
// will probably speed up performance.
bool LOG = true;
ofstream logfile;

// variables
int cameraID = -1;
string outputDir = "";
int quality = 0;
int frame = 0;

string currentTime()
{
   // TODO: need millisecond precision here to really be useful

   /*auto now = chrono::system_clock::now();
   time_t timestamp = chrono::system_clock::to_time_t(now);
   string prefix = "[";
   prefix += ctime(&timestamp);
   prefix += "] ";
   return prefix;*/

   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
#pragma warning(suppress : 4996)
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%F.%X", &tstruct);
   return buf;
}

void setupLog()
{
   if (!LOG)
      return;
   logfile.open(outputDir + "cameralog.txt");
}

void teardownLog()
{
   if (!LOG)
      return;
   logfile.close();
}

void log(string output)
{
   if (!LOG)
      return;
   logfile << "[" << currentTime().c_str() << "] " << output.c_str() << "\n";
}

void startupCamera(const int cameraHandle, const int imageQuality)
{
   // cache handle
   cameraID = cameraHandle;
   quality = imageQuality;

   // create output folder
   string time = currentTime();
   replace(time.begin(), time.end(), ':', '.');
   outputDir = "camerarun_" + time + "\\";
   // WINDOWS WHY ARE YOU LIKE THIS
   std::wstring stemp = std::wstring(outputDir.begin(), outputDir.end());
   LPCWSTR sw = stemp.c_str();
   CreateDirectory(sw, NULL);

   setupLog();
   stringstream logtext;
   logtext << "Starting up camera with ID " << cameraID << " and quality " << quality << "...";
   log(logtext.str());
   
   /*
   //---------------------------------------------------------------------------
   // Open camera with provided ID
   // STOLEN FROM file:///C:/Program%20Files/IDS/uEye/Help/uEye_Manual/index.html?is_initcamera.html
   // (and greatly simplified)
   HIDS hCam = cameraID;
   INT nRet = is_InitCamera(&hCam, NULL);
   if (nRet != IS_SUCCESS)
   {
      //Check if GigE uEye SE needs a new starter firmware
      if (nRet == IS_STARTER_FW_UPLOAD_NEEDED)
      {
         log("ERROR: Camera failed to start up because it requires a firmware update.");
      }
      else
      {
         log("ERROR: Camera failed to start up with return code " + nRet);
      }
      return;
   }
   //---------------------------------------------------------------------------

   // set display mode
   nRet = is_SetDisplayMode(&hCam, IS_SET_DM_DIRECT3D);
   if (nRet != IS_SUCCESS)
   {
      log("ERROR: Failed to set display mode with return code " + nRet);
      return;
   }

   // set trigger mode
   nRet = is_SetExternalTrigger(&hCam, IS_SET_TRIGGER_SOFTWARE);
   if (nRet != IS_SUCCESS)
   {
      log("ERROR: Failed to set display mode with return code " + nRet);
      return;
   }
   */

   log("...camera started up successfully.");
}

void captureImage()
{ 
   stringstream logtext;
   logtext << "Capturing frame " << frame << "...";
   log(logtext.str());

   /*
   // capture image
   HIDS hCam = cameraID;
   INT nRet = is_FreezeVideo(&hCam, IS_WAIT);
   if (nRet != IS_SUCCESS)
   {
      log("ERROR: Failed to capture image with return code " + nRet);
      return;
   }

   // save image
   stringstream filenamess;
   filenamess << outputDir << setw(10) << setfill('0') << frame << ".jpg";
   std::wstring filename = std::wstring(filenamess.str().begin(), filenamess.str().end());

   IMAGE_FILE_PARAMS ImageFileParams;
   ImageFileParams.pwchFileName = filename.c_str();
   ImageFileParams.nFileType = IS_IMG_JPG;
   ImageFileParams.nQuality = 80;
   nRet = is_ImageFile(&hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
   if (nRet != IS_SUCCESS)
   {
      log("ERROR: Failed to save image with return code " + nRet);
      return;
   }
   */

   ++frame;
   log("...image captured.");
}

void teardownCamera()
{
   log("Tearing down camera...");

   /*
   // shut down camera
   HIDS hCam = cameraID;
   INT nRet = is_ExitCamera(&hCam);
   if (nRet != IS_SUCCESS)
   {
      log("ERROR: Camera failed to shut down with return code " + nRet);
   }
   else
   {
      log("...camera shut down successfully.");
   }
   */

   // clean up variables
   // probably not necessary but i don't trust anything
   cameraID = -1;
   outputDir = "";
   quality = 0;
   frame = 0;

   teardownLog();
}

void testCallingFromMatlab(string filename, string input)
{
   ofstream outfile;
   outfile.open(filename);
   outfile << input.c_str() << '\n';
   outfile.close();
}

int main()
{
   //testCallingFromMatlab("ohai.txt", "check it out, matlab did the thing!");
   startupCamera(1, 80);
   captureImage();
   captureImage();
   captureImage();
   teardownCamera();
   return 0;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   int i;

   /* Examine input (right-hand-side) arguments. */
   mexPrintf("\nThere are %d right-hand-side argument(s).", nrhs);
   for (i = 0; i<nrhs; i++) {
      mexPrintf("\n\tInput Arg %i is of type:\t%s ", i, mxGetClassName(prhs[i]));
   }

   /* Examine output (left-hand-side) arguments. */
   mexPrintf("\n\nThere are %d left-hand-side argument(s).\n", nlhs);
   if (nlhs > nrhs)
      mexErrMsgIdAndTxt("MATLAB:mexfunction:inputOutputMismatch",
         "Cannot specify more outputs than inputs.\n");

   for (i = 0; i<nlhs; i++) {
      plhs[i] = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(plhs[i]) = (double)mxGetNumberOfElements(prhs[i]);
   }
}