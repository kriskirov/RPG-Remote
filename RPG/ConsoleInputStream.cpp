#include "ConsoleInputStream.h"
#include <limits>

ConsoleInputStream::ConsoleInputStream(std::istream& inputStream) : mInputStream(&inputStream){

}

ConsoleInputStream::~ConsoleInputStream(){

}

ConsoleInputStream& ConsoleInputStream::operator=(const ConsoleInputStream& rhs) {
	mInputStream = rhs.mInputStream;
	return *this;
}

ConsoleInputStream& ConsoleInputStream::operator>>(bool& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(char& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(char* object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(std::string& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(int& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(unsigned int& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(float& object){
	*mInputStream >> object;
	return *this;
}
ConsoleInputStream& ConsoleInputStream::operator>>(double& object){
	*mInputStream >> object;
	return *this;
}
void ConsoleInputStream::clear(){
	(*mInputStream).clear();
}
void ConsoleInputStream::ignore(){
	(*mInputStream).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ConsoleInputStream::fail() const{
	return (*mInputStream).fail();
}

ConsoleInputStream::operator bool() const{
	return !fail();
}

