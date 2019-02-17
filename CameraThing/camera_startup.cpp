
#include <sstream>

//#include "uEye.h"
#include "mex.h"

#include "state.h"
#include "utils.h"

using namespace std;

void startupCamera(const int cameraHandle, const string outputDir)
{
   stringstream logtext;
   logtext << "Starting up camera with ID " << cameraHandle << "...";
   log(logtext.str());

   /*
   //---------------------------------------------------------------------------
   // Open camera with provided ID
   // STOLEN FROM file:///C:/Program%20Files/IDS/uEye/Help/uEye_Manual/index.html?is_initcamera.html
   // (and greatly simplified)
   HIDS hCam = cameraHandle;
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
   error("Failed to set display mode with return code " + nRet);
   return;
   }

   // set trigger mode
   nRet = is_SetExternalTrigger(&hCam, IS_SET_TRIGGER_SOFTWARE);
   if (nRet != IS_SUCCESS)
   {
   error("Failed to set display mode with return code " + nRet);
   return;
   }
   */

   log("...camera started up successfully.");

   createOutputDir(outputDir);
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   if (nrhs != 2)
   {
      error("camera_startup: you need to provide two arguments");
   }

   if (!mxIsDouble(prhs[0]))
   {
      error("camera_startup: you need to provide a double for the camera handle (first argument)");
      return;
   }

   int cameraID = (int)mxGetScalar(prhs[0]);

   string outputDir = getOutputDir(prhs[1]);
   if (outputDir.empty())
   {
      return;
   }

   startupCamera(cameraID, outputDir);
}