#include "CombatableSettings.h"

CombatableSettings::CombatableSettings() : mIdentifiableSettings(IdentifiableSettings()), mStatisticsSettings(StatisticsSettings()), mLastAttacker(nullptr) {

}

CombatableSettings::CombatableSettings(const IdentifiableSettings& identifiableSettings, const StatisticsSettings& statisticsSettings, ICombatable* lastAttacker) :
mIdentifiableSettings(identifiableSettings),
mStatisticsSettings(statisticsSettings),
mLastAttacker(lastAttacker)
{

}