#include<vector>
#include <iostream>
#include <fstream>
using namespace std;
std::vector<int> GetBlockTable()
{
 std::vector<int> buffer;
 fstream f;
 f.open("blockTable.txt", ios::in);
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
 static const std::vector<int> blockTable = GetBlockTable();
 return 0;
}
