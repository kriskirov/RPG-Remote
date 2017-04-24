#ifndef IDENTIFIABLE_SETTINGS_H
#define IDENTIFIABLE_SETTINGS_H
#include <string>
#include "Faction.h"
#include "Race.h"
struct IdentifiableSettings{
	IdentifiableSettings();
	IdentifiableSettings(const std::string& name, const std::pair<Race,std::string>& race, const std::pair<Faction,std::string>& faction);
	IdentifiableSettings(const IdentifiableSettings& rhs) = default;
	~IdentifiableSettings() = default;
	IdentifiableSettings& operator=(const IdentifiableSettings& rhs) = default;

	std::string mName;
	std::pair<Race,std::string> mRace;
	std::pair<Faction,std::string> mFaction;
};
#endif