#include "../../idlib/precompiled.h"

#include "Mod_Cards.h"
#include "Mod_Card.h"

#include "Mod_BattleCreature.h"
#include "Mod_BattleSystem.h"

void Mod_Card_Block::Execute()
{
	Mod_Card::Execute();
	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->AddBlock(block);
}
void Mod_Card_Defend::Execute()
{
	Mod_Card_Block::Execute();
}