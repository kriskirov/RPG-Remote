#ifndef I_CONTROLLER_H
#define I_CONTROLLER_H
#include "IControllable.h"
#include "IReader.h"
#include "IOption.h"
#include "unique_map.h"

template<typename RESULT_TYPE>
class IController{
public:
	IController(IControllable& controllable, IOption<RESULT_TYPE>& option, unique_map<Action,RESULT_TYPE>& controls);
	IController(const IController<RESULT_TYPE>& rhs);
	virtual ~IController();
	IController& operator=(const IController<RESULT_TYPE>& rhs);
	RESULT_TYPE get_last_input();

	virtual void execute() =0;
protected:
	IControllable& mControllable;
	IOption<RESULT_TYPE>& mOption;
	unique_map<Action,RESULT_TYPE>& mControls;
	RESULT_TYPE mLastInput;
};

template<typename RESULT_TYPE>
IController<RESULT_TYPE>::IController(IControllable& controllable, IOption<RESULT_TYPE>& option, unique_map<Action,RESULT_TYPE>& controls) :mControllable(controllable), mOption(option), mControls(controls){
}

template<typename RESULT_TYPE>
IController<RESULT_TYPE>::IController(const IController<RESULT_TYPE>& rhs) : mControllable(rhs.mControllable), mOption(rhs.mOption), mControls(rhs.mControls){

}

template<typename RESULT_TYPE>
IController<RESULT_TYPE>::~IController(){

}

template<typename RESULT_TYPE>
IController<RESULT_TYPE>& IController<RESULT_TYPE>::operator=(const IController<RESULT_TYPE>& rhs){
	mControllable = rhs.mControllable;
	mOption = rhs.mOption;
	mControls = rhs.mControls;
	return *this;
}

template<typename RESULT_TYPE>
RESULT_TYPE IController<RESULT_TYPE>::get_last_input(){
	return mLastInput;
}
#endif