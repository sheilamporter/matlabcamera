// CameraThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

bool LOG = true;
ofstream logfile;

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
#pragma warning(suppress : 4996)
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%F.%X", &tstruct);
   return buf;
}

void setupLog()
{
   if (!LOG)
      return;
   //cout << ("cameralog_" + currentTime() + ".txt").c_str();
   string time = currentTime();
   replace(time.begin(), time.end(), ':', '.');
   logfile.open("cameralog_" + time + ".txt");
   //logfile.open("cameralog.txt");
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

void startupCamera()
{
   setupLog();
   log("starting up camera");
}

void captureImage()
{
   log("capturing image");
}

void teardownCamera()
{
   log("tearing down camera");
   teardownLog();
}

void testCallingFromMatlab(string filename, string input)
{
   ofstream outfile;
   outfile.open(filename);
   outfile << input.c_str() << '\n';
   outfile.close();
}

int main()
{
   //testCallingFromMatlab("ohai.txt", "check it out, matlab did the thing!");
   startupCamera();
   captureImage();
   teardownCamera();
   return 0;
}
