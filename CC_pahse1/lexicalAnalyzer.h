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
	//static const int arraySize;
	//static const string keywordFileName;
	//static const string listTokenFileName;
	//static const string errorFileName;
	//static const string symbolFileName;
	//static const string tTableFileName;
	//static const int statesCount;
	//static const int symbolsCount;
	//static const int tokensCount;
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
//const int LexicalAnalyzer::arraySize = 397;
//const string LexicalAnalyzer::keywordFileName = "keywords.txt";
//const string LexicalAnalyzer::errorFileName = "error.txt";
//const string LexicalAnalyzer::symbolFileName = "symbols.txt";
//const string LexicalAnalyzer::listTokenFileName = "listTokens.txt";
//const string LexicalAnalyzer::tTableFileName = "transitionTable.txt";
//const int LexicalAnalyzer::statesCount = 39;
//const int LexicalAnalyzer::symbolsCount = 24;
//const int LexicalAnalyzer::tokensCount = 34;