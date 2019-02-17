#ifndef LOGGING_INCLUDED
#define LOGGING_INCLUDED

#include <sstream>

#include "utils.h"

#include "mex.h"

using namespace std;

// change this to false if you don't want this to output log files.
// will probably speed up performance.
bool LOG = true;

void writeToLog(string output)
{
   stringstream log;
   log << "[camera " << currentTime().c_str() << "] " << output.c_str() << "\n";
   mexPrintf(log.str().c_str());
}

void log(string output)
{
   if (!LOG)
      return;
   writeToLog(output);
}

void error(string output)
{
   writeToLog("ERROR: " + output);
}

#endif // !LOGGING_INCLUDED

