
#include <sstream>

#include "mex.h"

#include "logging.h"
#include "state.h"
#include "utils.h"

using namespace std;

void startupCamera(const int cameraHandle, const int imageQuality)
{
   // cache stuff
   cacheCameraID(cameraHandle);
   cacheQuality(imageQuality);

   setupOutput();

   setupLog();
   stringstream logtext;
   logtext << "Starting up camera with ID " << getCameraID() << " and quality " << getQuality() << "...";
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


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   if (nrhs != 2)
   {
      mexPrintf("startupCamera: you need to provide 2 arguments");
   }

   if (!mxIsDouble(prhs[0]))
   {
      mexPrintf("startupCamera: camera handle (first argument) needs to be a double\n");
      return;
   }

   if (!mxIsDouble(prhs[1]))
   {
      mexPrintf("startupCamera: quality (second argument) needs to be a double\n");
      return;
   }

   int cameraID = (int)mxGetScalar(prhs[0]);
   int quality = (int)mxGetScalar(prhs[1]);

   startupCamera(cameraID, quality);
}