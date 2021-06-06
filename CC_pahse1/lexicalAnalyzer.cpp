#include "lexicalAnalyzer.h"

const int arraySize = 397;
const string keywordFileName = "keywords.txt";
const string errorFileName = "error.txt";
const string symbolFileName = "symbols.txt";
const string listTokenFileName = "listTokens.txt";
const string tTableFileName = "transitionTable.txt";
const string tokenFileName = "tokens.txt";
const int statesCount = 39;
const int symbolsCount = 24;
const int tokensCount = 34;

void LexicalAnalyzer::initialize()
{
	bool chk1, chk2, chk3;
	chk1 = setKeywords();
	chk2 = setTransitionTable();
	chk3 = setTokenList();
	if (!(chk1 && chk2 && chk3)) {
		exit(1);
	}
}

int LexicalAnalyzer::sumValue(string arr) {
	int sum = 0;
	for (int j : arr) {
		sum += j;
	}
	return sum;
}

LexicalAnalyzer::LexicalAnalyzer()
{
	initialize();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}

bool LexicalAnalyzer::setTokenList()
{
	ifstream fin(listTokenFileName);
	string loadToken;
	tokensList = new Token[statesCount];
	int occurs,loadIndex;
	if (fin) {
		fin >> loadToken;
		for (int i = 0; i < tokensCount;++i) {
			fin >> loadToken;
			fin >> occurs;
			for (int j = 0; j < occurs;++j) {
				fin >> loadIndex;
				tokensList[loadIndex].token = loadToken;
				tokensList[loadIndex].finalStatus = true;
			}
		}
		fin.close();
		return true;
	}
	else {
		cout << "error loading tokenList file\n";
		return false;
	}
}

bool LexicalAnalyzer::setKeywords()
{
	keywords = new string[arraySize];
	ifstream fin(keywordFileName);
	if (fin) {
		string extra;
		int sum,key;
		for (int i = 0; !fin.eof(); ++i) {
			fin >> extra;
			sum = 0;
			for (int j : extra) {
				sum += j;
			}
			key = generateHash(sum);
			if (keywords[key] != "\0") {
				key = generateHash(sum,1,key);
				if (keywords[key] != "\0") {
					fin.close();
					return false;
				}
				else {
					keywords[key] = extra;
				}
			}
			else {
				keywords[key] = extra;
			}
		}
		fin.close();
		return true;
	}
	else {
		cout << "error\n";
	}
}

int LexicalAnalyzer::generateHash(int sum,int type,int key)
{
	int alterSum;
	int alterKey;
	if (type == 0) {
		key = (sum) % arraySize;
		return key;
	}
	else{
		alterSum = 100 - (sum % 100);
		alterKey = (key + alterSum) % arraySize;
		return alterKey;
	}
}

bool LexicalAnalyzer::setTransitionTable()
{
	transitionTable = new int* [statesCount];
	for (int i = 0; i < statesCount; ++i) {
		transitionTable[i] = new int[arraySize];
		for (int j = 0; j < arraySize;++j) {
			transitionTable[i][j] = 0;
		}
	}

	string symbols[symbolsCount];
	ifstream fin1(symbolFileName);
	ifstream fin2(tTableFileName);
	int sum;
	int symbolIndex[symbolsCount];
	if (fin1&&fin2) {
		for (int i = 0; i < symbolsCount;++i) {
			fin1>>symbols[i];
		}
		fin1.close();

		for (int i = 0; i < symbolsCount;++i) {
			sum = sumValue(symbols[i]);
			symbolIndex[i] = generateHash(sum);
		}

		for (int i = 0; i < statesCount;++i) {
			for (int j = 0; j < symbolsCount;++j) {
				fin2>>transitionTable[i][symbolIndex[j]];
			}
		}
		fin2.close();
		return true;
	}
	else {
		cout << "error loading transition-table files\n";
	}
	return false;
}
bool LexicalAnalyzer::getToken() {
	BufferHandler buffer;
	string data;
	ofstream fout(tokenFileName);
	ofstream fout1(errorFileName);
	char character;
	int arrIndex = 0,key,result;
	bool status = false;
	while (buffer.getChar(character,status)) {
		if (character == ' ') {
			if (arrIndex != 0) {
				key = generateHash(' ');
				result = transitionTable[arrIndex][key];
				generateToken(fout,fout1,arrIndex, data);
				arrIndex = 0;
				data.clear();
			}
		}
		else{
			if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z')) {
				if (character == 'E' || character == 'e') {
					if (arrIndex == 35 || arrIndex == 36) {
						cout << "number e called\n";
						key = generateHash('e');
					}
					else {
						key = generateHash(sumValue("ID"));
					}
				}
				else {
					key = generateHash(sumValue("ID"));
				}
			}
			else if ((character >= '0' && character <= '9')) {
				key = generateHash(sumValue("NO"));
			}
			else {
				key = generateHash(character);
			}
			result = transitionTable[arrIndex][key];
			cout << "result: " << result << endl;
			if (result==0) {
				if (result != arrIndex) {
					generateToken(fout, fout1, arrIndex, data);
					data.clear();
					arrIndex = 0;
					status = true;
				}
			}
			else {
				data.append(string(1,character));
				arrIndex = result;
				status = false;
			}
		}
	}
	key = generateHash(character);
	fout.close();
	fout1.close();
	return true;
}
void LexicalAnalyzer::generateToken(ofstream& fout,ofstream &fout1,int arrIndex,string data) {
	cout << "data in genToken: " << data << endl;
	cout << "arrIndex in genToken: " << arrIndex << endl;
		if (tokensList[arrIndex].finalStatus) {
			fout << "<";
			if (arrIndex==1|| arrIndex == 35 || arrIndex == 36 || arrIndex == 37) {
				if (checkKeywordValidity(data)) {
					fout << data;
				}
				else {
					fout << tokensList[arrIndex].token << " , " << data;
				}
			}
			else {
				fout << tokensList[arrIndex].token;
			}
			fout << ">\n";
		}
		else {
			fout1 << data << endl;
		}
}
bool LexicalAnalyzer::checkKeywordValidity(string data) {
	int key = generateHash(sumValue(data));
	if (keywords[key].compare(data)==0) {
		return true;
	}
	return false;
}