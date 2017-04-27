#ifndef COMBATABLE_SETTINGS_H
#define COMBATABLE_SETTINGS_H
#include "IdentifiableSettings.h"
#include "StatisticsSettings.h"
#include "ICombatable.h"

struct CombatableSettings{
	CombatableSettings();
	CombatableSettings(const IdentifiableSettings& identifiableSettings, const StatisticsSettings& statisticsSettings, ICombatable* lastAttacker);
	~CombatableSettings() = default;
	CombatableSettings& operator=(const CombatableSettings& rhs) = default;
	
	IdentifiableSettings mIdentifiableSettings;
	StatisticsSettings mStatisticsSettings;
	ICombatable* mLastAttacker;
};
#endif