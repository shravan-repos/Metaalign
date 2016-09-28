#include "Align.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

void split(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
}



int oSize;
string* GetStateID(string file)
{

 fstream f;
 f.open(file.c_str(), ios::in); 
 string states;
 while (!f.eof())
 {   
   f>>states;
 }
 f.close();
 vector<string> state;
 split(states, ',', state);
 
 oSize = state.size();
 string* buffer = new string [oSize];  
 for ( int i=0; i < oSize; i++ ) 
 { 
   string str = state[i];
   str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
   buffer[i] = str; 
 } 
 cout<<file<<" "<<oSize<<endl; 
 return buffer;
}


string* GetAlignOutputID()
{
 string* buffer = new string[2];
 buffer[0] = "sequence1";
 buffer[1] = "sequence2";
 return buffer;
}


string* Align::_AlignstateId      = GetStateID("_AlignstateId.txt");
string* Align::_AlignemissionId   = GetStateID("_AlignemissionId.txt");
string* Align::_AligntransitionId = GetStateID("_AligntransitionId.txt");
string* Align::_AligntransF       = GetStateID("_AligntransF.txt");
string* Align::_AligntransT       = GetStateID("_AligntransT.txt");
string* Align::_AligntransP       = GetStateID("_AligntransP.txt");
string* Align::_AligntransE       = GetStateID("_AligntransE.txt");
string* Align::_AlignoutputId     = GetAlignOutputID();
string  Align::_Alignempty;

int Align::_AlignstateNum=5849;
int Align::_AlignemitNum=558;
int Align::_AligntransNum=19583;
int Align::_AlignoutputNum=2;

Align::Align()
{

}

Align::~Align()
{
    if (_AlignstateId)
    {
        delete [] _AlignstateId;
        _AlignstateId = NULL;
    }

    if (_AlignemissionId)
    {
        delete [] _AlignemissionId;
        _AlignemissionId = NULL;
    }

    if (_AligntransitionId)
    {
        delete [] _AligntransitionId;
        _AligntransitionId = NULL;
    }

    if (_AligntransF)
    {
        delete [] _AligntransF;
        _AligntransF = NULL;
    }

    if (_AligntransT)
    {
        delete [] _AligntransT;
        _AligntransT = NULL;
    }

    if (_AligntransP)
    {
        delete [] _AligntransP;
        _AligntransP = NULL;
    }

    if (_AligntransE)
    {
        delete [] _AligntransE;
        _AligntransE = NULL;
    }

    if (_AlignoutputId)
    {
        delete [] _AlignoutputId;
        _AlignoutputId = NULL;
    }
}

string* Align::Get_AlignstateId()
{
    return _AlignstateId;
}
string* Align::Get_AlignemissionId()
{
    return _AlignemissionId;
}
string* Align::Get_AligntransitionId()
{
    return _AligntransitionId;
}
string* Align::Get_AligntransF()
{
    return _AligntransF;
}
string* Align::Get_AligntransT()
{
    return _AligntransT;
}
string* Align::Get_AligntransP()
{
    return _AligntransP;
}
string* Align::Get_AligntransE()
{
    return _AligntransE;
}
string* Align::Get_AlignoutputId()
{
    return _AlignoutputId;
}
string Align::Get_Alignempty()
{
    return _Alignempty;
}

string& Align::Get_AlignstateId( int i )
{
    return _AlignstateId[i];
}
string& Align::Get_AlignemissionId( int i )
{
    return _AlignemissionId[i];
}
string& Align::Get_AligntransitionId( int i )
{
    return _AligntransitionId[i];
}
string& Align::Get_AligntransF( int i )
{
    return _AligntransF[i];
}
string& Align::Get_AligntransT( int i )
{
    return _AligntransT[i];
}
string& Align::Get_AligntransP( int i )
{
    return _AligntransP[i];
}
string& Align::Get_AligntransE( int i )
{
    return _AligntransE[i];
}
string& Align::Get_AlignoutputId( int i )
{
    return _AlignoutputId[i];
}

int Align::Get_AlignstateNum()
{
    return _AlignstateNum;
}
int Align::Get_AlignemitNum()
{
    return _AlignemitNum;
}
int Align::Get_AligntransNum()
{
    return _AligntransNum;
}
int Align::Get_AlignoutputNum()
{
    return _AlignoutputNum;
}

/*
int main()
{

 {
  string* buffer = Align::Get_AlignstateId();
  for ( int i=0 ; i < 5849; ++i )
  {
   assert(buffer[i] == Align::Get_AlignstateId(i) );
  }
 }

 {
  string* buffer = Align::Get_AlignemissionId();
  for ( int i=0 ; i < 558; ++i )
  {
   assert(buffer[i] == Align::Get_AlignemissionId(i) );
  }
 }

 {
  string* buffer = Align::Get_AligntransitionId();
  for ( int i=0 ; i < 19583; ++i )
  {
   assert(buffer[i] == Align::Get_AligntransitionId(i) );
  }
 }

 {
  string* buffer = Align::Get_AligntransF();
  for ( int i=0 ; i < 19583; ++i )
  {
   assert(buffer[i] == Align::Get_AligntransF(i) );
  }
 }

 {
  string* buffer = Align::Get_AligntransT();
  for ( int i=0 ; i < 19583; ++i )
  {
   assert(buffer[i] == Align::Get_AligntransT(i) );
  }
 }

 {
  string* buffer = Align::Get_AligntransP();
  for ( int i=0 ; i < 19583; ++i )
  {
   assert(buffer[i] == Align::Get_AligntransP(i) );
  }
 }

 {
  string* buffer = Align::Get_AligntransE();
  for ( int i=0 ; i < 19583; ++i )
  {
   assert(buffer[i] == Align::Get_AligntransE(i) );
  }
 }
 return 0;
}
*/


