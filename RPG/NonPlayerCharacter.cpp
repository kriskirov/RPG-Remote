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

void NonPlayerCharacter::trigger(const Trigger trigger){// no parameters, only responses
	switch (trigger)
	{
	case Trigger::attack:
		break;
	case Trigger::getAttacked:
		*mOutputStream << getName() << " yells: " << "HEEEELP! I am getting attacked!" << '\n';
		if (mLastAttacker){
			dealDamage(*mLastAttacker, *this);
		}
		break;
	default:
		break;
	}
}