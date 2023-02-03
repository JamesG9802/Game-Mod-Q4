#include "../../idlib/precompiled.h"
#pragma hdrstop
/*
	Map
	.	List<Node>
	Node
	.	List<Node> NextNodes
	>	BattleNode
	>	RestNode
	>	ShopNode
	BattleEntity
	.	Health
	.	List<BattleEntity> ExecuteAction()
	>	Player
	>	Pokemon
	>	Enemy
	Deck
	.	List<Card>
	.	DrawCard
	.	Reshuffle
	Battle
	.	List<Card> graveyard
	.	List<BattleEntity> playerTeam
	.	List<BattleEntity> enemyTeam

*/
#include <stdint.h>
int a() {
	return -1;
}
