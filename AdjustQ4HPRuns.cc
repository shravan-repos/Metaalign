#ifndef _IOSTREAM_H
#include <iostream>
#endif
#ifndef _VECTOR_H
#include <vector>
#endif
using namespace std;

/***
  NAME 

   AdjustQ4HPRuns

   DESCRIPTION 
      This routine adjusts the input quality values to account 
      for degradation associated with homopolymer runs.

   ARGUMENTS

      iSeq1          : Gene sequence.
      qSeq1          : Quality values.
      QParam         : Rate at which the quality value needs to be degraded.
                       default: 1.0
      QMin           : Minimum quality value, no reduction beyond this value.
                       default: 5.0

   NOTES
      Also refer to ReadParams to provide QParam, QMin as inputs.
***/


vector <int>& AdjustQ4HPRuns ( vector<char>& iSeq1, 
                               vector<int> qSeq1, 
                               int QParam = 1, 
                               int QMin = 5)
{
  vector<int>* qSeq = new vector <int> ();
  
  char HomoPolymerStart = 'X';
  
  int HP_Start = 0;
  int HP_End   = 0;
  
  for(unsigned int i=0; i <= iSeq1.size(); i++)
    {      
      if (HomoPolymerStart == 'X')
	{
	  HomoPolymerStart = iSeq1[i];
	  HP_Start = i;
	}
      else
	{
	  if (i == iSeq1.size())
	    {
	      HomoPolymerStart = 'X';
	      i--;
	      HP_End = i;
	    }	  
	  else if (iSeq1[i] != HomoPolymerStart)
	    {
	      HomoPolymerStart = 'X';
	      i--;
	      HP_End = i;
	    }
	  else
	    {
	      
	    }
	}
      
      for(int j=0; j<= (HP_End-HP_Start); j++)
	{
	  qSeq1[HP_Start+j] = (qSeq1[HP_Start+j] - (QParam*j));
	  if (qSeq1[HP_Start+j] < QMin)
	    {
	      qSeq1[HP_Start+j] = QMin;
	    }
	}
    }
  
  for(unsigned int i=0; i < iSeq1.size(); i++)
    {
      qSeq->push_back(qSeq1[i]);    
    }
  
  return *qSeq;
}
