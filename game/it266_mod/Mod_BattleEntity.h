#ifndef Mod_BattleEntity_h
#define Mod_BattleEntity_h

class Mod_BattleEntity {
public:
	int currentHealth;
	int maxHealth;

	Mod_BattleEntity(int currentHealth, int maxHealth)
	{
		this->currentHealth = currentHealth;
		this->maxHealth = maxHealth;
	}
};

class Mod_PlayerBattleEntity : Mod_BattleEntity {
public:
	Mod_PlayerBattleEntity(int currentHealth, int maxHealth)
		: Mod_BattleEntity(currentHealth, maxHealth)
	{

	}
};
#endif // !Mod_BattleEntity_h
