#!/usr/bin/perl
$ccfile = shift;
open(FI, $ccfile);

my %CFU;

$record = <FI>;

while ($record = <FI>)
{
  @words = split(/ /, $record);  
  $CFU{@words[0]} = @words[1];
}


close (FI);

$ccfile = shift;
open(FI, $ccfile);
$record = <FI>;
$record = <FI>;
$record = <FI>;
$record = <FI>;

@ProtName = ('A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V');

my %PMatS;

$i = 0;
while ($record = <FI>)
{  
    @words = split(/ /, $record);

    for($j=0;$j<=$i;$j++)
    {
      $P1 = @ProtName[$i];

      $P2 = @ProtName[$j];    

      $PMatS {$P1.$P2} = @words[$j];      
    }

    $i++;  
}

#print %PMatS;

# List of coding Codons
#@ArrCMU = (TTT,TCT,TAT,TGT,TTC,TCC,TAC,TGC,TTA,TCA,TTG,TCG,TGG,CTT,CCT,CAT,CGT,CTC,CCC,CAC,CGC,CTA,CCA,CAA,
#           CGA,CTG,CCG,CAG,CGG,ATT,ACT,AAT,AGT,ATC,ACC,AAC,AGC,ATA,ACA,AAA,AGA,ATG,ACG,AAG,AGG,GTT,GCT,GAT,
#           GGT,GTC,GCC,GAC,GGC,GTA,GCA,GAA,GGA,GTG,GCG,GAG,GGG);

#@ArrCMU = (TTT,TTC,TTA,TTG);

@CMUBlock = (TT,CT,AT,GT,TC,CC,AC,GC,CA,AA,GA,CG,AG,GG,TA,TG);

#@CMUBlock = (TT);

# Special cases: TAA/TAG/TGA (Stop Codons)

#@CMUBlock = (TA,TT,TG);
@NucBlock = (A,G,T,C);



%CUtoProt = (
"ATT",'I', 
"ATC",'I', 
"ATA",'I',

"CTT",'L', 
"CTC",'L', 
"CTA",'L', 
"CTG",'L', 
"TTA",'L', 
"TTG",'L',

"GTT",'V', 
"GTC",'V', 
"GTA",'V', 
"GTG",'V',

"TTT",'F', 
"TTC",'F',

"ATG",'M',

"TGT",'C', 
"TGC",'C',

"GCT",'A', 
"GCC",'A', 
"GCA",'A', 
"GCG",'A', 

"GGT",'G', 
"GGC",'G',
"GGA",'G', 
"GGG",'G', 

"CCT",'P', 
"CCC",'P', 
"CCA",'P', 
"CCG",'P',

"ACT",'T', 
"ACC",'T', 
"ACA",'T', 
"ACG",'T',

"TCT",'S', 
"TCC",'S', 
"TCA",'S', 
"TCG",'S', 
"AGT",'S', 
"AGC",'S',

"TAT",'Y',
"TAC",'Y',

"TGG",'W',

"CAA",'Q',
"CAG",'Q',

"AAT",'N',
"AAC",'N',

"CAT",'H', 
"CAC",'H',

"GAA",'E', 
"GAG",'E',

"GAT",'D', 
"GAC",'D',

"AAA",'K', 
"AAG",'K',

"CGT",'R', 
"CGC",'R', 
"CGA",'R', 
"CGG",'R', 
"AGA",'R', 
"AGG",'R');

open(MACRO,'>Macro.xml');
open(STATE,'>State.xml');
open(PROB, '>MatProb.xml');
open(TPROB, '>TranProb.xml');
open(EmitProb, '>EmitCode.xml');
open(TRANS, '>Trans.xml');

for($p=0;$p<@CMUBlock;$p++)
{
for($i=0;$i<@CMUBlock;$i++)
{ 
  $name = @CMUBlock[$p].'X'. @CMUBlock[$i].'X';
  
  $CMU1 = @CMUBlock[$p];
  $CMU2 = @CMUBlock[$i];
  
  @CMU1 = split(//,$CMU1);
  @CMU2 = split(//,$CMU2);
  
  print MACRO " <expand macro=\"macro1\"><slot var=\"_cls_\" value=\"$name\"/></expand>\n";
  
  print STATE "  <state id=\"$name","start\" emission=\"empty\"/>\n";
  print STATE "  <state id=\"$name","Dx1\" emission=\"emitgap", "@CMU2[0]\"/>\n";
  print STATE "  <state id=\"$name","Dx2\" emission=\"emitgap", "@CMU2[1]\"/>\n";

  print STATE "  <state id=\"$name","Ix0\" emission=\"emitrndx\"/>\n";
  print STATE "  <state id=\"$name","Ix1\" emission=\"emitrndx\"/>\n";
  print STATE "  <state id=\"$name","Ix2\" emission=\"emitrndx\"/>\n";

  print STATE "  <state id=\"$name","M1\" emission=\"emit","@CMU1[0]","@CMU2[0]\"/>\n";
  print STATE "  <state id=\"$name","M2\" emission=\"emit","@CMU1[1]","@CMU2[1]\"/>\n";
  print STATE "  <state id=\"$name","M3\" emission=\"empty\"/>\n";

  # New states introduced   
  

  my %test1;
  my %test2; 
  for($k=0;$k<@NucBlock;$k++)
  {
    $CMUA = $CMU1.@NucBlock[$k];
    $CMUB = $CMU2.@NucBlock[$k];
    $test1 {$CUtoProt{$CMUA}} = 1.0;
    $test2 {$CUtoProt{$CMUB}} = 1.0;

  }

  @keys1 = keys %test1;
  @keys2 = keys %test2;

  #print @keys;

  for($k=0;$k<@keys1;$k++)
  {
   for($j=0;$j<@keys2;$j++)
   {
      if(@keys1[$k] eq /[a-zA-Z]/ ||  @keys2[$j] eq /[a-zA-Z]/)
      {
        print "Special case in STATE Block: $name\t Protein1: @keys1[$l] Protein2: @keys2[$m]","\n";
        
      }
      else
      {
        $Prot=@keys1[$k].@keys2[$j]; 
        print STATE "<state id=\"$name","$Prot\" emission=\"emit","$name","$Prot\"/>\n";
      }
   
   }
    
  }
  print STATE "  <state id=\"$name","Iy0\" emission=\"emitrndy\"/>\n";
  print STATE "  <state id=\"$name","Iy1\" emission=\"emitrndy\"/>\n";
  print STATE "  <state id=\"$name","Iy2\" emission=\"emitrndy\"/>\n";
  print STATE "  <state id=\"$name","Dy1\" emission=\"emit","@CMU1[0]","gap\"/>\n";
  print STATE "  <state id=\"$name","Dy2\" emission=\"emit","@CMU1[1]","gap\"/>\n";
  print STATE "  <state id=\"$name","end\" emission=\"empty\"/>\n"; 

  $flag = 0; # Handles special cases.

  for($l=0;$l<@keys1;$l++)
  {
  for($m=0;$m<@keys2;$m++)
  {
   #print @keys1[$l],"\n";
   if(@keys1[$l] eq /[a-zA-Z]/ ||  @keys2[$m] eq /[a-zA-Z]/)
   { 
     print "Special case in TRANS Block: $name\t Protein1: @keys1[$l] Protein2: @keys2[$m]","\n";    
     $flag  = 1;
   }
   else
   {
     print TRANS "<transition from=\"$name","M3\" to=\"$name","@keys1[$l]","@keys2[$m]","\" probability=\"prob2$name","@keys1[$l]","@keys2[$m]","\"/>","\n";
     print TRANS "<transition from=\"$name",,"@keys1[$l]","@keys2[$m]","\" to=\"$name","end","\" probability=\"prob2","end","\"/>","\n";
     $flag = 0;
   }


   $EmitProb = 0.0;
   $ProbVal = 0.0;

   if ($flag == 0)
   {
    print EmitProb "<emission id=\"emit$name",@keys1[$l],@keys2[$m],"\">","\n";
    print EmitProb "<output idref=\"sequence1\"/>","\n";
    print EmitProb "<output idref=\"sequence2\"/>","\n";
    print EmitProb "<probability>","\n";
    print EmitProb "<code type=\"statement\" init=\"initialise1\">","\n";
    print EmitProb "<identifier output=\"sequence1\"> iSymb1 </identifier>","\n";
    print EmitProb "<identifier output=\"sequence2\"> iSymb2 </identifier>","\n";
    print EmitProb "<identifier type=\"result\" value=\"iResult\"/>","\n";
    print EmitProb "<![CDATA[","\n";
    print EmitProb "iResult = 0.0;","\n";
   }

   for($k=0;$k<@NucBlock;$k++)
   {
    for($j=0;$j<@NucBlock;$j++)
    {
     
     $CMUA = $CMU1.@NucBlock[$k];
     $CMUB = $CMU2.@NucBlock[$j];
        
     $val = $PMatS {$CUtoProt{$CMUA}.$CUtoProt{$CMUB}};   

     if($val == 0)
     {
       $val = $PMatS {$CUtoProt{$CMUB}.$CUtoProt{$CMUA}}; 
     }
  
     $val = $val*($CFU{$CMUA}*$CFU{$CMUB})/10000;  
     
    if ($CUtoProt{$CMUA} eq  @keys1[$l] && $CUtoProt{$CMUB} eq @keys2[$m])
    {
      $EmitProb += $val;
      #print  "emit@NucBlock[$k]@NucBlock[$j]","\t",$val,"\n"; #TO DO : On hold for now :(
      if ($flag == 0)
      {
       print EmitProb "iResult += $val*emitXX('@NucBlock[$k]','@NucBlock[$j]',iSymb1,iSymb2,iQscores1[iPos0],iQscores2[iPos1]);\n";      
      }
    }
     
     $ProbVal += $val;

   }
  
 
   
  }
  if ($flag == 0)
  {
    print EmitProb "iResult = iResult/$EmitProb;","\n";
    print EmitProb "]]>\n";
    print EmitProb "</code>\n";
    print EmitProb "</probability>\n";
    print EmitProb "</emission>\n";
  }
  
  #print "break\n";
  #print $EmitProb, "\n";
  #print  @keys1[$l], "\t", @keys2[$m], "\t", $EmitProb/$ProbVal,"\n";
  
  if ($flag == 0)
  {
    $ratio = $EmitProb/$ProbVal;
    print TPROB "  <probability id=\"prob2$name@keys1[$l]@keys2[$m]\"><code type=\"expression\"> $ratio  </code></probability>\n";
  }

   


  }
  }
  $ProbID = "mat".$name;
  print PROB "  <probability id=\"$ProbID\"><code type=\"expression\"> $ProbVal  </code></probability>\n";
  
}
}

close(MACRO);
close(STATE);
close(PROB);
close(EmitProb);



