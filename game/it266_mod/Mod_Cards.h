#pragma once
#include "../../idlib/precompiled.h"
#include "Mod_Card.h"

#include "Mod_BattleCreature.h"
#include "Mod_BattleSystem.h"

class Mod_BattleSystem;
class Mod_PlayerBattleCreature;

class Mod_Card_Attack : public Mod_Card {
public:
	int damage;
	Mod_Card_Attack(int cost, char* name, char* cardArt, char* cardText, int damage, bool isUpgraded) 
		: Mod_Card(cost, name, cardArt, cardText, isUpgraded)
	{
		this->damage = damage;
	}
	void Execute();
};
class Mod_Card_Strike : public Mod_Card_Attack {
public:
	Mod_Card_Strike(bool isUpgraded)
		: Mod_Card_Attack(1, "it266_card_strike_name", "it266_card_strike_art", "it266_card_strike_text", 6, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_Strike(isUpgraded); }
	void Execute();
};
class Mod_Card_SetupStrike : public Mod_Card_Attack {
public:
	Mod_Card_SetupStrike(bool isUpgraded)
		: Mod_Card_Attack(1, "it266_card_setupstrike_name", "it266_card_setupstrike_art", "it266_card_setupstrike_text", 2, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_Strike(isUpgraded); }
	void Execute();
};
class Mod_Card_Block : public Mod_Card {
public:
	int block;
	Mod_Card_Block(int cost, char* name, char* cardArt, char* cardText, int block, bool isUpgraded)
		: Mod_Card(cost, name, cardArt, cardText, isUpgraded)
	{
		this->block = block;
	}
	void Execute();
};
class Mod_Card_Defend : public Mod_Card_Block {
public:
	Mod_Card_Defend(bool isUpgraded) 
		: Mod_Card_Block(1, "it266_card_defend_name", "it266_card_defend_art", "it266_card_defend_text", 5, isUpgraded)
	{

	}
	void Execute();
	Mod_Card* Copy() override
	{
		return new Mod_Card_Defend(isUpgraded);
	}
};