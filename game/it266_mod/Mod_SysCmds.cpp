#include "../../idlib/precompiled.h"
#pragma hdrstop

//	IT 266
#include "./Mod_SysCmds.h"
#include "../it266_mod/Mod_Node.h"
#include "../it266_mod/Mod_Constants.h"
#include "../it266_mod/Mod_SysCmds.h"
#include "../it266_mod/Mod_BattleSystem.h"
#include "../it266_mod/Mod_BattleCreature.h"
#include "../Game_local.h"
//	IT 266
void Cmd_UpgradeCard(Mod_Card* card)
{
	card->isUpgraded = true;
	card->OnUpgrade();
}

void Cmd_ToggleMap_f(const idCmdArgs& args) {
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player)
	{
		player->mapui->HandleNamedEvent("ToggleMap");
	}
}

void Cmd_DeleteNodeUI_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer() && gameLocal.GetLocalPlayer()->nodeui)
	{
		keyvalueClass <int, idUserInterface*> kvpair(2, gameLocal.GetLocalPlayer()->nodeui);
		int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
		if (index != -1)
			gameLocal.GetLocalPlayer()->uiList.removeAt(index);
		delete gameLocal.GetLocalPlayer()->nodeui;
		gameLocal.GetLocalPlayer()->nodeui = NULL;
	}
}
void Cmd_LoadRestNode()
{
	idStr		temp;
	if (gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_restui", "", temp)) {
		idUserInterface* ui = uiManager->FindGui(temp, true, true, false);
		gameLocal.GetLocalPlayer()->nodeui = ui;
		ui->Activate(true, gameLocal.time);
		ui->SetStateInt("isvisible", 1);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
			(MOD_NodeUiZ, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
	}
}
void Cmd_StartBattle(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idStr		temp;
		idPlayer* player = gameLocal.GetLocalPlayer();

		if (gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_battle", "", temp)) {
			idUserInterface* battlegui = uiManager->FindGui(temp, true, true, false);
			battlegui->Activate(true, gameLocal.time);
			battlegui->SetStateInt("isvisible", 1);
			player->nodeui = battlegui;
			player->uiList.push(keyvalueClass<int, idUserInterface*>(MOD_NodeUiZ, battlegui));

			player->battleSystem.Mod_StartBattle();
		}
	}
}
void Cmd_LoadShop(const idCmdArgs& args)
{
	idStr		temp;
	if (gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_shopui", "", temp)) {
		idPlayer* player = gameLocal.GetLocalPlayer();
		idUserInterface* ui = uiManager->FindGui(temp, true, true, false);
		gameLocal.GetLocalPlayer()->nodeui = ui;
		ui->Activate(true, gameLocal.time);
		ui->SetStateInt("isvisible", 1);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
			(MOD_NodeUiZ, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
		gameLocal.GetLocalPlayer()->nodeui = ui;

		player->battleSystem.GenerateCardOptions();

		player->battleSystem.cardOption1->AddCard(50, 80);
		player->battleSystem.cardOption1->ui->SetStateInt("isBuyable", 1);

		player->battleSystem.cardOption2->AddCard(250, 80);
		player->battleSystem.cardOption2->ui->SetStateInt("isBuyable", 1);

		player->battleSystem.cardOption3->AddCard(450, 80);
		player->battleSystem.cardOption3->ui->SetStateInt("isBuyable", 1);

		player->nodeui->SetStateInt("price1", 30);
		player->nodeui->SetStateInt("price2", 30);
		player->nodeui->SetStateInt("price3", 30);
	}
}
void BuyCard(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		if (player->playerGoldAmt >= 30)
		{
			if (player->battleSystem.cardOption1->ui->GetStateInt("thiscard") == 1)
			{
				player->battleSystem.cardOption1->ui->SetStateInt("thiscard", 0);
				player->mod_deck.push(player->battleSystem.cardOption1->Copy());
				player->battleSystem.cardOption1->HideCard();

			}
			else if (player->battleSystem.cardOption2->ui->GetStateInt("thiscard") == 1)
			{
				player->battleSystem.cardOption2->ui->SetStateInt("thiscard", 0);
				player->mod_deck.push(player->battleSystem.cardOption2->Copy());
				player->battleSystem.cardOption2->HideCard();
			}
			else
			{
				player->battleSystem.cardOption3->ui->SetStateInt("thiscard", 0);
				player->mod_deck.push(player->battleSystem.cardOption3->Copy());
				player->battleSystem.cardOption3->HideCard();
			}
			player->playerGoldAmt -= 30;
			player->mapui->SetStateInt("player_gold", player->playerGoldAmt);
		}
	}
}
void CloseShop(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer()) {
		idPlayer* player = gameLocal.GetLocalPlayer();

		gameLocal.GetLocalPlayer()->uiList.removeAt(gameLocal.GetLocalPlayer()->uiList.indexOf(keyvalueClass<int, idUserInterface*>
			(MOD_NodeUiZ, gameLocal.GetLocalPlayer()->nodeui)));
		delete gameLocal.GetLocalPlayer()->nodeui;
		gameLocal.GetLocalPlayer()->nodeui = NULL;

		delete player->battleSystem.cardOption1;
		delete player->battleSystem.cardOption2;
		delete player->battleSystem.cardOption3;

		player->battleSystem.cardOption1 = NULL;
		player->battleSystem.cardOption2 = NULL;
		player->battleSystem.cardOption3 = NULL;
	}

}
//	Given a node, hides all relevant gui and loads the correct gui
void Cmd_LoadNode(const idCmdArgs& args, Mod_Node node)
{
	if (gameLocal.GetLocalPlayer())
		gameLocal.GetLocalPlayer()->battleSystem.currentFloor++;
	switch (node.type)
	{

	case node.MonsterNode:
		gameLocal.Printf("Loading Battle Ui\n");
		gameLocal.GetLocalPlayer()->battleSystem.fightingElite = false;
		Cmd_StartBattle(args);
		break;
	case node.EliteNode:
		gameLocal.Printf("Loading Elite Battle Ui\n");
		gameLocal.GetLocalPlayer()->battleSystem.fightingElite = true;
		Cmd_StartBattle(args);
		break;
	case node.RestNode:
	{
		gameLocal.Printf("Loading RestNode Ui\n");
		Cmd_LoadRestNode();
		break;
	}
	case node.ShopNode:
	{
		gameLocal.Printf("Loading Shop\n");
		Cmd_LoadShop(args);
	}
	case node.NotNode:
	default:
		break;
	}
}
void Cmd_SetActiveNode_f(const idCmdArgs& args) {
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (!player)
		return;
	int x = atoi(args.Argv(1));
	int y = atoi(args.Argv(2));
	gameLocal.Printf("Activating Node (%d %d)\n", x, y);
	for (int i = 0; i < player->mod_map.connections.size(); i++)
	{
		int fromx = player->mod_map.connections.get(i).fromx;
		int fromy = player->mod_map.connections.get(i).fromy;
		int tox = player->mod_map.connections.get(i).tox;
		int toy = player->mod_map.connections.get(i).toy;
		{
			char varname[64];
			char intBuffer[8];

			strcpy(varname, "node_");
			strcat(varname, itoa(tox, intBuffer, 10));
			strcat(varname, "_");
			strcat(varname, itoa(toy, intBuffer, 10));
			strcat(varname, "_available");

			//	 if from x == x from y == y
			player->mapui->SetStateFloat(varname, 1);
		}
		{
			char varname[64];
			char intBuffer[8];

			strcpy(varname, "node_");
			strcat(varname, itoa(fromx, intBuffer, 10));
			strcat(varname, "_");
			strcat(varname, itoa(fromy, intBuffer, 10));
			strcat(varname, "_available");

			//	 if from x == x from y == y
			player->mapui->SetStateFloat(varname, 1);
		}
	}
	for (int i = 0; i < player->mod_map.connections.size(); i++)
	{
		int fromx = player->mod_map.connections.get(i).fromx;
		int fromy = player->mod_map.connections.get(i).fromy;
		int tox = player->mod_map.connections.get(i).tox;
		int toy = player->mod_map.connections.get(i).toy;

		if (fromx != x || fromy != y)
			continue;
		char varname[64];
		char intBuffer[8];

		strcpy(varname, "node_");
		strcat(varname, itoa(tox, intBuffer, 10));
		strcat(varname, "_");
		strcat(varname, itoa(toy, intBuffer, 10));
		strcat(varname, "_available");

		//	 if from x == x from y == y
		player->mapui->SetStateFloat(varname, 0);
	}
	player->mapui->HandleNamedEvent("SetAvailable");
	Cmd_LoadNode(args, player->mod_map.nodes[x][y]);
}
/*
void Cmd_ActivateNode_f(const idCmdArgs& args) {
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (!player)
		return;
	int x = atoi(args.Argv(1));
	int y = atoi(args.Argv(2));
	gameLocal.Printf("Activating Node (%d %d)\n", x, y);
}
*/
void Cmd_OpenDeck_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (!player)
		return;
	player->deckui->SetStateInt("isvisible", 1);
	player->deckui->SetStateFloat("verticalOffset", 0);
	for (int i = 0; i < player->mod_deck.size(); i++)
	{
		int x = i % 4;
		int y = i / 4;
		Mod_Card* card = player->mod_deck.get(i);
		if (card == NULL)
			continue;
		card->AddCard(20 + 154 * x, y * 188);
	}
}
void Cmd_CloseDeck_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (!player)
		return;
	player->deckui->SetStateInt("isvisible", 0);
	for (int i = 0; i < player->mod_deck.size(); i++)
		player->mod_deck.get(i)->HideCard();
}
void Cmd_ToggleDeck_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (!player)
		return;
	if (player->deckui->GetStateInt("isvisible") == 0)
		Cmd_OpenDeck_f(args);
	else
		Cmd_CloseDeck_f(args);
}
void Cmd_PlayerDebug_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		gameLocal.Printf("Number of cards in deck: %d\n", player->mod_deck.size());
		gameLocal.Printf("Cards:\n");
		/*
		for (int i = 0; i < player->mod_deck.size();i++)
		{
			gameLocal.Printf("\t%s\n", player->mod_deck.get(i)->name);
			player->mod_deck.get(i)->AddCard(50*i, 50 *i);
		}
		*/
		player->mod_deck.get(0)->AddCard(50, 50);
		player->mod_deck.get(0)->HideCard();
		//	gameLocal.Printf("");
		//	gameLocal.Printf("");
	}
}
void Cmd_Sleep_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		int maxHealth = player->inventory.maxHealth;
		player->health = player->health + (int)(.30 * maxHealth) > maxHealth ?
			maxHealth : player->health + (int)(.30 * maxHealth);
		player->mapui->SetStateInt("player_health", player->health);
	}
}
void Cmd_ShowUpgradeMenu_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		for (int i = 0; i < player->mod_deck.size(); i++)
		{
			if (!(player->mod_deck.get(i)->isUpgraded))
				break;
			if (i == player->mod_deck.size() - 1)
				return;
		}
		player->deckui->SetStateInt("isvisible", 1);
		for (int i = 0; i < player->mod_deck.size(); i++)
		{
			if (player->mod_deck.get(i)->isUpgraded)
				continue;
			int x = i % 4;
			int y = i / 4;
			idUserInterface* ui;
			ui = player->mod_deck.get(i)->AddCard(20 + 154 * x, y * 188);
			ui->SetStateInt("isUpgradeable", 1);
		}
	}
}
void Cmd_HideUpgradeMenu_f()
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		player->deckui->SetStateInt("isvisible", 0);
		for (int i = 0; i < player->mod_deck.size(); i++)
		{
			if (player->mod_deck.get(i)->ui == NULL)
				continue;
			player->mod_deck.get(i)->HideCard();
			player->mod_deck.get(i)->ui->SetStateInt("isUpgradeable", 0);
		}
	}
}
void Cmd_ShowUpgradeCard_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();

		idStr temp;
		gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_confirmui", "", temp);
		player->confirmui = uiManager->FindGui(temp, true, true, false);
		player->confirmui->Activate(true, gameLocal.time);
		player->confirmui->SetStateInt("isvisible", 1);

		keyvalueClass<int, idUserInterface*> kvpair(MOD_DeckUiZ, player->confirmui);
		player->uiList.push(kvpair);
		player->uiList.sort();

		int cardIndex = -1;
		for (int i = 0; i < player->mod_deck.size(); i++)
		{
			if (player->mod_deck.get(i)->ui == NULL)
				continue;
			if (player->mod_deck.get(i)->ui->GetStateInt("thisCard") == 1)
			{
				cardIndex = i;
				player->mod_deck.get(i)->ui->SetStateInt("thisCard", 0);
				break;
			}
		}
		Cmd_HideUpgradeMenu_f();
		player->deckui->SetStateInt("isvisible", 1);
		player->mod_deck.get(cardIndex)->AddCard(201, 32);
		player->cardTarget = player->mod_deck.get(cardIndex);

	}
}

void Cmd_UpgradeBack_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		if (player->confirmui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_DeckUiZ, player->confirmui);
			int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
			if (index != -1)
				gameLocal.GetLocalPlayer()->uiList.removeAt(index);
			delete player->confirmui;
			player->confirmui = NULL;
			Cmd_ShowUpgradeMenu_f(args);
		}
	}
}
void Cmd_UpgradeConfirm_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		if (player->confirmui)
		{
			keyvalueClass <int, idUserInterface*> kvpair(MOD_DeckUiZ, player->confirmui);
			int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
			if (index != -1)
				gameLocal.GetLocalPlayer()->uiList.removeAt(index);
			delete player->confirmui;
			player->confirmui = NULL;
			Cmd_UpgradeCard(player->cardTarget);
			Cmd_HideUpgradeMenu_f();
		}
	}
}

void Cmd_EndTurn_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		Cmd_UnselectCard_f(args);
		gameLocal.Printf("Ending turn\n");
		player->battleSystem.SendRoundEvent("PlayerRoundEnd");
	}
}
void Cmd_StartTurn_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		player->battleSystem.SendRoundEvent("PlayerRoundStart");
	}
}
void Cmd_SelectBattleCard_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		if (player->cardTarget)
		{
			player->cardTarget->ui->SetStateInt("verticalOffset", 0);
			player->uiList.removeAt(
				player->uiList.indexOf(keyvalueClass<int, idUserInterface*>(
					MOD_SelectedCard, player->cardTarget->ui)));
			player->uiList.push(keyvalueClass<int, idUserInterface*>(
				player->cardTarget->currentZ, player->cardTarget->ui));
			player->uiList.sort();
		}
		Mod_PlayerBattleCreature* playerCreature = player->battleSystem.mod_battleplayer;
		int cardIndex = -1;
		for (int i = 0; i < playerCreature->mod_deck->hand.size(); i++)
		{
			if (playerCreature->mod_deck->hand.get(i)->ui->GetStateInt("thisCard") == 1)
			{
				cardIndex = i;
				playerCreature->mod_deck->hand.get(i)->ui->SetStateInt("thisCard", 0);
				break;
			}
		}
		if (cardIndex == -1)
			return;
		player->cardTarget = playerCreature->mod_deck->hand.get(cardIndex);
		player->cardTarget->ui->SetStateInt("verticalOffset",
			player->cardTarget->ui->GetStateInt("verticalOffset") - 100);
		player->uiList.removeAt(
			player->uiList.indexOf(keyvalueClass<int, idUserInterface*>(
				player->cardTarget->currentZ, player->cardTarget->ui)));
		player->uiList.push(keyvalueClass<int, idUserInterface*>(
			MOD_SelectedCard, player->cardTarget->ui));
		player->uiList.sort();
	}
}
void Cmd_UnselectCard_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		if (player->cardTarget)
		{
			player->cardTarget->ui->SetStateInt("verticalOffset", 0);
			player->uiList.removeAt(
				player->uiList.indexOf(keyvalueClass<int, idUserInterface*>(
					MOD_SelectedCard, player->cardTarget->ui)));
			player->uiList.push(keyvalueClass<int, idUserInterface*>(
				player->cardTarget->currentZ, player->cardTarget->ui));
			player->uiList.sort();
			player->cardTarget = NULL;
		}
	}
}
void Cmd_SelectTarget_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		if (player->cardTarget == NULL)
			return;
		for (int i = 0; i < player->battleSystem.enemies->size(); i++)
		{
			if (!player->battleSystem.enemies->get(i)->isDead && 
				player->battleSystem.enemies->get(i)->ui->GetStateInt("thisTarget") == 1)
			{
				player->battleSystem.enemies->get(i)->ui->SetStateInt("thisTarget", 0);
				player->enemyTarget = player->battleSystem.enemies->get(i);
				break;
			}
		}
		if (player->enemyTarget == NULL)
		{
			gameLocal.Printf("Enemy null\n");
			return;
		}
		Cmd_ExecuteCard_f(args);
	}
}
void Cmd_ExecuteCard_f(const idCmdArgs& args)
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player && player->battleSystem.battleStarted)
	{
		if (player->cardTarget == NULL)
			return;
		if (player->cardTarget->CanBePlayed())
		{
			//... oops :(
			Mod_Card* cardtarget = player->cardTarget;
			Cmd_UnselectCard_f(args);
			player->cardTarget = cardtarget;
			player->cardTarget->Execute();
			player->battleSystem.mod_battleplayer->mod_deck->DiscardCard(player->cardTarget);
			player->battleSystem.CheckStatus();
			player->cardTarget = NULL;
			player->enemyTarget = NULL;
		}
		else
		{
			Cmd_UnselectCard_f(args);
			player->enemyTarget = NULL;
		}
	}
}
void Cmd_WinBattle()
{
	ShowRewardScreen();
}
void Cmd_WinBattle_f(const idCmdArgs& args)
{
	Cmd_WinBattle();
}
void ShowRewardScreen()
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		idStr temp;
		player->spawnArgs.GetString("it266_reward", "", temp);
		player->nodeui = uiManager->FindGui(temp, true, true, false);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
			(MOD_NodeUiZ, player->nodeui));
		gameLocal.GetLocalPlayer()->uiList.sort();

		player->nodeui->Activate(true, gameLocal.time);
		player->nodeui->SetStateInt("isvisible", 1);
		player->nodeui->SetStateInt("goldvisible", 1);
		player->nodeui->SetStateInt("cardvisible", 1);
		
		temp = "";
		temp += player->battleSystem.CalculateGoldReward();
		temp += " gold";
		player->nodeui->SetStateString("goldreward", temp);
	}
}
void CloseRewardScreen(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		gameLocal.GetLocalPlayer()->uiList.removeAt(
			gameLocal.GetLocalPlayer()->uiList.indexOf(
			keyvalueClass<int, idUserInterface*>
			(MOD_NodeUiZ, player->nodeui)));
		gameLocal.GetLocalPlayer()->uiList.sort();
		delete player->nodeui;
		player->nodeui = NULL;
	}
}
void CollectGoldReward(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		player->playerGoldAmt += player->battleSystem.goldReward;
		player->mapui->SetStateInt("player_gold", player->playerGoldAmt);
		player->nodeui->SetStateInt("goldvisible", 0);
	}
}
void ShowCardReward(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		player->battleSystem.GenerateCardOptions();

		player->battleSystem.cardOption1->AddCard(50,80);
		player->battleSystem.cardOption1->ui->SetStateInt("isReward", 1);

		player->battleSystem.cardOption2->AddCard(250, 80);
		player->battleSystem.cardOption2->ui->SetStateInt("isReward", 1);

		player->battleSystem.cardOption3->AddCard(450, 80);
		player->battleSystem.cardOption3->ui->SetStateInt("isReward", 1);

		idStr temp;
		player->spawnArgs.GetString("it266_skipcard", "", temp);
		player->confirmui = uiManager->FindGui(temp, true, true, false);
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
			(MOD_BattleCharacter, player->confirmui));
		gameLocal.GetLocalPlayer()->uiList.sort();
		player->confirmui->SetStateInt("isvisible", 1);
	}
}
void CancelCard(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();

		delete player->battleSystem.cardOption1;
		delete player->battleSystem.cardOption2;
		delete player->battleSystem.cardOption3;
		
		player->battleSystem.cardOption1 = NULL;
		player->battleSystem.cardOption2 = NULL;
		player->battleSystem.cardOption3 = NULL;
		
		gameLocal.GetLocalPlayer()->uiList.removeAt(
			gameLocal.GetLocalPlayer()->uiList.indexOf(
				keyvalueClass<int, idUserInterface*>
				(MOD_BattleCharacter, player->confirmui)));
		gameLocal.GetLocalPlayer()->uiList.sort();
		delete player->confirmui;
		player->confirmui = NULL;
	}

}
void AddRewardCard(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
		if (player->battleSystem.cardOption1->ui->GetStateInt("thiscard") == 1)
			player->mod_deck.push(player->battleSystem.cardOption1->Copy());
		else if (player->battleSystem.cardOption2->ui->GetStateInt("thiscard") == 1)
			player->mod_deck.push(player->battleSystem.cardOption2->Copy());
		else
			player->mod_deck.push(player->battleSystem.cardOption3->Copy());
		CancelCard(args);
		player->nodeui->SetStateInt("cardvisible", 0);
	}
}