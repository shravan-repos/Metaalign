#ifndef _VECTOR_H
#include <vector>
#endif
using namespace std;

/***
  NAME 

   HandleNPositions

   DESCRIPTION 
      This routine handles missing nucleotide positions in sequence.
      It subsitutes the position with 'A' and sets low quality value.

   ARGUMENTS

      iSeq           : Gene sequence.
      qSeq           : Quality values.
      SeqNPositions  : List of positions with 'N'

***/


void HandleNPositions ( vector<char>& iSeq,
                        vector<int> & qSeq,
                        vector<int> & SeqNPositions)
{
  for(unsigned i = 0; i < iSeq.size(); i++)
  { 
    if (iSeq[i] == 'N')
    {
      SeqNPositions.push_back(i);

      qSeq[i] = 2;

      iSeq[i] = 'A';
    }
  }
}

