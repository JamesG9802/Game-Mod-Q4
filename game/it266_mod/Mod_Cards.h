#pragma once
#include "../../idlib/precompiled.h"
#include "Mod_Card.h"

#include "Mod_BattleCreature.h"
#include "Mod_BattleSystem.h"
#pragma hdrstop

class Mod_BattleSystem;
class Mod_PlayerBattleCreature;

class Mod_Card_Attack : public Mod_Card {
public:
	int damage;
	Mod_Card_Attack(int cost, char* name, char* cardArt, char* cardText, int damage) 
		: Mod_Card(cost, name, cardArt, cardText)
	{
		this->damage = damage;
	}
	void Execute() override { Mod_Card::Execute(); }
};
class Mod_Card_Strike : public Mod_Card_Attack {
public:
	Mod_Card_Strike() : Mod_Card_Attack(1, "it266_card_strike_name", "it266_card_strike_art", "it266_card_strike_text", 6) {}
	Mod_Card* Copy() { return new Mod_Card_Strike(); }
	void Execute() override { Mod_Card_Attack::Execute(); }
};
class Mod_Card_Block : public Mod_Card {
public:
	int block;
	Mod_Card_Block(int cost, char* name, char* cardArt, char* cardText, int block)
		: Mod_Card(cost, name, cardArt, cardText)
	{
		this->block = block;
	}
	void Execute();
};
class Mod_Card_Defend : public Mod_Card_Block {
public:
	Mod_Card_Defend() : Mod_Card_Block(1, "it266_card_defend_name", "it266_card_defend_art", "it266_card_defend_text", 5)
	{

	}
	void Execute();
	Mod_Card* Copy()
	{
		return new Mod_Card_Defend();
	}
};