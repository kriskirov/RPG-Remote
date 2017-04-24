#include "ICharacter.h"
#include "Human.h"
#include "Troll.h"
#include "Map.h"
#include "ConsoleOption.h"
#include <istream>
#include <algorithm>
#include "ConsoleController.h"
#include "ConsoleOption.h"
#include "ConsoleReader.h"
#include "unique_map.h"
#include "Action.h"
#include "PlayerCharacter.h"
#include "MovableSettings.h"
#include "Race.h"
#include "PlayerCombatManager.h"
#include "NonPlayerCharacter.h"
#include "ConsoleOutputStream.h"
#include "AutoConsoleOption.h"

using namespace std;

int main(){;
	ConsoleOutputStream consoleOutputStream = ConsoleOutputStream(cout);

	unique_map<Action,string> playerControls;
	playerControls.add(Action::moveNorth,"w");
	playerControls.add(Action::moveSouth, "s");
	playerControls.add(Action::moveWest, "a");
	playerControls.add(Action::moveEast, "d");
	playerControls.add(Action::enterCombat, "e");
	playerControls.add(Action::quitGame, "q");

	unique_map<Faction, string> gameFactions;
	gameFactions.add(Faction::player, "Player");
	gameFactions.add(Faction::playerEnemy, "Player Enemy");

	//Faction playerFaction = Faction::player;
	
	//vector<string> races{ "Human", "Troll" };
	unique_map<Race, string> gameRaces;
	gameRaces.add(Race::human, "Human");
	gameRaces.add(Race::troll, "Troll");

	RPG::Map<ICharacter*> map = RPG::Map<ICharacter*>(3, 3);
	
	Position pos1 = Position(0, 0);
	Position pos2 = Position(2, 2);

	ConsoleOption<string> characterNameMenu = ConsoleOption<string>("Enter Your character's name: ", 
		[](string x){
		return (x.length() > 2);
	},
	"Invalid name. Name must be at least 3 characters long! ");
	
	characterNameMenu.output();
	characterNameMenu.input();
	string playerName = characterNameMenu.get_result();

	ConsoleOption<string> characterRaceMenu = ConsoleOption<string>("Enter Your character's race: ", 
		[&gameRaces](string input){
		return gameRaces.isValidValue(input);
	},
	"Invalid race. The available races are Human and Troll");
	characterRaceMenu.output();
	characterRaceMenu.input();
	Race pRace;
	gameRaces.getKey(characterRaceMenu.get_result(), pRace);
	std::pair<Race, string> playerRace = gameRaces.getPair(pRace);

	PlayerCharacter* playChar;
	IdentifiableSettings idenSettings = IdentifiableSettings(playerName, playerRace, gameFactions.getPair(Faction::player));
	StatisticsSettings statSettings = StatisticsSettings(5.0f, 30.0f, 1);
	CombatableSettings combSettings = CombatableSettings(idenSettings, statSettings);
	MovableSettings<ICharacter*> movSettings = MovableSettings<ICharacter*>(map,pos1);

	AutoConsoleOption<ICharacter*> targetOption = AutoConsoleOption<ICharacter*>("Choose an enemy target:","No options available.");
	
	playChar = new PlayerCharacter(combSettings, movSettings, consoleOutputStream, targetOption);
	
	//if (playerRace == "Human"){
		//playChar = new PlayerCharacter(playerName, gameFactions.getPair(Faction::player), map, pos1, 5, 30);
	//}
	//else if (playerRace == "Troll"){
		//playChar = (ICharacter*) new Troll(playerName, gameFactions.getPair(Faction::player), map, pos1, 5, 30);
	//}

	ConsoleReader consoleReader = ConsoleReader(cin);

	ConsoleOption<string> playerControlOption = ConsoleOption<string>("Enter action:\n'w' - move North\n's' - move South\n'a' - move West\n'd' - move East\n'e' - attack Enemy\n'q' - quit Game",
		[&playerControls](string input){
		return playerControls.isValidValue(input);
	},
		"Invalid action. The available actions are:\n'w' - move North\n's' - move South\n'a' - move West\n'd' - move East\n'e' - attack Enemy\n'q' - quit Game");

	ConsoleController<string> playerController (*playChar, playerControlOption, playerControls);// ConsoleController<string>(*playChar, playerControlOption, playerControls);
	
	IdentifiableSettings enemyIdenSettings = IdentifiableSettings("Un'Goro", gameRaces.getPair(Race::human), gameFactions.getPair(Faction::playerEnemy));
	StatisticsSettings enemyStatSettings = StatisticsSettings(2.0f, 10.0f, 1);
	CombatableSettings enemyCombSettings = CombatableSettings(enemyIdenSettings, enemyStatSettings);
	MovableSettings<ICharacter*> enemyMovSettings = MovableSettings<ICharacter*>(map, pos2);
	NonPlayerCharacter* enemy = new NonPlayerCharacter(enemyCombSettings, enemyMovSettings, consoleOutputStream);
	//Troll* enemy = new Troll("Un'Goro", gameFactions.getPair(Faction::playerEnemy), map, pos2, 3, 20);

	while (playerController.get_last_input() != "q"){
		playerController.execute();
	}

	consoleOutputStream << '\n' << "The world of \"Another RPG\" awaits Your return, farewell!" << '\n';
	
	delete playChar;
	delete enemy;
	return 0;
}