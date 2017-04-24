#include "StatisticsSettings.h"

StatisticsSettings::StatisticsSettings() : mDamage(1.0f), mHealth(10.0f), mSpeed(1) {

}

StatisticsSettings::StatisticsSettings(const float damage, const float health, const int speed) : mDamage(damage), mHealth(health), mSpeed(speed) {

}