#ifndef NON_PLAYER_CHARACTER_H
#define NON_PLAYER_CHARACTER_H

#include "ICharacter.h"

class NonPlayerCharacter : public ICharacter{
public:

	NonPlayerCharacter(
		const CombatableSettings& combatableSettings,
		const MovableSettings<ICharacter*>& movableSettings,
		const QuotesSettings& quoteSettings,
		IOutputStream& outputStream
		);

	NonPlayerCharacter(const NonPlayerCharacter& rhs);
	virtual ~NonPlayerCharacter();

	bool operator==(const NonPlayerCharacter& rhs);
	bool operator!=(const NonPlayerCharacter& rhs);
	NonPlayerCharacter& operator=(const NonPlayerCharacter& rhs);

	virtual void trigger(const Trigger trigger) override;
};
#endif