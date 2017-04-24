#ifndef I_MOVABLE_H
#define I_MOVABLE_H
#include "IPosition.h"
class IMovable : public IPosition{
public:
	virtual void move(Position& offset) = 0;
	//call the relocate method on the mao with an instance, like: relocate(this,offset);
};
#endif