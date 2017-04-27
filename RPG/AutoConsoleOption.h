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
	AutoConsoleOption(const std::string& staticOutputMessege = "Available options are:", const std::string& noOptionsMessege = "No options to display!",
					  const std::string& impossibleOptionMessege = "This option is not available. Try again!", const std::string& invalidOptionMessege = "Invalid input.Try again!");
	AutoConsoleOption(const AutoConsoleOption& rhs);
	virtual ~AutoConsoleOption();
	AutoConsoleOption& operator=(const AutoConsoleOption& rhs);

	virtual void output() override;
	virtual void input() override;
protected:
	/*std::map<INPUT_TYPE,RESULT_TYPE> mTheMap;
	unsigned int mMaxOptionNumber;*/
};

template<typename RESULT_TYPE>
AutoConsoleOption<RESULT_TYPE>::AutoConsoleOption(const std::string& staticOutputMessege, const std::string& noOptionsMessege,
												  const std::string& impossibleOptionMessege, const std::string& invalidOptionMessege) :
IAutoOption(staticOutputMessege,noOptionsMessege,impossibleOptionMessege,invalidOptionMessege)
{
	//the VALUE(SET elements) must be convertible to a STRING
	static_assert(std::is_convertible<remove_pointer<RESULT_TYPE>::type,std::string>::value, "A template type of AutoConsoleOption must be convertible to std::string.");
	
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
	//concatinate the static messege with numbers from 1 to N that represent each CHOICE of the SET of CHOICES
	if (!mValueOptions.empty()){
		typedef std::set<RESULT_TYPE>::iterator Iter;
		unsigned int counter = 1;
		std::string messege;
		messege += mStaticOutputMessege + '\n';
		for (Iter iter = mValueOptions.begin(); iter != mValueOptions.end(); ++iter, ++counter){
			messege += "'" + std::to_string(counter) + "'" + " " + std::string(**iter) + '\n'; //must make overriden methods to take care of . and -> operator differences. also *Iter must be convertible to std::string
		}
		messege += '\n';
		cout << messege;
	}
	else{
		cout << mNoOptionsMessege << '\n';
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

	//check if the MAP is not EMPTY
	unsigned int input;
	if (!mOptions.empty()){
		while (true){
			if (cin >> input){
				//check if the INPUT is a valid KEY
				if (input > 0 && input <= mMaxOptionNumber){
					typedef std::map<unsigned int, RESULT_TYPE>::iterator OptionIter;
					OptionIter optionIter = mOptions.find(input);
					if (optionIter != mOptions.end()){
						//then accept the VALUE of the KEY (the CHOICE)
						mResult = (*optionIter).second;
						return;
					}
				}
				else{
					cout << mImpossibleMessege << endl;
				}
			}
			else{
				cout << mInvalidMessege << endl;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//otherwise try again
		}
	}
	//otherwise set the result to null
	mResult = nullptr;
}
#endif