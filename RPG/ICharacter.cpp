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

int ICharacter::getSpeed(){
	return mCombatableSettings.mStatisticsSettings.mSpeed;
}

void ICharacter::dealDamage(ICombatable& character, ICombatable& dealer){
	mLastAttacker = &dealer;
	character.takeDamage(mCombatableSettings.mStatisticsSettings.mDamage);
	trigger(Trigger::getAttacked);
}

void ICharacter::takeDamage(float damage){
	mCombatableSettings.mStatisticsSettings.mHealth -= damage;
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