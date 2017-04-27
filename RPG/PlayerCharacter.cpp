#include "PlayerCharacter.h"

//TODO: update constructors and operators
PlayerCharacter::PlayerCharacter(const CombatableSettings& combatableSettings, const MovableSettings<ICharacter*>& movableSettings, IOutputStream& outputStream, IAutoOption<ICharacter*>& targetOption) :
ICharacter(combatableSettings,movableSettings,outputStream),
mTargetOption(targetOption)
{

}

//PlayerCharacter::PlayerCharacter(const PlayerCharacter& rhs) : ICharacter(rhs), mPlayerCombatManager(rhs.mPlayerCombatManager){
//
//}

PlayerCharacter::~PlayerCharacter(){

}

//bool PlayerCharacter::operator==(const PlayerCharacter& rhs){
//	return ICharacter::operator==(rhs);
//}
//bool PlayerCharacter::operator!=(const PlayerCharacter& rhs){
//	return !((*this)==rhs);
//}

//PlayerCharacter& PlayerCharacter::operator=(const PlayerCharacter& rhs){
//	if (this != &rhs){
//		ICharacter::operator=(rhs);
//		mCombatableSettings = rhs.mCombatableSettings;
//		mMovableSettings = rhs.mMovableSettings;
//		mPlayerCombatManager = PlayerCombatManager::getInstance();
//	}
//	return *this;
//}

void PlayerCharacter::control(const Action action){
	if (!isDead()){
		switch (action){
		case Action::moveNorth:
			move(Position(0, mCombatableSettings.mStatisticsSettings.mSpeed));
			break;
		case Action::moveSouth:
			move(Position(0, -mCombatableSettings.mStatisticsSettings.mSpeed));
			break;
		case Action::moveWest:
			move(Position(-mCombatableSettings.mStatisticsSettings.mSpeed, 0));
			break;
		case Action::moveEast:
			move(Position(mCombatableSettings.mStatisticsSettings.mSpeed, 0));
			break;
		case Action::enterCombat:
			mTargetOption.set_options(mMovableSettings.mMap.getAllAtPositionWhere(mMovableSettings.mPosition,
				[](ICharacter* character){return character->getFaction().first != Faction::player; }));
			mTargetOption.output();
			mTargetOption.input();
			ICharacter* chosenTarget = mTargetOption.get_result();
			if (chosenTarget){
				trigger(Trigger::attack);
				dealDamage(*chosenTarget, *this);
			}
			else{
				*mOutputStream << "No enemies on site." << '\n';
			}
		}
	}
	else{
		*mOutputStream << "You are dead! No actions possible." << '\n';
	}
}

void PlayerCharacter::trigger(const Trigger trigger){// no parameters, only responses
	switch (trigger)
	{
	case Trigger::attack:
		*mOutputStream << getName() << " yells: " << "I am the almighty " << getName() << " and I am not afraid!" << '\n';
		break;
	case Trigger::getAttacked:
		if (!isDead()){
			*mOutputStream << getName() << " cries: " << "Arrrgh!" << '\n';
		}
		else{
			*mOutputStream << "*SMASH*" << '\n';
		}
		break;
	default:
		break;
	}
}