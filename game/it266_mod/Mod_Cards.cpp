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
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->nextTurnEnergyMod++;
	if (isUpgraded)
		gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->nextTurnEnergyMod++;
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