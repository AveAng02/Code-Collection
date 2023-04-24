#include <iostream>

using namespace std;

int main() {
   int x = 0;

   try 
   {
      if (x == 0) 
      {
         throw "Division by zero";
      }
      if (x==0 || 2/x > 0)
      {
        cout << x++ << "\n" << ++x << endl;
      }
   }
   catch(const char* msg) 
   {
      cerr << msg << endl;
   }

   return 0;
}
