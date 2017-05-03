#include "GameConditions.h"

GameConditions::GameConditions(
	RPG::Map<ICharacter*>& mapToClearFromEnemies, 
	ICombatable& playerCharacter, 
	IOutputStream& outputStream) : 
mMapToClearFromEnemies(mapToClearFromEnemies),
mPlayerCharacter(playerCharacter),
mOutputStream(outputStream)
{

}

GameConditions& GameConditions::operator=(const GameConditions& rhs) {
	mMapToClearFromEnemies = rhs.mMapToClearFromEnemies;
	mPlayerCharacter = rhs.mPlayerCharacter;
	mOutputStream = rhs.mOutputStream;
	return *this;
}

bool GameConditions::win(){
	std::set<ICharacter*> livingEnemiesSet = mMapToClearFromEnemies.getAllWhere( 
		[](ICharacter* character){ return !character->isDead() && character->getFaction().first == Faction::playerEnemy; } 
	);
	if (livingEnemiesSet.empty()){
		mOutputStream << "\nAll enemies are dead.\nYOU WIN!" << '\n';
		return true;
	}
	else{
		return false;
	}
}

bool GameConditions::lose(){
	if (mPlayerCharacter.isDead()){
		mOutputStream << "\nYou are DEAD!\nGAME OVER!" << '\n';
		return true;
	}
	else{
		return false;
	}
}