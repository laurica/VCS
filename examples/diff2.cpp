#include <iostream>

using std;

int main(int **argv, int argc) {
  cout << "You gave arguments: ";
  for (int i = 0; i < argc; ++i)
    {
      cout << argv[i] << "    ";
    }
  cout << endl;
  int moreMeaningfulName = 50;
  for (int i = 0; i < 20; ++i)
    {
      cout << "you do this number: " << moreMeaningfulName + i << endl;
    }
  cout << "Hello world!" << endl;

  return 0;
}
