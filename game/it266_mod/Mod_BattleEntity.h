#ifndef Mod_BattleEntity_h
#define Mod_BattleEntity_h

#include "../../idlib/precompiled.h"
#include "./Mod_Battle.h"

class Mod_BattleEntity {
	virtual void HandleRoundEvent(idStr str) = 0;
	virtual void ChooseAction(Mod_Battle battle) = 0;
	virtual void ExecuteAction(Mod_Battle battle) = 0;
	virtual void TakeDamage(Mod_Battle battle, int damage) = 0;
	virtual void Die(Mod_Battle battle) = 0;
};
#endif // !Mod_BattleEntity_h
