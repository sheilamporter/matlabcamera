
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
         stringstream out;
         out << "Camera failed to start up with return code " << nRet;
         error(out.str());
         tryLogDetails(hCam, nRet);
      }
      return -1;
   }
   else
   {
      stringstream out;
      out << "Camera successfully initialized camera with handle " << hCam;
      log(out.str());
   }
   //---------------------------------------------------------------------------

   // set display mode
   nRet = is_SetDisplayMode(hCam, IS_SET_DM_DIRECT3D);
   if (nRet != IS_SUCCESS)
   {
      stringstream out;
      out << "Failed to set display mode with return code " << nRet;
      error(out.str());
      tryLogDetails(hCam, nRet);
      return -1;
   }

   // set trigger mode
   nRet = is_SetExternalTrigger(hCam, IS_SET_TRIGGER_SOFTWARE);
   if (nRet != IS_SUCCESS)
   {
      stringstream out;
      out << "Failed to set trigger mode with return code " << nRet;
      error(out.str());
      tryLogDetails(hCam, nRet);
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