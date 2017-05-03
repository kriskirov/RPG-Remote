#ifndef I_COMBATABLE_H
#define I_COMBATABLE_H

#include "IIdentifiable.h"
#include "IStatistics.h"
#include "ITriggerable.h"

class ICombatable : public IIdentifiable, public IStatistics, public ITriggerable {
public:
	virtual void dealDamage(ICombatable& target, ICombatable& dealer) = 0;
	virtual void takeDamage(float amount, ICombatable* attacker) = 0;
	virtual ICombatable* getLastAttacker() = 0;
};
#endif