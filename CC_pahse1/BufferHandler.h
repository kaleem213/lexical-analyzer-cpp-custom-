#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
class BufferHandler
{
private:
	ifstream fin;
	string buffer;
	bool endRepeat, status;
	int bufferLength, presentIndex;
	bool initialize();
	bool inputLine();
public:
	BufferHandler();
	bool getChar(char&character, bool repeat=false);
};