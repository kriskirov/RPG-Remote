#include "GameConditions.h"

GameConditions::GameConditions(RPG::Map<ICharacter*>& mapToClearFromEnemies, ICombatable& playerCharacter) : mMapToClearFromEnemies(mapToClearFromEnemies),
mPlayerCharacter(playerCharacter){

}

GameConditions& GameConditions::operator=(const GameConditions& rhs) {
	mMapToClearFromEnemies = rhs.mMapToClearFromEnemies;
	mPlayerCharacter = rhs.mPlayerCharacter;
	return *this;
}

bool GameConditions::win(){
	std::set<ICharacter*> livingEnemiesSet = mMapToClearFromEnemies.getAllWhere( 
		[](ICharacter* character){ return !character->isDead() && character->getFaction().first == Faction::playerEnemy; } 
	);
	return livingEnemiesSet.empty();
}

bool GameConditions::lose(){
	return mPlayerCharacter.isDead();
}