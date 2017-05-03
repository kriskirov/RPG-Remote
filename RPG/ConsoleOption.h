#ifndef CONSOLE_OPTION_H
#define CONSOLE_OPTION_H

#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <functional>
#include "IOption.h"
#include <type_traits>

template<typename RESULT_TYPE>
class ConsoleOption : public IOption<RESULT_TYPE>{
public:
	
	ConsoleOption(
		const std::string& output,
		std::function <bool(RESULT_TYPE)> boolExpression,
		const std::string& impossibleOption = "This option is not available. Try again!",
		const std::string& invalidInput = "Invalid input. Try again!"
		);

	ConsoleOption(
		const std::string& output, 
		RESULT_TYPE defaultResult,
		std::function <bool(RESULT_TYPE)> boolExpression,
		const std::string& impossibleOption = "This option is not available. Try again!",
		const std::string& invalidInput = "Invalid input. Try again!"
		);

	virtual void input() override;
	virtual void output() override;
protected:
	std::string mOutput;
	std::function <bool(RESULT_TYPE)> mBoolExpression;
	std::string mImpossibleOption;
	std::string mInvalidInput;
};

template<typename RESULT_TYPE>
ConsoleOption<RESULT_TYPE>::ConsoleOption(
	const std::string& output,
	std::function <bool(RESULT_TYPE)> boolExpression,
	const std::string& impossibleOption,
	const std::string& invalidInput
	) :
	IOption<RESULT_TYPE>(RESULT_TYPE()),
	mOutput(output),
	mBoolExpression(boolExpression),
	mImpossibleOption(impossibleOption),
	mInvalidInput(invalidInput)
{
	static_assert(
		std::is_default_constructible<RESULT_TYPE>::value,
		"RESULT_TYPE must be default constructible with this constructor. If the needed type has no copy constructor use the other constructor of the ConsoleOption class."
		);
}

template<typename RESULT_TYPE>
ConsoleOption<RESULT_TYPE>::ConsoleOption(
	const std::string& output,
	RESULT_TYPE defaultResult,
	std::function <bool(RESULT_TYPE)> boolExpression,
	const std::string& impossibleOption,
	const std::string& invalidInput
	) : 
	IOption<RESULT_TYPE>(defaultResult),
	mOutput(output),
	mBoolExpression(boolExpression),
	mImpossibleOption(impossibleOption),
	mInvalidInput(invalidInput)
{

}

template<typename RESULT_TYPE>
void ConsoleOption<RESULT_TYPE>::output(){
	std::cout << mOutput << std::endl;
}

template <typename RESULT_TYPE>
void ConsoleOption<RESULT_TYPE>::input(){
	RESULT_TYPE result;
	while (true){
		if (cin >> result){
			if (mBoolExpression(result)){
				mResult = result;
				return;
			}
			else{
				cout << mImpossibleOption << endl;
			}
		}
		else{
			cout << mInvalidInput << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
#endif