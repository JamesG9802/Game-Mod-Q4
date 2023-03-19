#include "../../idlib/precompiled.h"

#include "Mod_Cards.h"
#include "Mod_Card.h"

#include "Mod_BattleCreature.h"
#include "Mod_BattleSystem.h"
void Mod_Card_Attack::Execute() 
{
	Mod_Card::Execute();
	gameLocal.GetLocalPlayer()->enemyTarget->TakeDamage(damage);
}
void Mod_Card_Strike::Execute()
{
	if (isUpgraded)
		damage = 9;
	Mod_Card_Attack::Execute();
}
void Mod_Card_SetupStrike::Execute()
{
	Mod_Card_Attack::Execute();
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->nextTurnEnergyMod--;
	if (isUpgraded)
		gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->nextTurnEnergyMod--;
}
void Mod_Card_Parry::Execute()
{
	if (isUpgraded)
		damage = 9;
	Mod_Card_Attack::Execute();
	int block = 5;
	if (isUpgraded)
		block = 8;
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->AddBlock(block);
}
void Mod_Card_HeavyBlow::Execute()
{
	if (isUpgraded)
		damage = 25;
	Mod_Card_Attack::Execute();
}
void Mod_Card_Slam::Execute()
{
	if(isUpgraded)
		gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->AddBlock(3);
	damage = gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->block;
	Mod_Card_Attack::Execute();
}
void Mod_Card_Block::Execute()
{
	Mod_Card::Execute();
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->AddBlock(block);
}
void Mod_Card_Defend::Execute()
{
	if (isUpgraded)
		block = 8;
	Mod_Card_Block::Execute();
}
void Mod_Card_Prepare::Execute()
{
	Mod_Card_Block::Execute();
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->mod_deck->DrawCard(1);
}
void Mod_Card_Prepare::OnUpgrade()
{
	Mod_Card::OnUpgrade();
	cost = 0;
	currentCost = 0;
}
void Mod_Card_Fortify::Execute()
{
	block = gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->block;
	if (isUpgraded)
		block *= 2;
	Mod_Card_Block::Execute();
}