#include "uEye.h"
#include "mex.h"

#include "logging.h"

using namespace std;

void teardownCamera(const int cameraHandle)
{
   stringstream logtext;
   logtext << "Tearing down camera with ID " << cameraHandle << "...";
   log(logtext.str());

   /*
   // shut down camera
   HIDS hCam = cameraHandle;
   INT nRet = is_ExitCamera(&hCam);
   if (nRet != IS_SUCCESS)
   {
      error("Camera failed to shut down with return code " + nRet);
   }
   else
   {
      log("...camera shut down successfully.");
   }
   */
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   if (nrhs != 1 || !mxIsDouble(prhs[0]))
   {
      error("camera_teardown: you need to provide a double for the camera handle");
      return;
   }

   int cameraID = (int)mxGetScalar(prhs[0]);

   teardownCamera(cameraID);
}