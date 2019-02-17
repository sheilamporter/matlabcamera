#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <algorithm>
#include <string>
#include <time.h>
#include <Windows.h>

using namespace std;

string dir = "";

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


void setupOutput()
{
   // create output folder
   string time = currentTime();
   replace(time.begin(), time.end(), ':', '.');
   string outputDir = "camerarun_" + time + "\\";
   // WINDOWS WHY ARE YOU LIKE THIS
   //std::wstring stemp = std::wstring(outputDir.begin(), outputDir.end());
   //LPCWSTR sw = stemp.c_str();
   LPCSTR s = outputDir.c_str();
   CreateDirectory(s, NULL);
}

#endif //UTILS_INCLUDED
