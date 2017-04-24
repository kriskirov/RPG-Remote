#ifndef I_RACE_H
#define I_RACE_H
#include "Race.h"
#include <string>
class IRace{
public:
	virtual std::pair<Race,std::string> getRace() = 0;
};
#endif