#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(
	const CombatableSettings& combatableSettings, 
	const MovableSettings<ICharacter*>& movableSettings, 
	const QuotesSettings& quoteSettings,
	IOutputStream& outputStream, 
	IAutoOption<ICharacter*>& targetOption
	) :
	ICharacter(combatableSettings,movableSettings,quoteSettings,outputStream),
	mTargetOption(targetOption)
{

}

PlayerCharacter::~PlayerCharacter(){

}

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
			mTargetOption.set_options(mMovableSettings.mMap.getAllAtPositionWhere(
				mMovableSettings.mPosition,
				[](ICharacter* character){return character->getFaction().first != Faction::player; })
				);
			mTargetOption.output();
			mTargetOption.input();
			ICharacter* chosenTarget = mTargetOption.get_result();
			if (chosenTarget){
				trigger(Trigger::attack);
				dealDamage(*chosenTarget, *this);
			}
		}
	}
}

void PlayerCharacter::trigger(const Trigger trigger){
	switch (trigger)
	{
	case Trigger::attack:
		*mOutputStream << mQuoteSettings.mAttack;
		break;
	case Trigger::getAttacked:
		if (!isDead()){
			*mOutputStream << mQuoteSettings.mGetAttacked;
		}
		else{
			*mOutputStream << mQuoteSettings.mGetAttackedWhileDead;
		}
		break;
	default:
		break;
	}
}