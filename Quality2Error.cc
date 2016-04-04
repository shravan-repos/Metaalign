#ifndef _VECTOR_H
#include <vector>
#endif
#include <math.h>
using namespace std;

/***
  NAME 

   Quality2Error

   DESCRIPTION 
      This routine translates between quality value and error.

   ARGUMENTS

      qSeq           : Quality values.
      iErr           : Error Values

***/

void Quality2Error ( vector<int>    & qSeq,
                     vector<double> & iErr)
{
for (unsigned int i=0; i < qSeq.size(); i++) 
{
  iErr.push_back(pow(10., -(double)qSeq[i]/10.));
}
}

