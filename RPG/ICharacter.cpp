#include "ICharacter.h"
#include <cassert>

ICharacter::ICharacter(const CombatableSettings& combatableSettings, const MovableSettings<ICharacter*>& movableSettings, IOutputStream &outputStream) : 
mCombatableSettings(combatableSettings), 
mMovableSettings(movableSettings),
mOutputStream(&outputStream)
{
	mMovableSettings.mMap.locate_absolute(mMovableSettings.mPosition, this);
}

ICharacter::ICharacter(const ICharacter& rhs) : 
mCombatableSettings(rhs.mCombatableSettings),
mMovableSettings(rhs.mMovableSettings),
mOutputStream(rhs.mOutputStream)
{
	
}

ICharacter::~ICharacter(){
	mMovableSettings.mMap.erase(this);
}

std::string ICharacter::getName(){
	return mCombatableSettings.mIdentifiableSettings.mName;
}

std::pair < Race, std::string> ICharacter::getRace(){
	return mCombatableSettings.mIdentifiableSettings.mRace;
}

std::pair<Faction, std::string> ICharacter::getFaction(){
	return mCombatableSettings.mIdentifiableSettings.mFaction;
}

float ICharacter::getDamage(){
	return mCombatableSettings.mStatisticsSettings.mDamage;
}

float ICharacter::getHealth(){
	return mCombatableSettings.mStatisticsSettings.mHealth;
}
bool ICharacter::isDead(){
	return mCombatableSettings.mStatisticsSettings.mHealth <= 0.0f;
}

int ICharacter::getSpeed(){
	return mCombatableSettings.mStatisticsSettings.mSpeed;
}

void ICharacter::dealDamage(ICombatable& target, ICombatable& attacker){
	*mOutputStream << attacker.getName() << " attacked " << target.getName() << "." << '\n';
	target.takeDamage(mCombatableSettings.mStatisticsSettings.mDamage, &attacker);
}

void ICharacter::takeDamage(float damage, ICombatable* attacker){
	mCombatableSettings.mStatisticsSettings.mHealth -= damage;
	mCombatableSettings.mLastAttacker = attacker;
	*mOutputStream << getName() << " received " << damage << " damage. (now " << getHealth() << " health points)" << '\n';
	trigger(Trigger::getAttacked);
}

ICombatable* ICharacter::getLastAttacker(){
	return mCombatableSettings.mLastAttacker;
}

Position ICharacter::getPosition(){
	return mMovableSettings.mPosition;
}

void ICharacter::setPosition(Position& pos){
	mMovableSettings.mPosition = pos;
}

void ICharacter::move(Position& offset){
	mMovableSettings.mMap.locate_relative(offset, this);
	//WARNING: coupling
	*mOutputStream << mCombatableSettings.mIdentifiableSettings.mName << "'s position is now: "
		<< mMovableSettings.mPosition.x << ":" << mMovableSettings.mPosition.y << '\n' << '\n';
	/*std::cout << std::endl << mCombatableSettings.mIdentifiableSettings.mName << "'s position is now: " 
		<< mMovableSettings.mPosition.x << ":" << mMovableSettings.mPosition.y << std::endl << std::endl;*/
}

//void ICharacter::trigger(const Trigger trigger){// no parameters, only responses
//	switch (trigger)
//	{
//	case Trigger::attack:
//		break;
//	case Trigger::getAttacked:
//		std::cout << getName() << " yells: " <<"HEEEELP! I am getting attackhed!";
//		break;
//	default:
//		break;
//	}
//}

bool ICharacter::operator==(const ICharacter& rhs) const{
	return (this == &rhs);
}

bool ICharacter::operator!=(const ICharacter& rhs) const {
	return !((*this) == rhs);
}

ICharacter& ICharacter::operator=(const ICharacter& rhs){
	if (this != &rhs){
		mCombatableSettings = rhs.mCombatableSettings;
		mMovableSettings = rhs.mMovableSettings;
		mOutputStream = rhs.mOutputStream;
	}
	return *this;
}

ICharacter::operator std::string() const {
	return mCombatableSettings.mIdentifiableSettings.mName + " " + std::to_string(mCombatableSettings.mStatisticsSettings.mHealth);
}