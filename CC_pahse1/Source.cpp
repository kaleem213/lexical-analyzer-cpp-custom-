#include<iostream>
#include<string>
#include<fstream>
#include"lexicalAnalyzer.h"
using namespace std;


int main() {
	LexicalAnalyzer lexical;
	if(lexical.getToken()){
	cout << "Done,Please check files\n";
	}
	return 0;
}