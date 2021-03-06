#ifndef I_AUTO_OPTION
#define I_AUTO_OPTION

#include <set>
#include <string>
#include <type_traits>
#include "InputOutputStream.h"

template<typename RESULT_TYPE>
class IAutoOption{
public:
	IAutoOption(
		InputOutputStream& ioStream,
		const std::string& staticOutputMessege = "Available options are:",
		const std::string& noOptionsMessege = "No options to display!",
		const std::string& impossibleOptionMessege = "This option is not available. Try again!",
		const std::string& invalidOptionMessege = "Invalid input.Try again!"
	);

	IAutoOption(const IAutoOption& rhs) = default;
	virtual ~IAutoOption();
	IAutoOption<RESULT_TYPE>& operator= (const IAutoOption& rhs) = default;

	//step 1 - set_options, step 2 - output, step 3 - input, step 4 - get_result
	void setOptions(std::set<RESULT_TYPE>& inputOptions);
	//step 1 - set_options, step 2 - output, step 3 - input, step 4 - get_result
	virtual void output() = 0;
	//step 1 - set_options, step 2 - output, step 3 - input, step 4 - get_result
	virtual void input() = 0;
	//step 1 - set_options, step 2 - output, step 3 - input, step 4 - get_result
	RESULT_TYPE getResult();

protected:
	std::set<RESULT_TYPE> mValueOptions;
	RESULT_TYPE mResult; // weak/aliased pointer
	InputOutputStream& mIOStream;
	std::string mStaticOutputMessege;
	std::string mNoOptionsMessege;
	std::string mImpossibleMessege;
	std::string mInvalidMessege;
};

template<typename RESULT_TYPE>
IAutoOption<RESULT_TYPE>::IAutoOption(
	InputOutputStream& ioStream,
	const std::string& staticOutputMessege, 
	const std::string& noOptionsMessege,
	const std::string& impossibleOptionMessege,
	const std::string& invalidOptionMessege
	) : 
	mResult(nullptr),
	mIOStream(ioStream),
	mStaticOutputMessege(staticOutputMessege),
	mNoOptionsMessege(noOptionsMessege),
	mImpossibleMessege(impossibleOptionMessege),
	mInvalidMessege(invalidOptionMessege)
{
	static_assert(std::is_pointer<RESULT_TYPE>::value, 
		"RESULT_TYPE must be a pointer type. IAutoOption accepts pointer-only types to maintain universal usage of the class.");
}

template<typename RESULT_TYPE>
IAutoOption<RESULT_TYPE>::~IAutoOption(){

}

template<typename RESULT_TYPE>
void IAutoOption<RESULT_TYPE>::setOptions(std::set<RESULT_TYPE>& valueOptions){
	mValueOptions = valueOptions;
}

template<typename RESULT_TYPE>
RESULT_TYPE IAutoOption<RESULT_TYPE>::getResult(){
	return mResult;
}
#endif