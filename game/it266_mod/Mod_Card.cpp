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

		gameLocal.GetLocalPlayer()->spawnArgs.GetString(cardArt, "", temp);
		ui->SetStateString("cardart", temp);

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

		/*
		const char* command;
		sysEvent_t	ev;
		ev = sys->GenerateMouseMoveEvent(-2000, -2000);
		command = ui->HandleEvent(&ev, gameLocal.time);
		gameLocal.GetLocalPlayer()->HandleGuiCommands(gameLocal.GetLocalPlayer(), command);

		// move to an absolute position
		ev = sys->GenerateMouseMoveEvent(gameLocal.GetLocalPlayer()->GetMouseX(), gameLocal.GetLocalPlayer()->GetMouseY());
		command = ui->HandleEvent(&ev, gameLocal.time);
		gameLocal.GetLocalPlayer()->HandleGuiCommands(gameLocal.GetLocalPlayer(), command);
		*/
		gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
			(guiZ, ui));
		gameLocal.GetLocalPlayer()->uiList.sort();
		return ui;
	}
	return NULL;
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