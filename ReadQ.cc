#ifndef _VECTOR_H
#include <vector>
#endif
#ifndef _FSTREAM_H
#include <fstream>
#endif
using namespace std;

/***
  NAME 

   ReadQ

   DESCRIPTION 
      This routine reads Quality values from an input file in FASTQ format.

   ARGUMENTS

      is             : input stream object.

   NOTES
      Returns the quality values as a vector of integers.
     
***/

vector <int>& ReadQ(istream & is)
{
  vector<int>* pSeq = new vector<int>();
  string read;
  while (!is.eof())
  {
    getline(is,read);
    if (read[0] == '+')
    {
      getline(is,read);
      break;
    }
  }
  for(unsigned int i=0; i< read.size(); i++)
  {
      pSeq->push_back(read[i]);
  }
  return *pSeq;
}
