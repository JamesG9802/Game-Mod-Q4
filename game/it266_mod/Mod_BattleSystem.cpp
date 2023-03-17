#include "../../idlib/precompiled.h"
#include "Mod_BattleSystem.h"
#include "Mod_BattleCreature.h"

Mod_BattleSystem::Mod_BattleSystem()
{
	this->mod_battleplayer = NULL;
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
	SendRoundEvent("PlayerRoundStart");
}
void Mod_BattleSystem::SendRoundEvent(idStr str)
{
	mod_battleplayer->HandleRoundEvent(str);
}