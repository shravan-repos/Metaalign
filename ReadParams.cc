#ifndef _FSTREAM_H
#include <fstream>
#endif
using namespace std;

/***
  NAME 

   ReadParams

   DESCRIPTION 
      This routine reads input parameters for 454 Homo polymer runs.

   ARGUMENTS

      QParam         : Rate at which the quality value needs to be degraded.
      QMin           : Minimum quality value, no reduction beyond this value.
      Q_N            : Order (Linear, quadratic) of reduction.
                       Not supported in this release.

   NOTES
      Supports linear variant only.
      This values are read in from a file 'params.txt'.
***/


void ReadParams (int& QParam, int& QMin, int& Q_N)
{
  fstream f;

  string Param;
  int value;

  QParam = 0;
  QMin   = 2;
  Q_N    = 2;

  f.open("params.txt", ios::in);
  while(!f.eof())
  {
    f >> Param;
    f >> value;

    if (Param.compare("QParam") == 0)
    {
       QParam = value;
    }
    else if (Param.compare("QMin") == 0)
    {
       QMin = value;
    }
    else if (Param.compare("Q_N") == 0)
    {
       Q_N = value;
    }
  }

  f.close();
}
