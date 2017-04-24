#ifndef I_STATISTICS_H
#define I_STATISTICS_H
#include "IDamage.h"
#include "IHealth.h"
#include "ISpeed.h"

class IStatistics : public IDamage, public IHealth, public ISpeed{

};
#endif