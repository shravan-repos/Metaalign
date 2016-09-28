/*
*    This file is part of HMMoC 1.3, a hidden Markov model compiler.
*    Copyright (C) 2007 by Gerton Lunter, Oxford University.
*
*    HMMoC is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    HMMOC is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with HMMoC; if not, write to the Free Software
*    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifdef __GNUC__
#include <ext/hash_map>
#else
#include <hash_map>
#endif



#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h> 
#include "FullModel_Nov24.h"
#include <stdlib.h>
#include "PrintSeq.cc"
#include <getopt.h>
//#include "Metaalign.h"

// List of Global variables
extern bool enableVerbose;
extern bool enableDebug;
extern bool enable454;
extern vector <int> Seq1NPositions;
extern vector <int> Seq2NPositions;

class Pars {
public:
  double iIns;
  double iDel;
  int    iWidth;
};


using namespace __gnu_cxx;

namespace __gnu_cxx
{
  template<> struct hash< std::string >
  {
    size_t operator()( const std::string& x ) const
    {
      return hash< const char* >()( x.c_str() );
    }
  };
}


const extern string _AlignstateId[];
const extern string _AlignemissionId[];

string EmitSeq1;
string EmitSeq2;

string ProtSeq1;
string ProtSeq2;

hash_map<string, string> Codon2Protein;
hash_map<string, string> AA_1_3;

//
// A struct to hold the alignment parameters, and the bandwidth
//

//
// Accessor classes for the standard and banding algorithms and types
//

class NoBanding {

public:

  typedef AlignDPTable    DPTable;

  //static bfloat Forward(DPTable** ppOutTable,Pars pars,vector<char>& iSequence1,vector<char>& iSequence2) {
  //return ::Forward(ppOutTable,pars.iDel,pars.iDelY,pars.iIns,pars.iInsY,pars.iSigma,iSequence1,iSequence2);

  //}


  static bfloat Viterbi_recurse(DPTable** ppOutTable,Pars pars,vector<char>& iSequence1,vector<char>& iSequence2,vector<double>& iQscores1_s,vector<double>& iQscores1_t,vector<double>& iQscores2_s,vector<double>& iQscores2_t ) {
    return ::Viterbi_recurse(ppOutTable,pars.iDel,pars.iIns,iSequence1,iSequence2,iQscores1_s,iQscores1_t,iQscores2_s,iQscores2_t);
  }

  static Path& Viterbi_trace(DPTable* pInTable,Pars pars,vector<char>& iSequence1,vector<char>& iSequence2,vector<double>& iQscores1_s,vector<double>& iQscores1_t,vector<double>& iQscores2_s,vector<double>& iQscores2_t) {
    return ::Viterbi_trace(pInTable,pars.iDel,pars.iIns,iSequence1,iSequence2,iQscores1_s,iQscores1_t,iQscores2_s,iQscores2_t);
  }


};





//
// Compute a Viterbi alignment
//

template<class T>
//Path& viterbi( Pars& pars, vector<char> iSeq1, vector<char> iSeq2 ) {
Path& viterbi( Pars& pars, vector<char> iSeq1, vector<char> iSeq2, vector<double> qSeq1_s, vector<double> qSeq1_t,vector<double> qSeq2_s, vector<double> qSeq2_t) {

  typename T::DPTable* pViterbiTable;	    
  //T::Viterbi_recurse(&pViterbiTable, pars, iSeq1, iSeq2, qSeq1, qSeq2 );

  bfloat prob = T::Viterbi_recurse(&pViterbiTable, pars, iSeq1, iSeq2, qSeq1_s, qSeq1_t, qSeq2_s,qSeq2_t);          
  Path& path = T::Viterbi_trace(pViterbiTable, pars, iSeq1, iSeq2, qSeq1_s, qSeq1_t, qSeq2_s, qSeq2_t);
  cout<<"Probability: "<<prob<<endl<<endl;
  if (enableDebug == true)
  {         
    cout<<"Viterbi recursion..."<<endl;

    cout<<"Viterbi traceback..." << endl;
    cout<<path;
    cout<<"\n\n";

    cout<<setw(20)<<left<<"State";
    cout<<" ";
    cout<<setw(20)<<left<<"Emission";                    
    cout<<endl; 

  } 

  // Printing the Genomic Sequence.	  
  for (int i=0; i < (int)path.size()-1; i++) 
  {
    int stateId = path.toState(i);     			
    string state = _AlignstateId[stateId];


    if(state.size() >= 9 && state.size() <= 9)
    {
      if (state.compare(4,5,"start") == 0) {
        EmitSeq1 += "|";
        EmitSeq2 += "|";
      } else if (state.compare(6,3,"end") == 0) 
      {
        EmitSeq1 += "|";
        EmitSeq2 += "|";
      }
    } else if(state.size() >= 7 && state.size() <= 7) 
    {
      if (state.compare(4,3,"end") == 0) 
      {
        EmitSeq1 += "|";
        EmitSeq2 += "|";
      }
    } else if(state.size() >= 11 && state.size() <= 11) 
    {
      if (state.compare(6,5,"start") == 0) 
      {
        EmitSeq1 += "|";
        EmitSeq2 += "|";
      }
    }
    string str = pViterbiTable->transitionEmit[path.transitions[i]];
    if (enableDebug == true)
    {  

      cout<<setw(20)<<left<<state;
      cout<<" ";
      cout<<setw(20)<<left<<str;
      cout<<endl;


      //cout<<endl<<state<<"\t"<<str;
    }

    if (str.compare(0,4,"emit") == 0)
    {

      if (str.size() == 6)
      {
        EmitSeq1 += str[4];
        EmitSeq2 += str[5];
      }	  
      else if (str.size() == 12)
      {	  
        EmitSeq1 += str[10];
        EmitSeq2 += str[11];	 

        ProtSeq1 += "*";
        ProtSeq1 += str[10];
        ProtSeq1 += "*";

        ProtSeq2 += "*";
        ProtSeq2 += str[11];
        ProtSeq2 += "*" ;	

      }
      else if (str.size() == 8)
      {
        if (str.compare(4,3,"gap") == 0)
        {
          EmitSeq1 += '.';

          EmitSeq2 += str[7];			

          ProtSeq1 += '.';
          ProtSeq2 += str[7];

        }
        else if (str.compare(4,4,"rndy")==0)
        {
          EmitSeq1 += '.';
          EmitSeq2 += 'X';
        }

        else if (str.compare(5,3,"gap") == 0)
        {

          EmitSeq1 += str[4];
          EmitSeq2 += '.';

          ProtSeq1 += str[4];
          ProtSeq2 += '.' ;
        }	
        else if (str.compare(4,4,"rndx")==0)
        {
          EmitSeq1 += 'X';
          EmitSeq2 += '.';
        }	   
      }	
    }

  }

  fstream f;
  f.open("Codon2Prot.txt", ios::in | ios::out);  
  string RLine1;
  string RLine2;  
  while(!f.eof())
  {
    f>>RLine1;
    f>>RLine2;    
    Codon2Protein[RLine1] = RLine2;
  }
  f.close(); 

  AA_1_3["A"] = "Ala";
  AA_1_3["R"] = "Arg";
  AA_1_3["N"] = "Asn";
  AA_1_3["D"] = "Asp";
  AA_1_3["C"] = "Cys";
  AA_1_3["Q"] = "Gln";
  AA_1_3["E"] = "Glu";
  AA_1_3["G"] = "Gly";
  AA_1_3["H"] = "His";
  AA_1_3["I"] = "Ile";
  AA_1_3["L"] = "Leu";
  AA_1_3["K"] = "Lys";
  AA_1_3["M"] = "Met";
  AA_1_3["F"] = "Phe";
  AA_1_3["P"] = "Pro";
  AA_1_3["S"] = "Ser";
  AA_1_3["T"] = "Thr";
  AA_1_3["W"] = "Trp";
  AA_1_3["Y"] = "Tyr";
  AA_1_3["V"] = "Val";
  AA_1_3["-"] = "---";


  int j = 0;
  for(int i=0;i<ProtSeq1.size();i++)
  { 


    if(!((Codon2Protein[ProtSeq1.substr (i,3)]).empty()))
    {

      string str = Codon2Protein[ProtSeq1.substr (i,3)];

      const char *Prot = str.c_str();

      ProtSeq1.replace(i,3,Prot,1); 
      ProtSeq2.replace(i,3,".",1);

      j = j + 3;
    }
    else if(ProtSeq1.compare(i,3,"XXX") == 0)
    {
      /*
      ProtSeq1[i]   = iSeq1[i];
      ProtSeq1[i+1] = iSeq1[i+1]; 
      ProtSeq1[i+2] = iSeq1[i+2]; 
      */
      string cod = "";

      cod.push_back(iSeq1[j]);
      cod.push_back(iSeq1[j+1]);
      cod.push_back(iSeq1[j+2]);


      string str = Codon2Protein[cod];
      const char *Prot = str.c_str();

      ProtSeq1.replace(i,3,Prot,1); 
      ProtSeq2.replace(i,3,".",1); 

      j = j + 3;

    }
    else
    {
      j = j + 1;
    }
  } 
  j=0;
  for(int i=0;i<ProtSeq2.size();i++)
  { 

    if(!((Codon2Protein[ProtSeq2.substr (i,3)]).empty()))
    {



      string str = Codon2Protein[ProtSeq2.substr (i,3)];

      const char *Prot = str.c_str();

      ProtSeq2.replace(i,3,Prot,1); 
      ProtSeq1.replace(i,3,".",1);

      j = j + 3;
    }
    else if(ProtSeq2.compare(i,3,"XXX") == 0)
    {
      /*
      ProtSeq1[i]   = iSeq1[i];
      ProtSeq1[i+1] = iSeq1[i+1]; 
      ProtSeq1[i+2] = iSeq1[i+2]; 
      */
      string cod = "";

      cod.push_back(iSeq2[j]);
      cod.push_back(iSeq2[j+1]);
      cod.push_back(iSeq2[j+2]);

      string str = Codon2Protein[cod];
      const char *Prot = str.c_str();

      ProtSeq2.replace(i,3,Prot,1); 
      ProtSeq1.replace(i,3,".",1); 

      j = j + 3;

    }
    else
    {
      j = j + 1;
    }
  }



  for(int i=0;i<ProtSeq1.size();i++)
  {
    if(ProtSeq1[i] == '*')
    {
      ProtSeq1.erase(i,1);
      ProtSeq2.erase(i,1);
      i--;
    }
  }   

  delete pViterbiTable;

  return path;
}







//
// Print the Viterbi alignment
//

template<class T>
void report( Path& path, typename T::DPTable* pFW, vector<char>& iSeq1, vector<char>& iSeq2 ) 
{
  //cout<<path;
  int x = 0;
  int y = 0;

  string line1 = "";
  string line2 = "";

  string ProtSeqFromState1 = "";  
  string ProtSeqFromState2 = "";  

  // Loop over all transitions, except the last one (to the end state)
  for (int i=0; i < (int)path.size()-1; i++) 
  {
    int stateId = path.toState(i);     

    string state = _AlignstateId[stateId];	

    /*
    vector <int> emission = path.emission(i);

    for(int k=0;k<emission.size();k++)
    {
    cout<<"\t"<<_AlignemissionId[emission[k]]<<"\t";

    }
    cout<<endl;
    */
    if(state.size() == 9)
    {
      if (state.compare(4,5,"start") == 0) 
      {
        if((state.compare(0,1,"i") == 0))
        {
          string Prot = AA_1_3[Codon2Protein [state.substr(1,3)]];
          ProtSeqFromState1 += Prot[0];
          ProtSeqFromState1 += Prot[1];
          ProtSeqFromState1 += Prot[2];

          ProtSeqFromState2 += "-";
          ProtSeqFromState2 += "-";
          ProtSeqFromState2 += "-";
        }
        if((state.compare(0,1,"d") == 0))
        {
          string Prot = AA_1_3[Codon2Protein [state.substr(1,3)]];
          ProtSeqFromState2 += Prot[0];
          ProtSeqFromState2 += Prot[1];
          ProtSeqFromState2 += Prot[2];

          ProtSeqFromState1 += "-";
          ProtSeqFromState1 += "-";
          ProtSeqFromState1 += "-";
        }
        line1 += "|";
        line2 += "|";

      } else if (state.compare(6,3,"end") == 0) {
        line1 += "|";
        line2 += "|";
      }
    } else if(state.size() >= 7 && state.size() <= 7) {
      if (state.compare(4,3,"end") == 0) {
        line1 += "|";
        line2 += "|";
      }
    } else if(state.size() >= 11 && state.size() <= 11) {
      if (state.compare(6,5,"start") == 0) {
        line1 += "|";
        line2 += "|";
      }
    }

    if(state.size() > 6){
      if ((state.compare(6,2,"M1") == 0) || (state.compare(6,2,"M2") == 0)){
        //if (state == "ainsert") {
        line1 += iSeq1[x++];
        line2 += iSeq2[y++];
      } 
      else if ((state.compare(6,2,"M3") == 0)){
        //if (state == "ainsert") {

        string NextState = _AlignstateId[path.toState(i+1)];

        string AA1 = AA_1_3[NextState.substr(6,1)]; 
        ProtSeqFromState1 += AA1[0];
        ProtSeqFromState1 += AA1[1];
        ProtSeqFromState1 += AA1[2];

        string AA2 = AA_1_3[NextState.substr(7,1)];
        ProtSeqFromState2 += AA2[0];
        ProtSeqFromState2 += AA2[1];
        ProtSeqFromState2 += AA2[2];

        line1 += iSeq1[x++];
        line2 += iSeq2[y++];
        i++;
      }

      else if(state.compare(0,6,"Random") == 0)
      {
        if((state.compare(6,2,"BX") == 0) || (state.compare(6,2,"EX") == 0))
        {
          ProtSeqFromState1 += iSeq1[x];
          //ProtSeqFromState1 += 'X';
          ProtSeqFromState2 += '-';

          line1+= iSeq1[x];
          line2+= '.';
          x++;

        }
        if((state.compare(6,2,"BY") == 0) || (state.compare(6,2,"EY") == 0))
        {	   
          line1+= '.';
          line2+= iSeq2[y];

          ProtSeqFromState1+= '-';
          ProtSeqFromState2+= iSeq2[y];
          //ProtSeqFromState2+= 'X';
          y++;

        }

      }
      else if ((state.compare(6,2,"Ix") == 0) || (state.compare(6,2,"Dy") == 0)) {
        //} else if (state == "ainsert" || state == "cinsert") {
        //cout << state << endl;
        line1 += iSeq1[x++];
        line2 += ".";
        if (state.compare(6,2,"Ix") == 0)
        {
          ProtSeqFromState1 += 'X';
          ProtSeqFromState2 += '.';
        }

      } else if ((state.compare(6,2,"Iy") == 0) || (state.compare(6,2,"Dx") == 0)) {
        //} else if (state == "AACACCIy0" || state == "AACACCIy1" || state == "AACACCIy2" || state == "AACACCIy3"|| state == "AACACCDx1" || state == "AACACCDx2" || state == "AACACCDx3") {
        //cout << state << endl;
        line1 += ".";
        line2 += iSeq2[y++];
        if (state.compare(6,2,"Iy") == 0)
        {
          ProtSeqFromState2 += 'X';
          ProtSeqFromState1 += '.';
        }

      }
    }
    else if (state.size() >= 6 && state.size() <= 7){


      if (state.compare(0,1,"i") == 0) {
        if (state.compare(4,1,"M") == 0) {
          line1 += iSeq1[x++];
          line2 += ".";
        } else if (state.compare(4,2,"Ix") == 0) {
          line1 += iSeq1[x++];
          line2 += ".";
        }
      } else if (state.compare(0,1,"d") == 0) {
        if (state.compare(4,1,"M") == 0) {
          line1 += ".";
          line2 += iSeq2[y++];
        } else if (state.compare(4,2,"Iy") == 0) {
          line1 += ".";
          line2 += iSeq2[y++];
        }
      }
    }


    //double posterior = marginalizedPosterior<T>( state, x, y, pFW, pBW );
    //char postId = "0123456789"[ min( int(posterior*10.0), 9) ];

    //line3 += postId;

  }



  //cout<<endl<<".::Emission Sequence::."<<endl;
  //cout<<EmitSeq1<<endl;
  //cout<<EmitSeq2<<endl;

  //cout<<endl<<".::Read Sequences::."<<endl;
  //cout << line1 << endl;
  //cout << line2 << endl;  



  //cout<<endl<<".::Protein Sequence (Before Change)::."<<endl;
  //cout<<ProtSeqFromState1<<endl;
  //cout<<ProtSeqFromState2<<endl;

  string Q1, Q2;

  for(int i=0;i<ProtSeqFromState2.size()-2;i++)
  { 

    if(!((Codon2Protein[ProtSeqFromState2.substr (i,3)]).empty()))
    {       

      string str = Codon2Protein[ProtSeqFromState2.substr (i,3)];
      cout<<ProtSeqFromState2.substr (i,3)<<"\t"<<str<<endl;
      string AA2 = AA_1_3[str];

      ProtSeqFromState2.replace(i,3,AA2);	   
      ProtSeqFromState1.replace(i,3,"---");            
    }
  }

  for(int i=0;i<ProtSeqFromState1.size()-2;i++)
  { 

    if(!((Codon2Protein[ProtSeqFromState1.substr (i,3)]).empty()))
    {
      string str = Codon2Protein[ProtSeqFromState1.substr (i,3)];
      string AA1 = AA_1_3[str];

      const char *Prot = str.c_str();

      ProtSeqFromState1.replace(i,3,AA1);	   
      ProtSeqFromState2.replace(i,3,"---"); 
    }
  }


  //cout<<endl<<"Printing After Change---"<<endl;
  PrintSeq (EmitSeq1, EmitSeq2, line1, line2, ProtSeqFromState1, ProtSeqFromState2, Q1, Q2, Seq1NPositions,Seq2NPositions,60);



  /*
  for(int i=1;i<ProtSeqFromState1.size()-1;i++)
  {
  if ((ProtSeqFromState1.compare(i-1,1,"*") == 0) && (ProtSeqFromState1.compare(i+1,1,"*") == 0))
  {			

  }
  else
  {
  if ((ProtSeqFromState1.compare(i,1,"*") != 0))
  {
  ProtSeqFromState1[i] = 'X';
  ProtSeqFromState2[i] = 'X';
  }
  }



  }



  ProtSeqFromState1.erase(0,1);
  ProtSeqFromState2.erase(0,1); 
  ProtSeqFromState1.erase(ProtSeqFromState1.size()-1,1);
  ProtSeqFromState2.erase(ProtSeqFromState2.size()-1,1);	

  for(int i=0;i<ProtSeq1.size();i++)
  {
  if(ProtSeqFromState1[i] == '*' || ProtSeqFromState1[i] == 'X' || ProtSeqFromState2[i] == 'X')
  {
  ProtSeqFromState1.erase(i,1);
  ProtSeqFromState2.erase(i,1);
  i--;
  }
  }
  */

  //  cout<<endl<<".::Protein Sequence::."<<endl;
  //cout<<ProtSeqFromState1<<endl;
  //cout<<ProtSeqFromState2<<endl;



  //cout<<endl<<ProtSeq1<<endl<<endl;
  //cout<<EmitSeq1<<endl<<endl;
  //cout << line1 << endl<<endl;
  //cout << line2 << endl<<endl;  
  //cout<<EmitSeq2<<endl<<endl;
  //cout<<ProtSeq2<<endl<<endl;



}



template<class T>
void execute( Pars pars, vector<char>& iSeq1, vector<char>& iSeq2, vector<double> qSeq1_s, vector<double> qSeq1_t,vector<double> qSeq2_s, vector<double> qSeq2_t) {

  // estimate iDelta and iR using Baum-Welch training

  // calculate the Viterbi path


  Path& path = viterbi<T>(pars, iSeq1, iSeq2, qSeq1_s, qSeq1_t, qSeq2_s, qSeq2_t);


  //cout << "Backward..." << endl;
  //T::Backward (&pBW, pars, iSeq1, iSeq2 );

  // report the results
  cout <<endl<< "Alignment:" << endl;
  report<T>( path, NULL, iSeq1, iSeq2 );

  // finished

  //delete pBW;
}

