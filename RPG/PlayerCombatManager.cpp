//#include "PlayerCombatManager.h"
//
//PlayerCombatManager::PlayerCombatManager(){
//
//}
//
//PlayerCombatManager& PlayerCombatManager::getInstance(){
//	static PlayerCombatManager instance;
//	return instance;
//}
//
//void PlayerCombatManager::execute(ICharacter& character){
//	//simulate random or calculated initiative of characters on site (like in tactical games)
//	//std::set<ICharacter*> enemyCharactersAtSite = mMap.getAllAtPositionWhere(mPlayerCharacter.getPosition(), [](ICharacter* c){return (c->getFaction().first != Faction::player); });
//	ICharacter* chosenEnemy = &(character.chooseTarget());
//	character.dealDamage(*chosenEnemy);
//	//let everybody choose an action
//	//*chosenEnemy.trigger(Trigger::getAttacked);
//}