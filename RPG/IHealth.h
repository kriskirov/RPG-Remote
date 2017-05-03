#ifndef I_HEALTH_H
#define I_HEALTH_H

class IHealth {
public:
	virtual float getHealth() = 0;
	virtual bool isDead() = 0;
};
#endif