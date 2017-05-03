#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H
#include "ICharacter.h"
#include "IAutoOption.h"
class PlayerCombatManager;

class PlayerCharacter : public ICharacter, public IControllable {
public: 
	PlayerCharacter(
		const CombatableSettings& combatableSettings, 
		const MovableSettings<ICharacter*>& movableSettings,
		const QuotesSettings& quoteSettings,
		IOutputStream& outputStream,
		IAutoOption<ICharacter*>& targetOption
		);

	PlayerCharacter(const PlayerCharacter& rhs) = delete;
	virtual ~PlayerCharacter();

	bool operator==(const PlayerCharacter& rhs) = delete;
	bool operator!=(const PlayerCharacter& rhs) = delete;
	PlayerCharacter& operator=(const PlayerCharacter& rhs) = delete;

	virtual void control(const Action action) override;
	virtual void trigger(const Trigger trigger) override;
protected:
	IAutoOption<ICharacter*>& mTargetOption;
};
#endif