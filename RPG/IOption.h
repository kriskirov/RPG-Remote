#ifndef I_OPTION_H
#define I_OPTION_H

#include <functional>

template<typename RESULT_TYPE>
class IOption{
public:
	IOption();
	IOption(RESULT_TYPE& result);
	virtual ~IOption();
	IOption(const IOption& rhs);
	IOption<RESULT_TYPE>& operator=(const IOption& rhs);

	virtual void output() = 0;
	virtual void input() = 0;
	RESULT_TYPE get_result();
protected:
	RESULT_TYPE mResult;
};

template<typename RESULT_TYPE>
IOption<RESULT_TYPE>::IOption() : mResult(RESULT_TYPE()){
}

template<typename RESULT_TYPE>
IOption<RESULT_TYPE>::IOption(RESULT_TYPE& result) : mResult(result){

}

template<typename RESULT_TYPE>
IOption<RESULT_TYPE>::~IOption(){

}

template<typename RESULT_TYPE>
IOption<RESULT_TYPE>::IOption(const IOption& rhs) : mResult(rhs.mResult){
	
}

template<typename RESULT_TYPE>
IOption<RESULT_TYPE>& IOption<RESULT_TYPE>::operator=(const IOption& rhs){
	mResult = rhs.mResult;
	return *this;
}

template<typename RESULT_TYPE>
RESULT_TYPE IOption<RESULT_TYPE>::get_result(){
	return mResult;
}
#endif