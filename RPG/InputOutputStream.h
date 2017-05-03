#ifndef INPUT_OUTPUT_STREAM_H
#define INPUT_OUTPUT_STREAM_H

#include "IInputStream.h"
#include "IOutputStream.h"

class InputOutputStream {
public:
	InputOutputStream(IInputStream& inputStream, IOutputStream& outputStream);
	InputOutputStream(const InputOutputStream& rhs) = default;
	InputOutputStream& operator=(const InputOutputStream& rhs);
	IInputStream& iStream();
	IOutputStream& oStream();
private:
	IInputStream& mInputStream;
	IOutputStream& mOutputStream;
};
#endif