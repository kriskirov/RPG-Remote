#ifndef I_IDENTIFIABLE_H
#define I_IDENTIFIABLE_H

#include "IName.h"
#include "IRace.h"
#include "IFaction.h"

class IIdentifiable : public IName, public IRace, public IFaction{

};
#endif