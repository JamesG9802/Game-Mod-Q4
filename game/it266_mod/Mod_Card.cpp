#include "Mod_Card.h"
#include "keyvalueClass.h"

#pragma hdrstop
void Mod_Card::AddCard(float x, float y)
{
	idStr temp;
	HideCard();
	gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_card", "", temp);
	ui = uiManager->FindGui(temp, true, false, false);

	ui->Activate(true, gameLocal.time);
	ui->SetStateFloat("cardx", x);
	ui->SetStateFloat("cardy", y);

	gameLocal.GetLocalPlayer()->spawnArgs.GetString(cardArt, "", temp);
	ui->SetStateString("cardart", temp);

	gameLocal.GetLocalPlayer()->spawnArgs.GetString(name, "", temp);
	ui->SetStateString("cardname", "gfx/guis/cards/card");

	ui->SetStateInt("isvisible", 1);

	gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
		(2, ui));
	gameLocal.GetLocalPlayer()->uiList.sort();
}
void Mod_Card::HideCard()
{
	if (ui)
	{
		int index = gameLocal.GetLocalPlayer()->uiList.indexOf(keyvalueClass <int, idUserInterface*>(2, ui));
		if(index != -1)
			gameLocal.GetLocalPlayer()->uiList.removeAt(index);
		delete ui;
	}
}
void Mod_Card::Execute()
{

}