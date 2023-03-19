#pragma once

template <typename T> class vectorClass;
class Mod_PlayerBattleCreature;
class Mod_EnemyBattleCreature;
class Mod_Card;
class Mod_BattleSystem {
public:
	/**/
	int goldReward = 0;
	Mod_Card* cardOption1 = NULL, *cardOption2 = NULL, *cardOption3 = NULL;
	/**/
	int currentFloor = 0;
	bool battleStarted = false;
	bool fightingElite = false;

	Mod_PlayerBattleCreature* mod_battleplayer;
	vectorClass<Mod_EnemyBattleCreature*>* enemies;
	Mod_BattleSystem();
	~Mod_BattleSystem();
	void Mod_StartBattle();
	void Mod_EndBattle();
	void SendRoundEvent(idStr str);
	void AddEnemy(Mod_EnemyBattleCreature* enemy);
	void CreateEnemyList();
	void CheckStatus();
	int CalculateGoldReward();
	void GenerateCardOptions();
	const char* GetRandomEnemyName();
	Mod_Card* GetRandomCard();
	Mod_Card* GetCard(int i);
};