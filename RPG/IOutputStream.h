#ifndef I_OUTPUT_STREAM
#define I_OUTPUT_STREAM

#include <string>

class IOutputStream{
public:
	virtual IOutputStream& operator<<(const bool object) = 0;
	virtual IOutputStream& operator<<(const char object) = 0;
	virtual IOutputStream& operator<<(const char* object) = 0;
	virtual IOutputStream& operator<<(const std::string object) = 0;
	virtual IOutputStream& operator<<(const int object) = 0;
	virtual IOutputStream& operator<<(const unsigned int object) = 0;
	virtual IOutputStream& operator<<(const float object) = 0;
	virtual IOutputStream& operator<<(const double object) = 0;

};
#endif