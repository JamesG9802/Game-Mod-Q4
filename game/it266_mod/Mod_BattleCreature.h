#pragma once

class Mod_BattleSystem;

class Mod_BattleCreature
{
public:
	idUserInterface* ui = NULL;
	int currentHP, maxHP;
	int block;
	Mod_BattleCreature(int currentHP, int maxHP)
	{
		this->currentHP = currentHP;
		this->maxHP = maxHP;
		block = 0;
	}
	virtual void HandleRoundEvent(idStr str) = 0;
	virtual void ChooseAction(Mod_BattleSystem battleSystem) = 0;
	virtual void Die() = 0;
	virtual void ExecuteAction(Mod_BattleSystem battleSystem) = 0;
	virtual void TakeDamage(int damage) = 0;
};

class Mod_PlayerBattleCreature : public Mod_BattleCreature
{

public:
	Mod_Deck* mod_deck = NULL;
	Mod_PlayerBattleCreature(int currentHP, int maxHP, vectorClass<Mod_Card*>* mod_deck) 
		: Mod_BattleCreature(currentHP, maxHP)
	{
		idStr temp;
		this->mod_deck = new Mod_Deck(mod_deck);
		
		gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_battlecreature", "", temp);
		ui = uiManager->FindGui(temp, true, true, false);
		ui->SetStateInt("isvisible", 1);
		
		ui->SetStateInt("xpos", 15);
		ui->SetStateInt("ypos", 90);
		ui->SetStateInt("isplayer", 1);

		ui->SetStateString("mod_name", "Player");

		ui->SetStateInt("mod_playerhealth", currentHP);
		ui->SetStateInt("mod_playermaxhealth", maxHP);
		ui->SetStateInt("blockamt", block);

		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>(MOD_NodeUiZ, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
	}
	~Mod_PlayerBattleCreature()
	{
		if(mod_deck)
			delete mod_deck;
		if (ui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_NodeUiZ, ui);
			int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
			if (index != -1)
				gameLocal.GetLocalPlayer()->uiList.removeAt(index);
			delete ui;
		}
	}
	void HandleRoundEvent(idStr str) override
	{
		if (str == "PlayerRoundStart")
		{
			mod_deck->DrawCard(5);
			block = 0;
		}
		else if (str == "PlayerRoundEnd")
		{
			mod_deck->DiscardHand();
		}
	}
	void ChooseAction(Mod_BattleSystem battleSystem) override
	{

	}
	void Die() override
	{
		idStr temp;
		gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_lose", "", temp);
		idUserInterface* newui = uiManager->FindGui(temp, true, true, false);
		newui->SetStateInt("isvisible", 1);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>(999, newui));
	}
	void ExecuteAction(Mod_BattleSystem battleSystem) override
	{

	}
	void TakeDamage(int damage) override
	{
		if (damage > 0)
			currentHP = currentHP - damage > 0 ? currentHP - damage : 0;
		else if (damage < 0)
			currentHP = currentHP - damage < maxHP ? currentHP - damage : maxHP;
		ui->SetStateInt("mod_playerhealth", currentHP);
		if (currentHP == 0)
			Die();
	}
};
class Mod_EnemyBattleCreature : public Mod_BattleCreature
{
public:
	bool isDead = false;
	Mod_EnemyBattleCreature(int currentHP, int maxHP, const char* name, int x, int y)
		: Mod_BattleCreature(currentHP, maxHP)
	{
		idStr temp;

		gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_battlecreature", "", temp);
		ui = uiManager->FindGui(temp, true, true, false);
		ui->SetStateInt("isvisible", 1);

		ui->SetStateInt("xpos", x);
		ui->SetStateInt("ypos", y);
		ui->SetStateInt("isplayer", 0);

		ui->SetStateString("mod_name", name);

		ui->SetStateInt("mod_playerhealth", currentHP);
		ui->SetStateInt("mod_playermaxhealth", maxHP);
		ui->SetStateInt("blockamt", block);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>(MOD_NodeUiZ, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
	}
	~Mod_EnemyBattleCreature()
	{
		if (ui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_NodeUiZ, ui);
			int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
			if (index != -1)
				gameLocal.GetLocalPlayer()->uiList.removeAt(index);
			delete ui;
		}
	}
	void ChooseAction(Mod_BattleSystem battleSystem) override
	{

	}
	void Die() override
	{
		ui->SetStateInt("isvisible", 0);
	}
	void HandleRoundEvent(idStr str) override
	{
		if (isDead)
			return;
		if (str == "EnemyRoundStart")
		{
			block = 0;
		}
		else if (str == "PlayerRoundStart")
		{
		}
	}
	void ExecuteAction(Mod_BattleSystem battleSystem) override
	{

	}
	void TakeDamage(int damage) override
	{
		if (isDead)
			return;
		if (damage > 0)
			currentHP = currentHP - damage > 0 ? currentHP - damage : 0;
		else if (damage < 0)
			currentHP = currentHP - damage < maxHP ? currentHP - damage : maxHP;
		ui->SetStateInt("mod_playerhealth", currentHP);
		if (currentHP == 0)
			Die();
	}
};