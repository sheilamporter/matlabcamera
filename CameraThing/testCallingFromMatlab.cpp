/*=================================================================
* mexfunction.c
*
* This example demonstrates how to use mexFunction.  It returns
* the number of elements for each input argument, providing the
* function is called with the same number of output arguments
* as input arguments.

* This is a MEX-file for MATLAB.
* Copyright 1984-2011 The MathWorks, Inc.
* All rights reserved.
*=================================================================*/

#include <fstream>
#include <iostream>

#include "mex.h"

using namespace std;

void testCallingFromMatlab(string filename, string contents)
{
   ofstream outfile;
   outfile.open(filename);
   outfile << contents.c_str() << '\n';
   outfile.close();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   /*if (!mxIsChar(prhs[0]))
   {
   mexPrintf("filename (first argument) needs to be a string");
   return;
   }

   if (!mxIsChar(prhs[1]))
   {
   mexPrintf("file contents (second argument) needs to be a string");
   return;
   }

   string filename = mxArrayToString(prhs[0]);
   string contents = mxArrayToString(prhs[1]);*/

   testCallingFromMatlab("ohai.txt", "sheila is so good at computers");

   // specify output if it's there
   /*if (nlhs == 1)
   {
   plhs[0] = "heck yeah";
   }*/
}
