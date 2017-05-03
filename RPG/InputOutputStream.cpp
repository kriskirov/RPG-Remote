#include "InputOutputStream.h"

InputOutputStream::InputOutputStream(IInputStream& inputStream, IOutputStream& outputStream) : 
mInputStream(inputStream),
mOutputStream(outputStream)
{

}

InputOutputStream& InputOutputStream::operator=(const InputOutputStream& rhs){
	mInputStream = rhs.mInputStream;
	mOutputStream = rhs.mOutputStream;
	return *this;
}

IInputStream& InputOutputStream::iStream(){
	return mInputStream;
}

IOutputStream& InputOutputStream::oStream(){
	return mOutputStream;
}