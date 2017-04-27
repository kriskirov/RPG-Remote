#ifndef I_CHARACTER_H
#define I_CHARACTER_H
#include "IIdentifiable.h"
#include "IStatistics.h"
#include "ICombatable.h"
#include "IMovable.h"
#include "ITriggerable.h"
#include "IControllable.h"
#include "Position.h"
#include "Map.h"
#include <string>
#include "Faction.h"
#include "CombatableSettings.h"
#include "MovableSettings.h"
#include "IOption.h"
#include "IOutputStream.h"

class ICharacter : public ICombatable, public IMovable {
public:
	//ICharacter(const std::string& name, const std::pair<Faction,std::string> faction, RPG::Map<ICharacter*>& map, const Position& position, float damage, float health);
	ICharacter(const CombatableSettings& combatableSettings, const MovableSettings<ICharacter*>& movableSettings, IOutputStream& outputStream);
	ICharacter(const ICharacter& rhs);
	virtual ~ICharacter();

	bool operator==(const ICharacter& rhs) const;
	bool operator!=(const ICharacter& rhs) const;
	ICharacter& operator=(const ICharacter& rhs);

	std::string getName() override;
	std::pair<Race,std::string> getRace() override;
	virtual std::pair<Faction, std::string> getFaction() override;
	float getDamage() override;
	virtual void dealDamage(ICombatable& target, ICombatable& dealer) override;
	virtual void takeDamage(float amount, ICombatable* attacker) override;
	ICombatable* getLastAttacker() override;
	float getHealth() override;
	bool isDead() override;
	virtual int getSpeed() override;
	Position getPosition() override;
	void setPosition(Position& pos) override;
	virtual void move(Position& offset) override;
	//virtual void control(Action& action) override;
	//virtual void trigger(const Trigger trigger) override;
	operator std::string() const;

protected:
	CombatableSettings mCombatableSettings;
	MovableSettings<ICharacter*> mMovableSettings;
	IOutputStream* mOutputStream;
	/*std::string mName;
	std::string mRace;
	std::pair<Faction, std::string> mFaction;
	float mDamage;
	float mHealth;
	int mSpeed;
	Position mPosition;
	RPG::Map<ICharacter*>* mMap;*/
};
#endif // !CHARACTER_H
