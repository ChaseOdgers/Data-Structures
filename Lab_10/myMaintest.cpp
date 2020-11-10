#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]){
//  ostream & operator >> (istream &input, std::char ',');
  int num;
  vector<int> vectorOfInts;
  string filename = argv[1];
  ifstream inFile;
  inFile.open(filename);
	string LastInitial, FirstName, City, Occupation, Number;
  cout<<filename<<endl;
	while(getline(inFile, LastInitial))
	{

	}
}
