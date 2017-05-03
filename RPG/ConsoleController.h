#ifndef CONSOLE_CONTROLLER_H
#define CONSOLE_CONTROLLER_H

#include "IController.h"
#include"IControllable.h"
#include"IReader.h"
#include"IOption.h"
#include"unique_map.h"

template<typename RESULT_TYPE>
class ConsoleController : public IController<RESULT_TYPE>{
public:
	ConsoleController(
		IControllable& controllable,
		IOption<RESULT_TYPE>& option,
		unique_map<Action,RESULT_TYPE>& controls
		);

	ConsoleController(const ConsoleController& rhs);
	virtual ~ConsoleController();
	ConsoleController& operator=(const ConsoleController& rhs);

	virtual void execute() override;
};

template <typename RESULT_TYPE>
ConsoleController<RESULT_TYPE>::ConsoleController(
	IControllable& controllable,
	IOption<RESULT_TYPE>& option,
	unique_map<Action,RESULT_TYPE>& controls
	) :
	IController(controllable, option, controls)
{

}

template<typename RESULT_TYPE>
ConsoleController<RESULT_TYPE>::ConsoleController(const ConsoleController& rhs) : IController(rhs){

}

template<typename RESULT_TYPE>
ConsoleController<RESULT_TYPE>::~ConsoleController(){

}

template<typename RESULT_TYPE>
ConsoleController<RESULT_TYPE>& ConsoleController<RESULT_TYPE>::operator=(const ConsoleController& rhs) {
	IController::operator=(rhs);
	return *this;
}

template<typename RESULT_TYPE>
void ConsoleController<RESULT_TYPE>::execute(){
	mOption.output();
	mOption.input();
	RESULT_TYPE& r = mOption.get_result();
	Action action;
	mControls.getKey(r,action);
	mControllable.control(action);
	mLastInput = r;
}
#endif