#ifndef CONSOLE_READER_H
#define CONSOLE_READER_H

#include "IReader.h"
#include <istream>

class ConsoleReader : public IReader {
public:
	ConsoleReader(std::istream& inputStream);
	virtual ~ConsoleReader();
	ConsoleReader(const ConsoleReader& rhs);
	ConsoleReader& operator=(const ConsoleReader& rhs);

	virtual char read()override;
protected:
	std::istream* mInputStream;
};
#endif
