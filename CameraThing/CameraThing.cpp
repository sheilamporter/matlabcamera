// CameraThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// only used for testCallingFromMatlab, can probably remove
#include <iostream>
#include <fstream>

using namespace std;

void testCallingFromMatlab()
{
   ofstream outfile;
   outfile.open("ohai.txt");
   outfile << "check it out, matlab did the thing!\n";
   outfile.close();
}

int main()
{
   testCallingFromMatlab();
   return 0;
}
