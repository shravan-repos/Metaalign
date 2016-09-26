#include<vector>
#include <iostream>
#include <fstream>
using namespace std;
std::vector<int> GetStateFromTable()
{
 std::vector<int> buffer;
 fstream f;
 f.open("stateFromTable.txt", ios::in);
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
 static const std::vector<int> stateFromTable = GetStateFromTable();
 return 0;
}
