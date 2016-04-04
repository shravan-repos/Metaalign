#ifndef _VECTOR_H
#include <vector>
#endif
#ifndef _FSTREAM_H
#include <fstream>
#endif
using namespace std;

/***
  NAME 

   ReadSeq

   DESCRIPTION 
      This routine reads a sequence from an input file in FASTQ format.

   ARGUMENTS

      is             : input stream object.
      SeqName        : Contains the name of Sequence read from file.

   NOTES
      Returns the sequence as a vector of charecters.
     
***/


vector <char>& ReadSeq(istream & is, string& SeqName)
{
  vector<char>* pSeq = new vector<char>();

  string read;
  while (!is.eof())
  {
    getline(is,read);
    if (read[0] == '@')
    {
      read.erase(0,1);
      SeqName = read;
      getline(is,read);
      break;
    }
  }
  for(unsigned int i=0; i< read.size(); i++)
  {
       if (read[i] >= 'a' && read[i] <= 'z')
       {
         read[i] &= 0xDF;  // make upper case
       }
       if (read[i] == 'A' || read[i] == 'C' || read[i] == 'G' || read[i] == 'T' || read[i] == 'N')
       {
          pSeq->push_back(read[i]);         
       }
  }
  return *pSeq;
}
