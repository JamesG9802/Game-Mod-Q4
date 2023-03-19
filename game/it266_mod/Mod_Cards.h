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
		: Mod_Card_Attack(1, "it266_card_setupstrike_name", "it266_card_setupstrike_art", "it266_card_setupstrike_text", 7, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_SetupStrike(isUpgraded); }
	void Execute();
};
class Mod_Card_Parry : public Mod_Card_Attack {
public:
	Mod_Card_Parry(bool isUpgraded)
		: Mod_Card_Attack(1, "it266_card_parry_name", "it266_card_parry_art", "it266_card_parry_text", 6, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_Parry(isUpgraded); }
	void Execute();
};
class Mod_Card_HeavyBlow : public Mod_Card_Attack {
public:
	Mod_Card_HeavyBlow(bool isUpgraded)
		: Mod_Card_Attack(2, "it266_card_heavyblow_name", "it266_card_heavyblow_art", "it266_card_heavyblow_text", 16, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_HeavyBlow(isUpgraded); }
	void Execute();
};
class Mod_Card_Slam : public Mod_Card_Attack {
public:
	Mod_Card_Slam(bool isUpgraded)
		: Mod_Card_Attack(1, "it266_card_slam_name", "it266_card_slam_art", "it266_card_slam_text", 0, isUpgraded) {}
	Mod_Card* Copy() override { return new Mod_Card_Slam(isUpgraded); }
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
class Mod_Card_Prepare : public Mod_Card_Block {
public:
	Mod_Card_Prepare(bool isUpgraded)
		: Mod_Card_Block(1, "it266_card_prepare_name", "it266_card_prepare_art", "it266_card_prepare_text", 5, isUpgraded)
	{
		if (isUpgraded)
		{
			currentCost = 0;
			cost = 0;
		}
	}
	void Execute();
	void OnUpgrade();
	Mod_Card* Copy() override
	{
		return new Mod_Card_Prepare(isUpgraded);
	}
};
class Mod_Card_Fortify : public Mod_Card_Block {
public:
	Mod_Card_Fortify(bool isUpgraded)
		: Mod_Card_Block(1, "it266_card_fortify_name", "it266_card_fortify_art", "it266_card_fortify_text", 0, isUpgraded)
	{
	}
	void Execute();
	Mod_Card* Copy() override
	{
		return new Mod_Card_Fortify(isUpgraded);
	}
};