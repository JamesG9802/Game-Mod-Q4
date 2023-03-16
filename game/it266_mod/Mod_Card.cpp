#include "../../idlib/precompiled.h"
#include "Mod_Card.h"
#include "keyvalueClass.h"
#pragma hdrstop
idUserInterface* Mod_Card::AddCard(float x, float y)
{
	if (gameLocal.GetLocalPlayer())
	{
		idStr temp;
		if (!ui)
		{
			gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_card", "", temp);
			ui = uiManager->FindGui(temp, true, true, false);
			ui->Activate(true, gameLocal.time);
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
		
		if (gameLocal.GetLocalPlayer()->uiList.indexOf(keyvalueClass<int, idUserInterface*>
			(guiZ, ui)) == -1)
		{
			gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
				(guiZ, ui));
			gameLocal.GetLocalPlayer()->uiList.sort();
		}
		return ui;
	}
	return NULL;
}
idUserInterface* Mod_Card::AddBattleCard(float x, float y)
{
	AddCard(x, y);
	ui->SetStateInt("inBattle", 1);
	return ui;
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
	if (ui)
	{
		keyvalueClass <int, idUserInterface*> kvpair(guiZ, ui);
		int index = gameLocal.GetLocalPlayer()->uiList.indexOf(kvpair);
		if (index != -1)
			gameLocal.GetLocalPlayer()->uiList.removeAt(index);
		delete ui;
	}
}
void Mod_Card::Execute()
{

}
Mod_Card* Mod_Card::Copy()
{
	return NULL;
}