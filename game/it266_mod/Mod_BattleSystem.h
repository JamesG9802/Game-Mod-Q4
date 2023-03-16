#pragma once

class Mod_PlayerBattleCreature;

class Mod_BattleSystem {
public:
	Mod_PlayerBattleCreature* mod_battleplayer;
	Mod_BattleSystem();
	~Mod_BattleSystem();
	void Mod_StartBattle();
	void SendRoundEvent(idStr str);
};