#include "../../idlib/precompiled.h"
#include "Mod_Card.h"
#include "keyvalueClass.h"

#include "Mod_BattleCreature.h"
#include "Mod_BattleSystem.h"
#pragma hdrstop
idUserInterface* Mod_Card::AddCard(float x, float y, const char* cardgui, int zMod)
{
	if (gameLocal.GetLocalPlayer())
	{
		idStr temp;
		if (!ui)
		{
			gameLocal.GetLocalPlayer()->spawnArgs.GetString(cardgui, "", temp);
			ui = uiManager->FindGui(temp, true, true, false);
			ui->Activate(true, gameLocal.time);
			currentZ = guiZ + zMod;
			gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
				(currentZ, ui));
			gameLocal.GetLocalPlayer()->uiList.sort();
		}
		else
		{
			ChangeZ(zMod);
		}
		ui->SetStateFloat("cardx", x);
		ui->SetStateFloat("cardy", y);

		/*	If only it was this simple; for some reason having a variable image draws it over
		*	every other gui element
		*	Options:	
				- Create a card gui for every single possible card art
		*		- Create a windowDef inside a card gui with every single possible card art
		gameLocal.GetLocalPlayer()->spawnArgs.GetString(cardArt, "", temp);
		ui->SetStateString("cardart", temp);
		*/
		gameLocal.GetLocalPlayer()->spawnArgs.GetString(name, "", temp);
		if (isUpgraded)
			temp += "+";
		ui->SetStateString("cardname", temp);
		temp = cardText;
		if (isUpgraded)
			temp += "+";
		gameLocal.GetLocalPlayer()->spawnArgs.GetString(temp, "", temp);
		
		ui->SetStateString("cardtext", temp);
		temp = "";
		temp += currentCost;
		
		ui->SetStateString("cardcost", temp);
		ui->SetStateInt("isvisible", 1);
		return ui;
	}
	return NULL;
}
idUserInterface* Mod_Card::AddBattleCard(float x, float y, int zMod)
{
	AddCard(x, y, "it266_battlecard", zMod);
	ui->SetStateInt("inBattle", 1);
	gameLocal.GetLocalPlayer()->uiList.sort();
	return ui;
}
bool Mod_Card::CanBePlayed()
{
	return this->currentCost <=
		gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->currentEnergy;
}
void Mod_Card::ChangeZ(int newZmod)
{
	if (gameLocal.GetLocalPlayer()->uiList.indexOf(keyvalueClass<int, idUserInterface*>
		(currentZ, ui)) != -1)
	{
		gameLocal.GetLocalPlayer()->uiList.removeAt(
			gameLocal.GetLocalPlayer()->uiList.indexOf(keyvalueClass<int, idUserInterface*>
				(currentZ, ui)));
	}
	currentZ = guiZ + newZmod;
	gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
		(currentZ, ui));
	gameLocal.GetLocalPlayer()->uiList.sort();
}
void Mod_Card::HideCard()
{
	if (ui)
	{
		ui->SetStateInt("isvisible", 0);
	}
}
void Mod_Card::DeleteUI()
{
	gameLocal.Printf("Card ");
	if (ui)
	{
		keyvalueClass <int, idUserInterface*> kvpair(currentZ, ui);
		int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
		if (index != -1)
			gameLocal.GetLocalPlayer()->uiList.removeAt(index);
		delete ui;

		gameLocal.Printf("Deleting\n");
	}
}
void Mod_Card::Execute()
{

	gameLocal.GetLocalPlayer()->battleSystem.mod_battleplayer->ChangeEnergyByCost(this->currentCost);
}
Mod_Card* Mod_Card::Copy()
{
	return NULL;
}
void Mod_Card::OnUpgrade()
{

}