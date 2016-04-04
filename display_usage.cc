#ifndef _IOSTREAM_H
#include <iostream>
#endif

using namespace std;
/***
  NAME 

   display_usage

   DESCRIPTION 
      This routine displays the help messages.

   ARGUMENTS
   
      none
***/

void display_usage()
{

 cout<<"\nUSAGE:";

 cout<<"\n./Metaalign [-h] [--help] [-d] [--debug] [-q] [--query] [-s] [--subject] [--e454] [-4]";

 cout<<"\nArguments";
 cout<<"\n -q <File_In>";
 cout<<"\n    Input file name (*FASTQ format*)";
 cout<<"\n -s <File_In>";
 cout<<"\n    Input file name (*FASTQ format*)";
 cout<<"\nOPTIONAL ARGUMENTS";
 cout<<"\n -h";
 cout<<"\n    Print USAGE and DESCRIPTION;  ignore other arguments";
 cout<<"\n -d";
 cout<<"\n    Debug mode (includes state transition/Probability)";
 cout<<"\n -4";
 cout<<"\n    Enable 454 mode";
 cout<<"\n";

}
