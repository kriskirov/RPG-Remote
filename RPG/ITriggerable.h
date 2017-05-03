#ifndef I_TRIGGERABLE_H
#define I_TRIGGERABLE_H

#include "Trigger.h"

class ITriggerable{
public:
	virtual void trigger(const Trigger trigger) = 0;
};
#endif