#ifndef CONSOLE_OUTPUT_STREAM
#define CONSOLE_OUTPUT_STREAM

#include "IOutputStream.h"
#include <ostream>

class ConsoleOutputStream : public IOutputStream{
public:
	ConsoleOutputStream(std::ostream& outputStream);
	ConsoleOutputStream(const ConsoleOutputStream& rhs) = default;
	ConsoleOutputStream& operator=(const ConsoleOutputStream& rhs);
	virtual ~ConsoleOutputStream();

	virtual ConsoleOutputStream& operator<<(const bool object) override;
	virtual ConsoleOutputStream& operator<<(const char object) override;
	virtual ConsoleOutputStream& operator<<(const char* object) override;
	virtual ConsoleOutputStream& operator<<(const std::string object) override;
	virtual ConsoleOutputStream& operator<<(const int object) override;
	virtual ConsoleOutputStream& operator<<(const unsigned int object) override;
	virtual ConsoleOutputStream& operator<<(const float object) override;
	virtual ConsoleOutputStream& operator<<(const double object) override;

protected:
	std::ostream* mOutputStream;
};
#endif