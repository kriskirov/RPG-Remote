#include "ConsoleController.h"
#include "ConsoleOption.h"
#include "ConsoleReader.h"
#include "PlayerCharacter.h"
#include "NonPlayerCharacter.h"
#include "ConsoleOutputStream.h"
#include "ConsoleInputStream.h"
#include "AutoConsoleOption.h"
#include "GameConditions.h"

using namespace std;

int main(){
	//Composition root

	QuotesSettings playerQuotes = QuotesSettings(
		"You shouts out: I shall not be stopped by evil!\n",
		"You agonizes: Ughhh...\n",
		"The sound *SMASH* comes from Your dead body.\n",
		"You are dead.\n"
		);

	QuotesSettings enemyQuotes = QuotesSettings(
		"Enemy groans: Fresh meat!\n",
		"Enemy cries in pain: AAArrrghhh!\n",
		"The sound *SMASH* comes from Your enemy's dead body.\n",
		"This enemy has died.\n"
		);

	ConsoleOutputStream consoleOutputStream = ConsoleOutputStream(cout);
	ConsoleInputStream consoleInputStream = ConsoleInputStream(cin);
	InputOutputStream ioStream = InputOutputStream(consoleInputStream, consoleOutputStream);

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

	unique_map<Race, string> gameRaces;
	gameRaces.add(Race::human, "Human");
	gameRaces.add(Race::troll, "Troll");

	RPG::Map<ICharacter*> map = RPG::Map<ICharacter*>(3, 3);
	
	Position pos1 = Position(0, 0);
	Position pos2 = Position(2, 2);

	consoleOutputStream << "Welcome to the world of \"Another RPG\"!\n\n"
		<< "Customize Your character's details...\n";

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
	CombatableSettings combSettings = CombatableSettings(idenSettings, statSettings, nullptr);
	MovableSettings<ICharacter*> movSettings = MovableSettings<ICharacter*>(map,pos1);

	AutoConsoleOption<ICharacter*> targetOption = AutoConsoleOption<ICharacter*>(ioStream,"Choose an enemy target:","No enemies at site.");
	
	playChar = new PlayerCharacter(combSettings, movSettings, playerQuotes, consoleOutputStream, targetOption);
	GameConditions gameConditions = GameConditions(map,*playChar,consoleOutputStream);

	consoleOutputStream << '\n' << "Welcome to the world of \"Another RPG\"!"
		<< "\nGame goal is: Kill all enemies on the map." << '\n'
		<< "Initial coordinates: " << playChar->getPosition().x << ":" << playChar->getPosition().y << '\n';

	ConsoleReader consoleReader = ConsoleReader(cin);

	ConsoleOption<string> playerControlOption = ConsoleOption<string>(
		"\nEnter action:"
		"\n'w' - move North"
		"\n's' - move South"
		"\n'a' - move West"
		"\n'd' - move East"
		"\n'e' - attack Enemy"
		"\n'q' - quit Game"
		"\n",
		[&playerControls](string input){
		return playerControls.isValidValue(input);
		},
		"Invalid action. The available actions are:"
		"\n'w' - move North"
		"\n's' - move South"
		"\n'a' - move West"
		"\n'd' - move East"
		"\n'e' - attack Enemy"
		"\n'q' - quit Game"
		"\n"
	);

	ConsoleController<string> playerController (*playChar, playerControlOption, playerControls);
	
	IdentifiableSettings enemyIdenSettings = IdentifiableSettings(
		"Un'Goro", 
		gameRaces.getPair(Race::human), 
		gameFactions.getPair(Faction::playerEnemy)
		);

	StatisticsSettings enemyStatSettings = StatisticsSettings(2.0f, 10.0f, 1);
	
	CombatableSettings enemyCombSettings = CombatableSettings(enemyIdenSettings, enemyStatSettings, nullptr);
	MovableSettings<ICharacter*> enemyMovSettings = MovableSettings<ICharacter*>(map, pos2);
	NonPlayerCharacter* enemy = new NonPlayerCharacter(enemyCombSettings, enemyMovSettings, enemyQuotes, consoleOutputStream);

	while (!(playerController.get_last_input() != playerControls.getPair(Action::quitGame).second) != !gameConditions.lose() != gameConditions.win()){
		playerController.execute();
	}

	consoleOutputStream << '\n' << "The world of \"Another RPG\" awaits Your return, farewell!" << '\n';
	
	delete playChar;
	delete enemy;
	ConsoleOption<string> exitKeyOption = ConsoleOption<string>("Enter \"quit\" to terminate the application...",
		[](string x){
		return (x == "quit");
	},
	"The command to quit is \"quit\".");
	exitKeyOption.output();
	exitKeyOption.input();
	return 0;
}