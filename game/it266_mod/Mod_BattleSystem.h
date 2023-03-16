#pragma once

class Mod_PlayerBattleCreature;

class Mod_BattleSystem {
public:
	bool battleStarted = false;

	Mod_PlayerBattleCreature* mod_battleplayer;
	Mod_BattleSystem();
	~Mod_BattleSystem();
	void Mod_StartBattle();
	void SendRoundEvent(idStr str);
};