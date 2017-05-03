#ifndef I_FACTION_H
#define I_FACTION_H

#include <string>
#include "Faction.h"

class IFaction{
public:
	virtual std::pair<Faction, std::string> getFaction() = 0;
};
#endif