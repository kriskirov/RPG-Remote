#include "IdentifiableSettings.h"

IdentifiableSettings::IdentifiableSettings() : mName("Default Name"), mRace(std::pair<Race,std::string>(Race::none,"None")), mFaction(std::pair<Faction,std::string>(Faction::none,"None")){

}

IdentifiableSettings::IdentifiableSettings(const std::string& name, const std::pair<Race,std::string>& race, const std::pair < Faction, std::string>& faction) : mName(name), mRace(race), mFaction(faction) {

}