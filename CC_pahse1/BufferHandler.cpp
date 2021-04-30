#include "BufferHandler.h"

const string codeFileName = "code.txt";

bool BufferHandler::initialize()
{
    fin.open(codeFileName);
    if (!fin){
        cout << "error loading code file\n";
        return false;
    }
    else
    {
        return true;
    }
}

BufferHandler::BufferHandler()
{
    if (!initialize()) {
        exit(1);
    }
	else {
		bufferLength = 0;
		presentIndex = 0;
		buffer = "\0";
		endRepeat = true;
	}
}

bool BufferHandler::getChar(char& character,bool repeat)
{
	if (presentIndex == bufferLength) {
		status = inputLine();
	}
	if (!repeat) {
		do {
			character = buffer[presentIndex];
		} while (character == '\t');
		++presentIndex;
	}
	else {
	}
	return status;
}
bool BufferHandler::inputLine() {
	if (!fin.eof()) {
		presentIndex = 0;
		buffer.clear();
		getline(fin, buffer);
		buffer.append(1,' ');
		bufferLength = buffer.length();
		return true;
	}
	return false;
}
