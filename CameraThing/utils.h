#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <algorithm>
#include <sstream>
#include <string>
#include <time.h>
#include <Windows.h>

#include "mex.h"

using namespace std;

// change this to 'false' if you don't want camera code to output debug logs.
// it will still output errors.
bool LOG = true;

void writeToLog(string output)
{
   stringstream log;
   log << "[camera] " << output.c_str() << "\n";
   mexPrintf(log.str().c_str());
}

void log(string output, bool force = false)
{
   if (!LOG && !force)
      return;
   writeToLog(output);
}

void error(string output)
{
   writeToLog("ERROR: " + output);
}

void tryLogDetails(int cameraHandle, int errorCode)
{
   if (errorCode == IS_NO_SUCCESS)
   {
      char* errorString;
      int ret = is_GetError(cameraHandle, &errorCode, &errorString);
      stringstream output;
      output << "DETAILS: ";
      if (ret == IS_SUCCESS)
      {
         output << errorString;
      }
      else
      {
         output << "Could not get more information about the error";
      }
      log(output.str(), true);
   }
}

void errorWithReturnCodeAndDetails(int cameraHandle, int returnCode, string text)
{
   stringstream output;
   output << text << returnCode;
   error(output.str());
   tryLogDetails(cameraHandle, returnCode);
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
   if (mxIsChar(input) != 1)
   {
      error("output directory (4th argument) is not a string");
      return "";
   }

   /* input must be a row vector */
   if (mxGetM(input) != 1)
   {
      error("output directory (4th argument) is not a vector");
      return "";
   }

   /* get the length of the input string */
   buflen = (mxGetM(input) * mxGetN(input)) + 1;

   /* copy the string data from prhs[0] into a C string input_ buf.    */
   input_buf = mxArrayToString(input);

   if (input_buf == NULL)
   {
      error("couldn't convert output directory to string");
      return "";
   }

   string outputDir(input_buf);

   outputDir = sanitizeOutputDir(outputDir);

   mxFree(input_buf);

   return outputDir;
}

void createOutputDir(string dir)
{
   LPCSTR s = dir.c_str();
   CreateDirectory(s, NULL);
   // TODO: error if this fails??
}

#endif //UTILS_INCLUDED
