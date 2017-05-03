#ifndef QUOTES_SETTINGS_H
#define QUOTES_SETTINGS_H

#include <string>

struct QuotesSettings{
	QuotesSettings() = default;

	QuotesSettings(
		std::string attack, 
		std::string getAttacked,
		std::string getAttackedWhileDead,
		std::string dead
		);

	~QuotesSettings() = default;

	QuotesSettings& operator=(const QuotesSettings& rhs) = default;

	std::string mAttack;
	std::string mGetAttacked;
	std::string mGetAttackedWhileDead;
	std::string mDead;
};

#endif