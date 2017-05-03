#ifndef I_INPUT_STREAM_H
#define I_INPUT_STREAM_H

#include <string>

class IInputStream {
public:
	virtual IInputStream& operator>>(bool& object) = 0;
	virtual IInputStream& operator>>(char& object) = 0;
	virtual IInputStream& operator>>(char* object) = 0;
	virtual IInputStream& operator>>(std::string& object) = 0;
	virtual IInputStream& operator>>(int& object) = 0;
	virtual IInputStream& operator>>(unsigned int& object) = 0;
	virtual IInputStream& operator>>(float& object) = 0;
	virtual IInputStream& operator>>(double& object) = 0;
	
	virtual void clear() = 0;
	virtual void ignore() = 0;
	virtual bool fail() const = 0;

	virtual operator bool() const = 0;
};
#endif