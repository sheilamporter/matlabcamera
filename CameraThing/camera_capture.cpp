#include <iomanip>
#include <sstream>

// TEMPORARY - REMOVE THESE
#include <iostream>
#include <fstream>

#include "uEye.h"
#include "mex.h"

#include "utils.h"

using namespace std;

void captureImage(const int cameraHandle, const int quality, const int frame, const string outputDir)
{
   stringstream logtext;
   logtext << "Capturing frame " << frame << "...";
   log(logtext.str());

   stringstream filenamess;
   filenamess << outputDir << setw(10) << setfill('0') << frame << ".jpg";

   logtext.clear();
   logtext << "filename: " << filenamess.str();
   log(logtext.str());

   /*
   // TEMPORARY - REMOVE THIS
   ofstream testfile;
   testfile.open(filenamess.str());
   testfile << "pretend i am a picture pls\n";
   testfile.close();
   */

   /**/
   // capture image
   HIDS hCam = cameraHandle;
   INT nRet = is_FreezeVideo(hCam, IS_WAIT);
   if (nRet != IS_SUCCESS)
   {
      stringstream out;
      out << "Failed to capture image with return code " << nRet;
      error(out.str());
      return;
   }
   else
   {
      log("captured image");
   }

   // save image
   std::wstring filename = std::wstring(filenamess.str().begin(), filenamess.str().end());
   wchar_t* filenameCstr = const_cast<wchar_t*>(filename.c_str());

   IMAGE_FILE_PARAMS ImageFileParams;
   ImageFileParams.pwchFileName = filenameCstr;
   ImageFileParams.nFileType = IS_IMG_JPG;
   ImageFileParams.nQuality = quality;
   nRet = is_ImageFile(hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
   if (nRet != IS_SUCCESS)
   {
      stringstream out;
      out << "Failed to save image with return code " << nRet;
      error(out.str());
      return;
   }
   else
   {
      log("saved image");
   }
   /**/

   log("...image captured.");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   if (nrhs != 4)
   {
      error("camera_capture: you need to provide 4 arguments (camera handle, quality, frame #, and output folder)");
      return;
   }

   for (int i = 0; i < 3; ++i)
   {
      if (!mxIsDouble(prhs[i]) && !mxIsInt32(prhs[i]))
      {
         stringstream s;
         s << "camera_capture: argument " << i << " is not a number.";
         error(s.str());
         return;
      }
   }

   int cameraID = (int) mxGetScalar(prhs[0]);
   int quality = (int) mxGetScalar(prhs[1]);
   int frame = (int) mxGetScalar(prhs[2]);

   string outputDir = getOutputDir(prhs[3]);
   if (outputDir.empty())
   {
      return;
   }

   log("about to call captureImage");

   captureImage(cameraID, quality, frame, outputDir);
}
