#include "NonPlayerCharacter.h"

NonPlayerCharacter::NonPlayerCharacter(const CombatableSettings& combatableSettings, const MovableSettings<ICharacter*>& movableSettings, IOutputStream& outputStream) :
ICharacter(combatableSettings, movableSettings, outputStream)
{

}

NonPlayerCharacter::NonPlayerCharacter(const NonPlayerCharacter& rhs) : ICharacter(rhs){

}

NonPlayerCharacter::~NonPlayerCharacter(){

}

bool NonPlayerCharacter::operator==(const NonPlayerCharacter& rhs){
	return ICharacter::operator==(rhs);
}
bool NonPlayerCharacter::operator!=(const NonPlayerCharacter& rhs){
	return !((*this) == rhs);
}

NonPlayerCharacter& NonPlayerCharacter::operator=(const NonPlayerCharacter& rhs){
	if (this != &rhs){
		ICharacter::operator=(rhs);
	}
	return *this;
}

void NonPlayerCharacter::trigger(const Trigger pTrigger){// no parameters, only responses
	switch (pTrigger)
	{
	case Trigger::attack:
		if (!isDead()){
			if (mCombatableSettings.mLastAttacker){
				dealDamage(*mCombatableSettings.mLastAttacker, *this);
			}
		}
		break;
	case Trigger::getAttacked:
		if (!isDead()){
			*mOutputStream << getName() << " yells: " << "Aaaaghhhh!" << '\n';
		}
		else{
			*mOutputStream << "*SMASH*" << '\n';
			*mOutputStream << getName() << " is dead." << '\n';
		}
		trigger(Trigger::attack);
		break;
	default:
		break;
	}
}