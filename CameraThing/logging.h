#ifndef LOGGING_INCLUDED
#define LOGGING_INCLUDED

#include <sstream>

#include "utils.h"

#include "mex.h"

using namespace std;

// change this to false if you don't want this to output log files.
// will probably speed up performance.
bool LOG = true;

void log(string output)
{
   if (!LOG)
      return;
   stringstream log;
   log << "[" << currentTime().c_str() << "] " << output.c_str() << "\n";
   mexPrintf(log.str().c_str());
}


#endif // !LOGGING_INCLUDED

