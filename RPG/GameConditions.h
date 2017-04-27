#ifndef GAME_CONDITIONS_H
#define GAME_CONDITIONS_H
#include "ICharacter.h"
#include "Map.h"
class GameConditions{
public:
	GameConditions(RPG::Map<ICharacter*>& mapToClearFromEnemies, ICombatable& playerCharacter);
	GameConditions(const GameConditions& rhs) = default;
	GameConditions& operator=(const GameConditions& rhs);

	bool win();
	bool lose();
private:
	RPG::Map<ICharacter*>& mMapToClearFromEnemies;
	ICombatable& mPlayerCharacter;
};
#endif
