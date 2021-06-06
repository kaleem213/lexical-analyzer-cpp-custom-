#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include"BufferHandler.h"
using namespace std;

struct Token {
	string token;
	bool finalStatus=false;
};

class LexicalAnalyzer
{
private:
	void initialize();
	void generateToken(ofstream &fout,ofstream &fout1, int arrIndex,string data);
	bool setKeywords();
	bool setTransitionTable();
	int sumValue(string arr);
	bool checkKeywordValidity(string data);
	bool setTokenList();
	int generateHash(int sum, int type = 0, int key = 0);
protected:
	string *keywords;
	Token *tokensList;
	int **transitionTable;
public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	bool getToken();
};