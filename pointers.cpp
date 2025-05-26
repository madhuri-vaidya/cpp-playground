/*
* Playing around with pointers
* 
* Compilation command: g++ ./pointers.cpp -o pointers
* 
* Usage: ./pointers.exe <play / array>
*   play: assign and re-assign pointers
*   array: access elements of an array using pointers
*/

#include <iostream>

using namespace std;

void pointer_play () {
  int first, second;
  int *p1, *p2;

  p1 = &first;
  cout << "p1 is " << p1 << endl;
  *p1 = 10;
  cout << "first is " << first << endl << endl;
  
  p2 = &second;
  cout << "p2 is " << p2 << endl;
  *p2 = 20;
  cout << "second is " << second << endl << endl;

  cout << "Setting *p2 = *p1" << endl;
  *p2 = *p1;
  cout << "first is " << first << endl;
  cout << "second is " << second << endl;
  cout << "p1 is" << p1 << endl;
  cout << "p2 is " << p2 << endl << endl;

  cout << "Setting p1 = p2" << endl;
  second = 20;
  p1 = p2;
  cout << "first is " << first << endl;
  cout << "second is " << second << endl;
  cout << "p1 is" << p1 << endl;
  cout << "p2 is " << p2 << endl;
  cout << "*p1 is " << *p1 << endl;
  cout << "*p2 is " << *p2 << endl << endl;
}

void pointer_array() {
  int numbers[7];
  int *p;
  p = numbers;
  *p = 10;
  p++; *p = 20;
  p = &numbers[2]; *p = 30;
  p = numbers + 3; *p = 40;
  p = numbers; *(p + 4) = 50;

  int length = sizeof(numbers) / sizeof(numbers[0]);

  for(int i = 0; i < length; i++) { cout << numbers[i] << " "; }
}

int main(int argc, char *argv[]) {
  
  auto print_usage = []() {
    cout << "Usage:" << endl;
    cout << "./pointer_play <play / array>" << endl;
  };

  if(argc < 2) { print_usage(); return 1; }

  string mode = argv[1];

  if(mode == "play") { pointer_play(); }
  
  else if (mode == "array") { pointer_array(); }
  
  else {
    cout << "Mode not recognized. Please select one from 'play' or 'array'.." << endl;
    print_usage();
  }

  return 0;
}
