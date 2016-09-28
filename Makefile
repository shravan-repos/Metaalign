#    This file is part of Metalign, tool for pairwise alignment of low quality reads.
#    Copyright (C) 2010 Degui Zhi, Shravan, University of Alabama at Birmingham.

AdjustQ4HPRuns.o: 
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall AdjustQ4HPRuns.cc
algebras.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall algebras.cc
display_usage.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall display_usage.cc
PrintSeq.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall PrintSeq.cc
ReadParams.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall ReadParams.cc
ReadSeq.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall ReadSeq.cc
ReadQ.o  :
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall ReadQ.cc
ReadArguments.o: 
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall ReadArguments.cc
HandleNPositions.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall HandleNPositions.cc       
Quality2Error.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall Quality2Error.cc
Execute.o: 
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall Execute.cc
Align.o:
	g++ -c -O3 -ffast-math -finline-limit=10000 -Wall Align.cpp
FullModel_Nov24.o:
	g++ -c -v -O3 -ffast-math -finline-limit=10000 -W -Wall FullModel_Nov24_reverse.cc FullModel_Nov24.h
Metaalign: AdjustQ4HPRuns.o HandleNPositions.o  ReadArguments.o display_usage.o ReadParams.o ReadSeq.o ReadQ.o Quality2Error.o Execute.o Align.o FullModel_Nov24.o
	g++ -o $@ -lstdc++ -O3 -ffast-math -finline-limit=10000 -Wall Metaalign.cc AdjustQ4HPRuns.o HandleNPositions.o  ReadArguments.o display_usage.o ReadParams.o ReadSeq.o ReadQ.o Quality2Error.o Metaalign.h Execute.o Align.o FullModel_Nov24.o FullModel_Nov24.h 
clean: 
	rm *.o
