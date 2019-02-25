
#include <sstream>

#include "uEye.h"
#include "mex.h"

#include "utils.h"

using namespace std;

int startupCamera(const string outputDir)
{
   log("Starting up camera...");

   /**/
   //---------------------------------------------------------------------------
   // Open camera with provided ID
   // STOLEN FROM file:///C:/Program%20Files/IDS/uEye/Help/uEye_Manual/index.html?is_initcamera.html
   // (and greatly simplified)
   HIDS hCam;
   INT nRet = is_InitCamera(&hCam, NULL);
   if (nRet != IS_SUCCESS)
   {
      //Check if GigE uEye SE needs a new starter firmware
      if (nRet == IS_STARTER_FW_UPLOAD_NEEDED)
      {
         log("Camera failed to start up because it requires a firmware update.");
      }
      else
      {
         errorWithReturnCodeAndDetails(hCam, nRet, "Failed to initialize camera with return code ");
      }
      return -1;
   }
   else
   {
      stringstream out;
      out << "Successfully initialized camera with handle " << hCam;
      log(out.str());
   }
   //---------------------------------------------------------------------------

   SENSORINFO sInfo;
   is_GetSensorInfo(hCam, &sInfo);
   stringstream info;
   info << "Color mode is ";
   if (sInfo.nColorMode == IS_COLORMODE_BAYER) info << "BAYER";
   else if (sInfo.nColorMode == IS_COLORMODE_CBYCRY) info << "CBYCRY";
   else info << "MONO8";
   log(info.str());

   // set color mode
   nRet = is_SetColorMode(hCam, IS_CM_JPEG);
   if (nRet != IS_SUCCESS)
   {
      errorWithReturnCodeAndDetails(hCam, nRet, "Failed to set color mode with return code ");
      return -1;
   }

   // TODO set AOI?

   // set display mode
   nRet = is_SetDisplayMode(hCam, IS_SET_DM_DIB);
   if (nRet != IS_SUCCESS)
   {
      errorWithReturnCodeAndDetails(hCam, nRet, "Failed to set display mode with return code ");
      return -1;
   }

   // set trigger mode
   nRet = is_SetExternalTrigger(hCam, IS_SET_TRIGGER_SOFTWARE);
   if (nRet != IS_SUCCESS)
   {
      errorWithReturnCodeAndDetails(hCam, nRet, "Failed to set trigger mode with return code ");
      return -1;
   }
   /**/

   log("...camera started up successfully.");

   createOutputDir(outputDir);

   return hCam;
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   if (nrhs != 1)
   {
      error("camera_startup: you need to provide the output directory");
   }

   if (nlhs != 1)
   {
      error("camera_startup: you need to assign the output of this function to a variable");
   }

   string outputDir = getOutputDir(prhs[0]);
   if (outputDir.empty())
   {
      return;
   }

   // create 1x1 integer for camera handle output
   plhs[0] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);

   // fill in plhs[0] to contain my data
   int* data = (int*)mxGetData(plhs[0]);

   // starts up camera, creates output directory, and returns camera handle
   data[0] = startupCamera(outputDir);
}