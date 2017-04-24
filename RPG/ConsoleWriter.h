#ifndef CONSOLE_WRITER_H
#define CONSOLE_WRITER_H
#include "IWriter.h"

class ConsoleWriter : public IWriter{
public:
	void write(char c)override;
};
#endif