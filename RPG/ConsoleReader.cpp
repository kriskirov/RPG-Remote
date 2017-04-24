#include "ConsoleReader.h"

ConsoleReader::ConsoleReader(std::istream& inputStream) : mInputStream(&inputStream){

}

ConsoleReader::~ConsoleReader(){

}

ConsoleReader::ConsoleReader(const ConsoleReader& rhs) : mInputStream(rhs.mInputStream) {

}

ConsoleReader& ConsoleReader::operator=(const ConsoleReader& rhs) {
	mInputStream = rhs.mInputStream;
	return *this;
}

char ConsoleReader::read(){
	char c;
	(*mInputStream)>>c;
	return c;
}