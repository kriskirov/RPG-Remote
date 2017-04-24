#include "CombatableSettings.h"

CombatableSettings::CombatableSettings() : mIdentifiableSettings(IdentifiableSettings()), mStatisticsSettings(StatisticsSettings()) {

}

CombatableSettings::CombatableSettings(const IdentifiableSettings& identifiableSettings, const StatisticsSettings& statisticsSettings) :
mIdentifiableSettings(identifiableSettings),
mStatisticsSettings(statisticsSettings)
{

}