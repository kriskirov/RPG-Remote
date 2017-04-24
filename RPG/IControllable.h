#ifndef I_CONTROLLABLE_H
#define I_CONTROLLABLE_H
#include "Action.h"
class IControllable{
public:
	virtual void control(const Action action) = 0;
};
#endif