#ifndef I_NAME_H
#define I_NAME_H
#include <string>
class IName {
public:
	virtual std::string getName() = 0;
};
#endif