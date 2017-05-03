#ifndef CONSOLE_INPUT_STREAM_H
#define CONSOLE_INPUT_STREAM_H

#include "IInputStream.h"
#include <istream>

class ConsoleInputStream : public IInputStream{
public:
	ConsoleInputStream(std::istream& inputStream);
	ConsoleInputStream(const ConsoleInputStream& rhs) = default;
	ConsoleInputStream& operator=(const ConsoleInputStream& rhs);
	virtual ~ConsoleInputStream();

	virtual ConsoleInputStream& operator>>(bool& object) override;
	virtual ConsoleInputStream& operator>>(char& object) override;
	virtual ConsoleInputStream& operator>>(char* object) override;
	virtual ConsoleInputStream& operator>>(std::string& object) override;
	virtual ConsoleInputStream& operator>>(int& object) override;
	virtual ConsoleInputStream& operator>>(unsigned int& object) override;
	virtual ConsoleInputStream& operator>>(float& object) override;
	virtual ConsoleInputStream& operator>>(double& object) override;

	virtual void clear() override;
	virtual void ignore() override;
	virtual bool fail() const override;

	virtual operator bool() const override;

protected:
	std::istream* mInputStream;
};
#endif