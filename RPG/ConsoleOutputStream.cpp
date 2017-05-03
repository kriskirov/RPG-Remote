#include "ConsoleOutputStream.h"
ConsoleOutputStream::ConsoleOutputStream(std::ostream& outputStream) : mOutputStream(&outputStream){

}

ConsoleOutputStream::~ConsoleOutputStream(){

}

ConsoleOutputStream& ConsoleOutputStream::operator=(const ConsoleOutputStream& rhs) {
	mOutputStream = rhs.mOutputStream;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const bool object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const char object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const char* object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const std::string object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const int object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const unsigned int object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const float object){
	*mOutputStream << object;
	return *this;
}

ConsoleOutputStream& ConsoleOutputStream::operator<<(const double object){
	*mOutputStream << object;
	return *this;
}