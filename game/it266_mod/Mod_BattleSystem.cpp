#include "../../idlib/precompiled.h"
#include "./vectorClass.h"
#include "Mod_BattleSystem.h"
#include "Mod_BattleCreature.h"

class Mod_EnemyBattleCreature;

Mod_BattleSystem::Mod_BattleSystem()
{
	this->mod_battleplayer = NULL;
	this->enemies = new vectorClass< Mod_EnemyBattleCreature*>();
}
Mod_BattleSystem::~Mod_BattleSystem()
{
	if(this->mod_battleplayer != NULL)
		delete this->mod_battleplayer;
}
void Mod_BattleSystem::Mod_StartBattle()
{
	battleStarted = true;

	idPlayer* player = gameLocal.GetLocalPlayer();
	player->cardTarget = NULL;
	this->mod_battleplayer = new Mod_PlayerBattleCreature(player->health, player->inventory.maxHealth, &player->mod_deck);
	this->mod_battleplayer->mod_deck->Shuffle();
	CreateEnemyList();
	SendRoundEvent("PlayerRoundStart");
}
void Mod_BattleSystem::SendRoundEvent(idStr str)
{
	mod_battleplayer->HandleRoundEvent(str);
}
void Mod_BattleSystem::AddEnemy(Mod_EnemyBattleCreature* enemy)
{
	enemies->push(enemy);
}
void Mod_BattleSystem::CreateEnemyList()
{
	Mod_EnemyBattleCreature* enemy1 = new Mod_EnemyBattleCreature(10, 10,"Pikachu", 330, 40);
	Mod_EnemyBattleCreature* enemy2 = new Mod_EnemyBattleCreature(10, 10, "Charizard", 500, 40);
	Mod_EnemyBattleCreature* enemy3 = new Mod_EnemyBattleCreature(10, 10, "Squirtle", 330, 190);
	Mod_EnemyBattleCreature* enemy4 = new Mod_EnemyBattleCreature(10, 10, "Potato", 500, 190);

	AddEnemy(enemy1);
	AddEnemy(enemy2);
	AddEnemy(enemy3);
	AddEnemy(enemy4);
}