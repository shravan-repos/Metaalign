# include <string>
using std::string;
double emitXX(char iRefSymb1, char iRefSymb2, int iSymb1, int iSymb2, double iQscores1, double iQscores2)
{  
    double iResult = 0.0;
    if (iSymb2 != iRefSymb2) 
    {
         if (iSymb1 != iRefSymb1) 
         {
              iResult = iQscores1*iQscores2/9;
         } 
         else 
         {
              iResult = (1-iQscores1)*iQscores2/3;
         }
    } 
   else 
   {
         if (iSymb1 != iRefSymb1) 
         {
              iResult = iQscores1*(1-iQscores2)/3;
         } 
         else 
         {
              iResult = (1-iQscores1)*(1-iQscores2);
         }
    }   
    
    return iResult;
}

