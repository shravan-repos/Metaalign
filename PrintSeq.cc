#ifndef _STRING_H
#include <string>
#endif
#ifndef _IOSTREAM_H
#include <iostream>
#endif
#include <vector>
using namespace std;

/***
  NAME 

   PrintSeq

   DESCRIPTION 
      This routine prints the alignment in 6 Track format.

   ARGUMENTS

      EmS1           : subject gene sequence.
      EmS2           : query gene sequence.
      line1          : subject read sequence.
      line2          : query read sequence.
      Prot1          : subject protein sequence.
      Prot2          : query protein sequence.
      Q1             : subject quality values.
      Q2             : query quality values.
      Seq1NPositions : list of subject N positions.
      Seq2NPositions : list of query N positions.
      indent         : number of nucleotides per line.

   NOTES
      Can be made 8 track format using Q1, Q2. Not 
      done as a part of this release.
***/


void PrintSeq(string EmS1, 
              string EmS2, 
              string line1, 
              string line2, 
              string Prot1, 
              string Prot2, 
              string Q1, 
              string Q2, 
              vector<int> Seq1NPositions,
              vector<int> Seq2NPositions,
              int    indent=60)
{
  unsigned int i = 0, j = 0;
  unsigned int Pos = line1.find_first_of('|');
  unsigned int z = indent;
  
  while (Pos <= line2.size())
    {
      line1.erase(Pos,1);
      Pos = line1.find_first_of('|');
    }
  
  Pos = line2.find_first_of('|');

  while (Pos <= line2.size())
    {
      line2.erase(Pos,1);
      Pos = line2.find_first_of('|');
    }
  
  Pos = EmS1.find_first_of('|');

  while (Pos <= EmS1.size())
    {
      EmS1.erase(Pos,1);
      Pos = EmS1.find_first_of('|');
    }
  
  Pos = EmS2.find_first_of('|');

  while (Pos <= EmS2.size())
    {
      EmS2.erase(Pos,1);
      Pos = EmS2.find_first_of('|');
    }
  
  for(i=0; i < Seq1NPositions.size(); i++)
    {
      line1[Seq1NPositions[i]] = 'N';
    }
  
  for(i=0; i < Seq2NPositions.size(); i++)
    {
      line2[Seq2NPositions[i]] = 'N';
    }
  
  cout<<endl;
  
  for (j=0; j < line2.size(); j+=z)
    {
      cout<<"SUB_READ"<<"\t";
      for(i = j; i < j+z && i < line1.size(); i++)
        {
          cout<<line1[i];
        }
      cout<<endl<<"SUB_GENS"<<"\t";
      for(i = j; i < j+z && i < EmS1.size(); i++)
        {
          cout<<EmS1[i];
        }
      cout<<endl<<"SUB_PROT"<<"\t";
      for(i = j; i < j+z && i < Prot1.size(); i++)
        {
          cout<<Prot1[i];
        }
      cout<<endl<<"QUE_PROT"<<"\t";
      for(i = j; i < j+z && i < Prot2.size(); i++)
        {
          cout<<Prot2[i];
        }
      cout<<endl<<"QUE_GENS"<<"\t";
      for(i = j; i < j+z && i < EmS2.size(); i++)
        {
          cout<<EmS2[i];
        }
      cout<<endl<<"QUE_READ"<<"\t";
      for(i = j; i < j+z && i < line2.size() ; i++)
        {
          cout<<line2[i];
        }
      cout<<endl<<endl;
    }      
}

