#include "QuotesSettings.h"

QuotesSettings::QuotesSettings(
	std::string attack,
	std::string getAttacked,
	std::string getAttackedWhileDead,
	std::string dead
	):
	mAttack(attack),
	mGetAttacked(getAttacked),
	mGetAttackedWhileDead(getAttackedWhileDead),
	mDead(dead)
{

}