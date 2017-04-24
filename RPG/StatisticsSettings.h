#ifndef STATISTICS_SETTINGS_H
#define STATISTICS_SETTINGS_H
struct StatisticsSettings{
	StatisticsSettings();
	StatisticsSettings(const float damage, const float health, const int speed);
	~StatisticsSettings() = default;
	StatisticsSettings& operator=(const StatisticsSettings& rhs) = default;

	float mDamage;
	float mHealth;
	int mSpeed;
};
#endif