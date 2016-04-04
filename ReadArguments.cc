#ifndef _FSTREAM_H
#include <fstream>
#endif
#ifndef _GETOPT_H
#include <getopt.h>
#endif

#include "globalArgs_t.h"

using namespace std;

/***
    NAME 

    ReadArguments

    DESCRIPTION 
    This routine reads command line arguments.

    ARGUMENTS

    argc       : command line arguments.
      argv       : command line arguments.
      globalArgs : Returns the set of command line options.
      

      NOTES      
      Makes use of getopt
***/

static const struct option longOpts[] =
  {
    { "subject", required_argument, NULL, 's' },
    { "query"  , required_argument, NULL, 'q' },
    { "verbose", no_argument,       NULL, 'v' },
    { "help"   , no_argument,       NULL, 'h' },
    { "debug"  , no_argument,       NULL, 'd' },
    { "e454"   , no_argument,       NULL, '4' },
    {  NULL,     no_argument,       NULL,  0  }
  };


void ReadArguments (int argc, char** argv, globalArgs_t&  globalArgs)
{  
  globalArgs.verbosity = 0;
  globalArgs.help      = 0;
  globalArgs.debug     = 0;
  globalArgs.e454      = 0;  
  
  static const char *optString = "s:q:vhd4";
  int longIndex;
  int opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
  while( opt != -1 )
    {
      switch( opt )
        {
	case 's':
	  globalArgs.subject = optarg;
	  break;
	  
	case 'q':
	  globalArgs.query = optarg;
	  break;
	  
	case 'v':
	  globalArgs.verbosity = 1; // true
	  break;
	  
	case 'h':
	  globalArgs.help = 1;  // true
	  break;
	case 'd':
	  globalArgs.debug = 1;
	  break;
	case '4':
	  globalArgs.e454 = 1;
	  
	case '0':
	  break;
	  
	default:
	  break;
        }
      opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    } 
} 

