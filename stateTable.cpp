#include<vector>
#include <iostream>
#include <fstream>
using namespace std;



std::vector<int> GetstateTable1()
{
 std::vector<int> buffer;
 fstream f;
 f.open("stateTable1.txt", ios::in);
 char temp;
 int index;
 while (!f.eof())
 {
   f>>index;
   f>>temp;
   buffer.push_back(index);
 }
 f.close();

 for ( int i=0; i<buffer.size(); i++)
  cout<<buffer[i]<<", ";
 return buffer;
}

std::vector<int> GetstateTable2()
{
 std::vector<int> buffer;
 fstream f;
 f.open("stateTable2.txt", ios::in);
 char temp;
 int index;
 while (!f.eof())
 {
   f>>index;
   f>>temp;
   buffer.push_back(index);
 }
 f.close();

 for ( int i=0; i<buffer.size(); i++)
  cout<<buffer[i]<<", ";
 return buffer;
}




int main()
{
 static const std::vector<int> stateTable1 = GetstateTable1();
 static const std::vector<int> stateTable2 = GetstateTable2();
 

return 0;
}
