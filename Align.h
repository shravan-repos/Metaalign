#include <string>
using namespace std;
class Align
{
  public:
 
  Align();
  ~Align(); 
  static string* Get_AlignstateId();
  static string* Get_AlignemissionId();
  static string* Get_AligntransitionId();
  static string* Get_AligntransF();
  static string* Get_AligntransT();
  static string* Get_AligntransP();
  static string* Get_AligntransE();
  static string* Get_AlignoutputId();
  static string Get_Alignempty();

  static string& Get_AlignstateId( int i );
  static string& Get_AlignemissionId( int i );
  static string& Get_AligntransitionId( int i );
  static string& Get_AligntransF( int i );
  static string& Get_AligntransT( int i );
  static string& Get_AligntransP( int i );
  static string& Get_AligntransE( int i );
  static string& Get_AlignoutputId( int i );

  static int Get_AlignstateNum(); 
  static int Get_AlignemitNum();
  static int Get_AligntransNum();
  static int Get_AlignoutputNum();

  private:
  static string* _AlignstateId;
  static string* _AlignemissionId;
  static string* _AligntransitionId;
  static string* _AligntransF;
  static string* _AligntransT;
  static string*  _AligntransP;
  static string* _AligntransE;
  static string* _AlignoutputId;
  static string  _Alignempty;

  static int _AlignstateNum;
  static int _AlignemitNum;
  static int _AligntransNum;
  static int _AlignoutputNum;
};
