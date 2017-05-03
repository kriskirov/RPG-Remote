#ifndef I_POSITION_H
#define I_POSITION_H

#include "Position.h"
#include "Map.h"

class IPosition{
public:
	virtual Position getPosition() = 0;
	virtual void setPosition(Position& pos) = 0;
};
#endif