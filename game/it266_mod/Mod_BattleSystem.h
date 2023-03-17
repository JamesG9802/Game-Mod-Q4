#pragma once

template <typename T> class vectorClass;
class Mod_PlayerBattleCreature;
class Mod_EnemyBattleCreature;
class Mod_BattleSystem {
public:
	bool battleStarted = false;

	Mod_PlayerBattleCreature* mod_battleplayer;
	vectorClass<Mod_EnemyBattleCreature*>* enemies;
	Mod_BattleSystem();
	~Mod_BattleSystem();
	void Mod_StartBattle();
	void SendRoundEvent(idStr str);
	void AddEnemy(Mod_EnemyBattleCreature* enemy);
	void CreateEnemyList();
};