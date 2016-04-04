#include "Metaalign.h"

class Pars {
public:
  double iIns;
  double iDel;
  int    iWidth;
};

extern bool enableVerbose ;
extern bool enableDebug   ;
extern bool enable454     ;

extern vector <int> Seq1NPositions;
extern vector <int> Seq2NPositions;

extern Pars pars;

extern globalArgs_t globalArgs;

int main(int argc, char** argv) 
{
  // set initial parameters
 
  pars.iDel   = 0.3;
  pars.iIns   = 0.3;
  pars.iWidth = 0;

  string Seq1Name;
  string Seq2Name;
  
  vector<double> iErr1_s;
  vector<double> iErr2_s;
  
  vector<double> iErr1_t;
  vector<double> iErr2_t;
  
  int QParam, QMin, Q_N;   
  
  if (argc == 1)
    {
      display_usage();
      return 0;
    }  
  
  ReadArguments (argc, argv, globalArgs);
  
  if (globalArgs.help == 1)
    {
      display_usage();
      cout<<endl;
      return 0;
    }  
  if (globalArgs.verbosity == 1)
    {
      enableVerbose = true; 
    }
  if (globalArgs.debug == 1)
    {      
      enableDebug = true;
    }
  if (globalArgs.e454 == 1)
    {     
      enable454 = true;
    }   
  
  if (globalArgs.subject == NULL || globalArgs.query == NULL)
    {
      cout<<"Invalid Sequence files .. terminating";
      return 1;
    }
  
  // subject sequence
  std::ifstream ifsIo(globalArgs.subject);
  vector<char>& iSeq1   = ReadSeq(ifsIo,Seq1Name);
  vector<int> & qSeq1_s = ReadQ  (ifsIo);
  ifsIo.close();

  if (iSeq1.size() == 0 || qSeq1_s.size() == 0 || iSeq1.size() != qSeq1_s.size())
    {
      cout<<"Error reading subject Sequence. Terminating"<<endl;
      return 1;
    }
  
  //Query Sequence
  std::ifstream ifsIp(globalArgs.query);
  vector<char>& iSeq2   = ReadSeq(ifsIp, Seq2Name);
  vector<int> & qSeq2_s = ReadQ(ifsIp);
  ifsIo.close();
  
  if (iSeq2.size() == 0 || qSeq2_s.size() == 0 || iSeq2.size() != qSeq2_s.size())
    {
      cout<<"Error reading Query Sequence. Terminating"<<endl;
      return 1;
    }  
  
  cout<< "Read sequences\n" <<Seq1Name<<" Length: " <<iSeq1.size() << "\n" 
      <<Seq2Name<<" Length: " <<iSeq2.size() << ".";
  
  cout<<endl<<"Executing..."<<endl;
  
  
  HandleNPositions (iSeq1,qSeq1_s,Seq1NPositions);
  HandleNPositions (iSeq2,qSeq2_s,Seq2NPositions);  
  
  Quality2Error(qSeq1_s,iErr1_s);
  Quality2Error(qSeq2_s,iErr2_s); 
    
    
  /* 454 Homopolymer runs */  
  ReadParams (QParam,QMin,Q_N);
  
  vector<int>& qSeq1_t =  AdjustQ4HPRuns(iSeq1, qSeq1_s, QParam, QMin);
  vector<int>& qSeq2_t =  AdjustQ4HPRuns(iSeq2, qSeq2_s, QParam, QMin);  
  
  Quality2Error(qSeq1_t,iErr1_t);
  Quality2Error(qSeq2_t,iErr2_t)  ;
    
  //execute<NoBanding>( pars, iSeq1, iSeq2, iErr1_s, iErr1_t, iErr2_s, iErr2_t);
    
}
