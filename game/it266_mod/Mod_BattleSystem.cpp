#include "../../idlib/precompiled.h"
#include "./vectorClass.h"
#include "Mod_BattleSystem.h"
#include "Mod_BattleCreature.h"
#include "Mod_SysCmds.h"
#include "Mod_Cards.h"
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
	if (cardOption1)
		delete cardOption1;
	if (cardOption2)
		delete cardOption2;
	if (cardOption3)
		delete cardOption2;
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
void Mod_BattleSystem::Mod_EndBattle()
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	player->cardTarget = NULL;
	player->enemyTarget = NULL;

	player->uiList.removeAt(
		player->uiList.indexOf(keyvalueClass<int, idUserInterface*>(MOD_NodeUiZ, player->nodeui)));
	delete player->nodeui;
	player->nodeui = NULL;

	battleStarted = false;
	player->health = mod_battleplayer->currentHP;
	delete mod_battleplayer;
	mod_battleplayer = NULL;
	while (enemies->size() != 0)
		delete enemies->pop();
}
void Mod_BattleSystem::SendRoundEvent(idStr str)
{
	mod_battleplayer->HandleRoundEvent(str);
	for (int i = 0; i < enemies->size(); i++)
	{
		enemies->get(i)->HandleRoundEvent(str);
	}
	if (str == "PlayerRoundEnd")
	{
		idStr temp = "EnemyRoundStart";
		SendRoundEvent(temp);
	}
	if (str == "EnemyRoundStart")
	{
		idStr temp = "EnemyRoundEnd";
		SendRoundEvent(temp);
	}
	if (str == "EnemyRoundEnd")
	{
		idStr temp = "PlayerRoundStart";
		SendRoundEvent(temp);
	}
}
void Mod_BattleSystem::AddEnemy(Mod_EnemyBattleCreature* enemy)
{
	enemies->push(enemy);
}
void Mod_BattleSystem::CreateEnemyList()
{
	if (currentFloor == 1)
	{
		Mod_EnemyBattleCreature* enemy1 = new Mod_EnemyBattleCreature(10, 10, GetRandomEnemyName(), 330, 55, currentFloor);
		AddEnemy(enemy1);
		return;
	}
	int difficulty = currentFloor;
	if (fightingElite)
		difficulty = (int)(difficulty * 1.5);
	int random = gameLocal.random.RandomInt(100);
	if (random < 33)
	{
		int temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * 2.5 + temprandom,
			(int)(10 + difficulty) * 2.5 + temprandom, GetRandomEnemyName(), 330, 55, difficulty));
	}
	else if (random < 66)
	{
		int temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * 1.25 + temprandom,
			(int)(10 + difficulty) * 1.25 + temprandom, GetRandomEnemyName(), 330, 55, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * 1.25 + temprandom,
			(int)(10 + difficulty) * 1.25 + temprandom, GetRandomEnemyName(), 500, 55, difficulty));
	}
	else if (random < 90)
	{
		int temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .75 + temprandom,
			(int)(10 + difficulty) * .75 + temprandom, GetRandomEnemyName(), 330, 55, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .75 + temprandom,
			(int)(10 + difficulty) * .75 + temprandom, GetRandomEnemyName(), 500, 55, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .75 + temprandom,
			(int)(10 + difficulty) * .75 + temprandom, GetRandomEnemyName(), 330, 220, difficulty));
	}
	else
	{
		int temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .5 + temprandom,
			(int)(10 + difficulty) * .5 + temprandom, GetRandomEnemyName(), 330, 55, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .5 + temprandom,
			(int)(10 + difficulty) * .5 + temprandom, GetRandomEnemyName(), 500, 55, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .5 + temprandom,
			(int)(10 + difficulty) * .5 + temprandom, GetRandomEnemyName(), 330, 220, difficulty));
		temprandom = gameLocal.random.RandomInt(5);
		AddEnemy(new Mod_EnemyBattleCreature(
			(int)(10 + difficulty) * .5 + temprandom,
			(int)(10 + difficulty) * .5 + temprandom, GetRandomEnemyName(), 500, 220, difficulty));
	}
}
void Mod_BattleSystem::CheckStatus()
{
	bool allDead = true;
	for (int i = 0; i < enemies->size(); i++)
	{
		if (enemies->get(i)->isDead == false)
		{
			allDead = false;
			break;
		}
	}
	if (allDead)
	{
		Mod_EndBattle();
		Cmd_WinBattle();
	}
}
int Mod_BattleSystem::CalculateGoldReward()
{
	goldReward = 10 + currentFloor * gameLocal.random.RandomInt(5);
	if (fightingElite)
		goldReward *= 3;
	return goldReward;
}
void Mod_BattleSystem::GenerateCardOptions()
{
	if (cardOption1 != NULL)
	{
		delete cardOption1;
		delete cardOption2;
		delete cardOption3;
	}
	const int cardamt = 6;
	int arr[cardamt];
	for (int i = 0; i < cardamt; i++)
		arr[i] = i;
	for (int i = 0; i < cardamt; i++)
	{
		int j = gameLocal.random.RandomInt(cardamt);
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	cardOption1 = GetCard(arr[0]);
	cardOption2 = GetCard(arr[1]);
	cardOption3 = GetCard(arr[2]);

}
const char* Mod_BattleSystem::GetRandomEnemyName()
{
	int num = gameLocal.random.RandomInt(10);
	switch (num)
	{
	case 0: return "Pikachu";
	case 1: return "Bulbasaur";
	case 2: return "Pidgey";
	case 3: return "Muk";
	case 4: return "Charizard";
	case 5: return "Ash";
	case 6: return "Cloyster";
	case 7: return "Onyx";
	case 8: return "Ekans";
	case 9: return "Ditto";
	default: return "Pokemon";
	}
}
Mod_Card* Mod_BattleSystem::GetRandomCard()
{
	int num = gameLocal.random.RandomInt(6);
	return GetCard(num);
}
Mod_Card* Mod_BattleSystem::GetCard(int i)
{
	switch (i)
	{
	case 0: return new Mod_Card_Parry(false);
	case 1: return new Mod_Card_Prepare(false);
	case 2: return new Mod_Card_SetupStrike(false);
	case 3: return new Mod_Card_HeavyBlow(false);
	case 4: return new Mod_Card_Fortify(false);
	default:
	case 5: return new Mod_Card_Slam(false);
	}
}