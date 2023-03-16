#pragma once

class Mod_BattleSystem;

class Mod_BattleCreature
{
public:
	int currentHP, maxHP;
	int block;
	Mod_BattleCreature(int currentHP, int maxHP)
	{
		this->currentHP = currentHP;
		this->maxHP = maxHP;
		block = 0;
	}
	virtual void HandleRoundEvent(idStr str) = 0;
	virtual void ChooseAction(Mod_BattleSystem battleSystem) = 0;
	virtual void Die() = 0;
	virtual void ExecuteAction(Mod_BattleSystem battleSystem) = 0;
	virtual void TakeDamage(int damage) = 0;
};

class Mod_PlayerBattleCreature : Mod_BattleCreature
{

public:
	Mod_Deck* mod_deck;
	Mod_PlayerBattleCreature(int currentHP, int maxHP, vectorClass<Mod_Card*>* mod_deck) : Mod_BattleCreature(currentHP, maxHP)
	{
		this->mod_deck = new Mod_Deck(mod_deck);
	}
	~Mod_PlayerBattleCreature()
	{
		delete mod_deck;
	}
	void HandleRoundEvent(idStr str) override
	{
		if (str == "PlayerRoundStart")
		{
			mod_deck->DrawCard(5);
			block = 0;
		}
		else if (str == "PlayerRoundEnd")
		{
			mod_deck->DiscardHand();
		}
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