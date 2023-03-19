#pragma once

class Mod_BattleSystem;

class Mod_BattleCreature
{
public:
	idUserInterface* ui = NULL;
	int currentHP, maxHP;
	int block;

	bool isDead = false;
	Mod_BattleCreature(int currentHP, int maxHP)
	{
		this->currentHP = currentHP;
		this->maxHP = maxHP;
		block = 0;
	}
	virtual void HandleRoundEvent(idStr str) = 0;
	virtual void ChooseAction(Mod_BattleSystem* battleSystem) = 0;
	virtual void Die() = 0;
	virtual void ExecuteAction(Mod_BattleSystem* battleSystem) = 0;
	void SetupUI(bool isPlayer, int x = 15, int y = 90)
	{
		if (ui == NULL)
		{
			idStr temp;

			gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_battlecreature", "", temp);
			ui = uiManager->FindGui(temp, true, true, false);
		}
		ui->SetStateInt("isvisible", 1);
		ui->SetStateInt("xpos", x);
		ui->SetStateInt("ypos", y);
		ui->SetStateInt("isplayer", isPlayer);

		ui->SetStateInt("mod_playerhealth", currentHP);
		ui->SetStateInt("mod_playermaxhealth", maxHP);
		ui->SetStateInt("blockamt", block);

		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>(MOD_BattleCharacter, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
	}
	virtual void TakeDamage(int damage)
	{
		if (isDead)
			return;
		if (damage > 0)	//	Positive damage
		{
			if (block > 0)	// has block
			{
				block -= damage;
				if (block < 0)	// damage > block, block disappears and damage continues
				{
					damage = -block;
					block = 0;
				}
				else
					damage = 0;
			}
			currentHP = currentHP - damage > 0 ? currentHP - damage : 0;
		}
		else if (damage < 0)	//	Negative Damage; heal
			currentHP = currentHP - damage < maxHP ? currentHP - damage : maxHP;
		ui->SetStateInt("mod_playerhealth", currentHP);
		ui->SetStateInt("blockamt", block);
		if (currentHP == 0)
			Die();
	}
	void AddBlock(int blockAmt)
	{
		SetBlock(block + blockAmt);
	}
	void SetBlock(int newBlock)
	{
		block = newBlock;
		ui->SetStateInt("blockamt", newBlock);
	}
};

class Mod_PlayerBattleCreature : public Mod_BattleCreature
{

public:
	int nextTurnEnergyMod = 0;
	int currentEnergy = 0;
	Mod_Deck* mod_deck = NULL;
	Mod_PlayerBattleCreature(int currentHP, int maxHP, vectorClass<Mod_Card*>* mod_deck) 
		: Mod_BattleCreature(currentHP, maxHP)
	{
		this->mod_deck = new Mod_Deck(mod_deck);
		SetupUI(true);
		ui->SetStateString("mod_name", "Player");
	}
	~Mod_PlayerBattleCreature()
	{
		if(mod_deck)
			delete mod_deck;
		if (ui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_BattleCharacter, ui);
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
			SetEnergy(3);
			ChangeEnergyByCost(nextTurnEnergyMod);
			nextTurnEnergyMod = 0;
			mod_deck->DrawCard(5);
			SetBlock(0);
		}
		else if (str == "PlayerRoundEnd")
		{
			mod_deck->DiscardHand();
		}
	}
	void ChooseAction(Mod_BattleSystem* battleSystem) override
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
	void ExecuteAction(Mod_BattleSystem* battleSystem) override{}
	void TakeDamage(int damage) override
	{
		Mod_BattleCreature::TakeDamage(damage);
		gameLocal.GetLocalPlayer()->mapui->SetStateInt("player_health", currentHP);
		gameLocal.GetLocalPlayer()->mapui->SetStateInt("player_maxhealth", maxHP);
	}
	void ChangeEnergyByCost(int cost)
	{
		SetEnergy(currentEnergy - cost > 0 ? currentEnergy - cost : 0);
	}
	void SetEnergy(int newEnergy)
	{
		currentEnergy = newEnergy;
		gameLocal.GetLocalPlayer()->nodeui->SetStateInt("energyamt", currentEnergy);
	}
};
class Mod_EnemyBattleCreature : public Mod_BattleCreature
{
public:
	float difficulty = 0;
	int intent = -1;
	int intentAmt = 0;
	Mod_EnemyBattleCreature(int currentHP, int maxHP, const char* name, int x, int y, int difficulty)
		: Mod_BattleCreature(currentHP, maxHP)
	{
		this->difficulty = difficulty;
		SetupUI(false, x, y);
		ui->SetStateString("mod_name", name);
	}
	~Mod_EnemyBattleCreature()
	{
		if (ui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_BattleCharacter, ui);
			int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
			if (index != -1)
				gameLocal.GetLocalPlayer()->uiList.removeAt(index);
			delete ui;
		}
	}
	void ChooseAction(Mod_BattleSystem* battleSystem) override
	{
		idStr temp = "";
		intent = gameLocal.random.RandomInt(3);
		if (intent == 1 && gameLocal.random.RandomInt(100) < 33)
			intent = 0;
		else if (intent == 1 && gameLocal.random.RandomInt(100) < 66)
			intent = 2;
		switch (intent)
		{
		case 0:
		case 1:
			intentAmt = (gameLocal.random.RandomInt(5 +(int)(difficulty/2)) + 3 + difficulty);
			temp += intentAmt;
			ui->SetStateString("intentamt", temp);
			if (intent == 0)
				ui->HandleNamedEvent("Attack");
			else
				ui->HandleNamedEvent("AttackDefend");
			break;
		case 2:
		default:
			ui->SetStateString("intentamt", temp);
			ui->HandleNamedEvent("Defend");
			break;
		}
		gameLocal.Printf("Intent: %d\n", intent);
	}
	void Die() override
	{
		ui->SetStateInt("isvisible", 0);
		isDead = true;
	}
	void HandleRoundEvent(idStr str) override
	{
		if (isDead)
			return;
		if (str == "EnemyRoundStart")
		{
			SetBlock(0);
			ExecuteAction(&(gameLocal.GetLocalPlayer()->battleSystem));
		}
		else if (str == "PlayerRoundStart")
		{
			ChooseAction(&(gameLocal.GetLocalPlayer()->battleSystem));
		}
	}
	void ExecuteAction(Mod_BattleSystem* battleSystem) override
	{
		switch (intent)
		{
		case 0:
		case 1:
			battleSystem->mod_battleplayer->TakeDamage(intentAmt);
			if(intent == 0)
				break;
		case 2:
			AddBlock(5 +(int)(difficulty/2));
			break;
		}
	}
};