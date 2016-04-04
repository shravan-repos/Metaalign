#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "globalArgs_t.h"
using namespace std;

/***
 List of Function declarations
***/


vector <int>& AdjustQ4HPRuns ( vector<char>& iSeq1,
                               vector<int> qSeq1,
                               int QParam = 1,
                               int QMin = 5);
void display_usage();

void PrintSeq(string EmS1,
              string EmS2,
              string line1,
              string line2,
              string Prot1,
              string Prot2,
              string Q1,
              string Q2,
              vector <int> Seq1NPositions,
              vector <int> Seq2NPositions,
              int    indent=60);

void ReadArguments (int argc, char** argv, globalArgs_t&  globalArgs);


vector <int>& ReadQ(istream & is);


void HandleNPositions ( vector<char>& iSeq,
                        vector<int> & qSeq,
                        vector<int> & SeqNPositions);



void Quality2Error ( vector<int>    & qSeq,
                     vector<double> & iErr);


void ReadParams (int& QParam, int& QMin, int& Q_N);


vector <char>& ReadSeq(istream & is, string& SeqName);
 






