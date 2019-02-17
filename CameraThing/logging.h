#ifndef LOGGING_INCLUDED
#define LOGGING_INCLUDED

#include <fstream>
#include <iostream>

#include "utils.h"

using namespace std;

// change this to false if you don't want this to output log files.
// will probably speed up performance.
bool LOG = true;
ofstream logfile;

void setupLog()
{
   if (!LOG)
      return;
   logfile.open(outputDir() + "cameralog.txt");
}

void teardownLog()
{
   if (!LOG)
      return;
   logfile.close();
}

void log(string output)
{
   if (!LOG)
      return;
   logfile << "[" << currentTime().c_str() << "] " << output.c_str() << "\n";
}


#endif // !LOGGING_INCLUDED

