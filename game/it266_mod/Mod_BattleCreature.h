#pragma once

class Mod_BattleSystem;

class Mod_BattleCreature
{
public:
	Mod_BattleCreature()
	{

	}
	virtual void HandleRoundEvent(idStr str) = 0;
	virtual void ChooseAction(Mod_BattleSystem battleSystem) = 0;
	virtual void Die() = 0;
	virtual void ExecuteAction(Mod_BattleSystem battleSystem) = 0;
	virtual void TakeDamage(int damage) = 0;
};

class Mod_PlayerBattleCreature : Mod_BattleCreature
{
	Mod_PlayerBattleCreature() : Mod_BattleCreature()
	{

	}
	void HandleRoundEvent(idStr str) override
	{

	}
	void ChooseAction(Mod_BattleSystem battleSystem) override
	{

	}
	void Die() override
	{

	}
	void ExecuteAction(Mod_BattleSystem battleSystem) override
	{

	}
	void TakeDamage(int damage) override
	{

	}
};