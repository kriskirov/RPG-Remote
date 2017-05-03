#ifndef AUTO_CONSOLE_OPTION
#define AUTO_CONSOLE_OPTION

#include "IAutoOption.h"
#include <string>
#include <set>
#include <map>
#include <type_traits>
#include <string>

template<typename RESULT_TYPE>
class AutoConsoleOption : public IAutoOption<RESULT_TYPE>{
public:
	AutoConsoleOption(
		InputOutputStream& ioStream,
		const std::string& staticOutputMessege = "Available options are:", 
		const std::string& noOptionsMessege = "No options to display!",
		const std::string& impossibleOptionMessege = "This option is not available. Try again!", 
		const std::string& invalidOptionMessege = "Invalid input.Try again!"
		);

	AutoConsoleOption(const AutoConsoleOption& rhs);
	virtual ~AutoConsoleOption();
	AutoConsoleOption& operator=(const AutoConsoleOption& rhs);

	virtual void output() override;
	virtual void input() override;
};

template<typename RESULT_TYPE>
AutoConsoleOption<RESULT_TYPE>::AutoConsoleOption(
	InputOutputStream& ioStream,
	const std::string& staticOutputMessege, 
	const std::string& noOptionsMessege,
	const std::string& impossibleOptionMessege,
	const std::string& invalidOptionMessege
	) :
	IAutoOption(
	ioStream,
	staticOutputMessege,
	noOptionsMessege,
	impossibleOptionMessege,
	invalidOptionMessege
	)
{
	static_assert(std::is_convertible<remove_pointer<RESULT_TYPE>::type,std::string>::value, 
		"A template type of AutoConsoleOption must be convertible to std::string.");
	
}

template<typename RESULT_TYPE>
AutoConsoleOption<RESULT_TYPE>::AutoConsoleOption(const AutoConsoleOption& rhs) : IAutoOption(rhs)
{

}

template<typename RESULT_TYPE>
AutoConsoleOption<RESULT_TYPE>::~AutoConsoleOption(){

}

template<typename RESULT_TYPE>
AutoConsoleOption<RESULT_TYPE>& AutoConsoleOption<RESULT_TYPE>::operator=(const AutoConsoleOption& rhs) {
	IAutoOption::operator=(rhs);
	return *this;
}

template<typename RESULT_TYPE>
void AutoConsoleOption<RESULT_TYPE>::output(){
	if (!mValueOptions.empty()){
		typedef std::set<RESULT_TYPE>::iterator Iter;
		unsigned int counter = 1;
		std::string messege;
		messege += mStaticOutputMessege + '\n';
		for (Iter iter = mValueOptions.begin(); iter != mValueOptions.end(); ++iter, ++counter){
			//**iter must be convertible to std::string
			messege += "'" + std::to_string(counter) + "'" + " " + std::string(**iter) + '\n';
		}
		messege += '\n';
		mIOStream.oStream() << messege;
	}
	else{
		mIOStream.oStream() << mNoOptionsMessege << '\n';
	}
}

template<typename RESULT_TYPE>
void AutoConsoleOption<RESULT_TYPE>::input(){
	//take the SET of CHOICES
	typedef std::set<RESULT_TYPE>::iterator Iter;
	std::map<unsigned int, RESULT_TYPE> mOptions;
	unsigned int mMaxOptionNumber = 1;
	//construct a MAP from it. The MAP is constructed with a NUMBER as a key and the respective value from the SET as a VALUE
	for (Iter iter = mValueOptions.begin(); iter != mValueOptions.end(); ++iter, ++mMaxOptionNumber){
		mOptions.insert(std::pair<unsigned int,RESULT_TYPE>(mMaxOptionNumber, *iter));
	}

	unsigned int input;
	if (!mOptions.empty()){
		while (true){
			if (mIOStream.iStream() >> input){
				if (input > 0 && input <= mMaxOptionNumber){
					typedef std::map<unsigned int, RESULT_TYPE>::iterator OptionIter;
					OptionIter optionIter = mOptions.find(input);
					if (optionIter != mOptions.end()){
						mResult = (*optionIter).second;
						return;
					}
				}
				else{
					mIOStream.oStream() << mImpossibleMessege << '\n';
				}
			}
			else{
				mIOStream.oStream() << mInvalidMessege << '\n';
			}
			mIOStream.iStream().clear();
			mIOStream.iStream().ignore();
		}
	}
	mResult = nullptr;
}
#endif