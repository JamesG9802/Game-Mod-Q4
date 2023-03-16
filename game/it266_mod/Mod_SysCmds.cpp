#include "../../idlib/precompiled.h"
#pragma hdrstop

//	IT 266
#include "./Mod_SysCmds.h"
#include "../it266_mod/Mod_Node.h"
#include "../it266_mod/Mod_Constants.h"
#include "../it266_mod/Mod_SysCmds.h"
#include "../it266_mod/Mod_BattleSystem.h"
#include "../Game_local.h"
//	IT 266
void Cmd_UpgradeCard(Mod_Card* card)
{
	card->isUpgraded = true;
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
			(2, ui));
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
			player->uiList.push(keyvalueClass<int, idUserInterface*>(2, battlegui));

			player->battleSystem.Mod_StartBattle();
		}
	}
}
//	Given a node, hides all relevant gui and loads the correct gui
void Cmd_LoadNode(const idCmdArgs& args, Mod_Node node)
{
	switch (node.type)
	{

	case node.MonsterNode:
		gameLocal.Printf("Loading Battle Ui\n");
		Cmd_StartBattle(args);
		break;
	case node.EliteNode:
	case node.RestNode:
	{
		gameLocal.Printf("Loading RestNode Ui\n");
		Cmd_LoadRestNode();
		break;
	}
	case node.ShopNode:
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
	}
}
void Cmd_ShowUpgradeMenu_f(const idCmdArgs& args)
{
	if (gameLocal.GetLocalPlayer())
	{
		idPlayer* player = gameLocal.GetLocalPlayer();
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
			Cmd_UpgradeCard(player->cardTarget);
			Cmd_HideUpgradeMenu_f();
		}
	}
}

void Cmd_EndTurn_f(const idCmdArgs& args)
{
	gameLocal.Printf("Ending turn\n");
}
