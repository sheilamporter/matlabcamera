// CameraThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// only used for testCallingFromMatlab, can probably remove
#include <iostream>
#include <fstream>

using namespace std;

void testCallingFromMatlab(string filename, string input)
{
   ofstream outfile;
   outfile.open(filename);
   outfile << input.c_str() << '\n';
   outfile.close();
}

int main()
{
   testCallingFromMatlab("ohai.txt", "check it out, matlab did the thing!");
   return 0;
}
