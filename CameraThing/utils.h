#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <algorithm>
#include <string>
#include <time.h>
#include <Windows.h>

#include "mex.h"

using namespace std;

static string dir = "";

string outputDir()
{
   return dir;
}

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
   //#pragma warning(suppress : 4996)
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%F.%X", &tstruct);
   return buf;
}

string sanitizeOutputDir(string dir)
{
   replace(dir.begin(), dir.end(), ':', '.');
   replace(dir.begin(), dir.end(), ' ', '_');
   return dir + "\\";
}

string getOutputDir(const mxArray *input)
{
   // string nonsense
   char *input_buf;
   size_t buflen;

   /* input must be a string */
   if (mxIsChar(prhs[3]) != 1)
   {
      error("camera_capture: output directory (4th argument) is not a string");
      return "";
   }

   /* input must be a row vector */
   if (mxGetM(prhs[3]) != 1)
   {
      error("camera_capture: output directory (4th argument) is not a vector");
      return "";
   }

   /* get the length of the input string */
   buflen = (mxGetM(prhs[3]) * mxGetN(prhs[3])) + 1;

   /* copy the string data from prhs[0] into a C string input_ buf.    */
   input_buf = mxArrayToString(prhs[3]);

   if (input_buf == NULL)
   {
      error("camera_capture: couldn't convert output directory to string");
      return "";
   }

   string outputDir(input_buf);

   outputDir = sanitizeOutputDir(outputDir);

   return outputDir;
}

void createOutputDir(string dir)
{
   LPCSTR s = dir.c_str();
   CreateDirectory(s, NULL);
}

#endif //UTILS_INCLUDED
