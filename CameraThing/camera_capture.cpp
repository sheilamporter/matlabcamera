//#include "uEye.h"
#include "mex.h"

#include "utils.h"

using namespace std;

void captureImage(const int cameraHandle, const int quality, const int frame, const string outputDir)
{
   stringstream logtext;
   logtext << "Capturing frame " << frame << "...";
   log(logtext.str());

   /*
   // capture image
   HIDS hCam = cameraHandle;
   INT nRet = is_FreezeVideo(&hCam, IS_WAIT);
   if (nRet != IS_SUCCESS)
   {
   error("Failed to capture image with return code " + nRet);
   return;
   }

   // save image
   stringstream filenamess;
   filenamess << outputDir << setw(10) << setfill('0') << frame << ".jpg";
   std::wstring filename = std::wstring(filenamess.str().begin(), filenamess.str().end());

   IMAGE_FILE_PARAMS ImageFileParams;
   ImageFileParams.pwchFileName = filename.c_str();
   ImageFileParams.nFileType = IS_IMG_JPG;
   ImageFileParams.nQuality = quality;
   nRet = is_ImageFile(&hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
   if (nRet != IS_SUCCESS)
   {
   error("Failed to save image with return code " + nRet);
   return;
   }
   */

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
      if (!mxIsDouble(prhs[i]))
      {
         stringstream s;
         s << "camera_capture: argument " << i << " is not a double.";
         error(s.str());
         return;
      }
   }

   int cameraID = (int)mxGetScalar(prhs[0]);
   int quality = (int)mxGetScalar(prhs[1]);
   int frame = (int)mxGetScalar(prhs[2]);

   string outputDir = getOutputDir(prhs[1]);
   if (outputDir.empty())
   {
      return;
   }

   captureImage(cameraID, quality, frame, outputDir);
}
