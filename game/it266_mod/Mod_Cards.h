#include "../../idlib/precompiled.h"
#include "Mod_Card.h"
#pragma hdrstop

class Mod_Card_Attack : public Mod_Card {
public:
	int damage;
	Mod_Card_Attack(int cost, char* name, char* cardArt, char* cardText, int damage) 
		: Mod_Card(cost, name, cardArt, cardText)
	{
		this->damage = damage;
	}
	void Execute()
	{

	}
};
class Mod_Card_Strike : public Mod_Card_Attack {
public:
	Mod_Card_Strike() : Mod_Card_Attack(1, "it266_card_strike_name", "it266_card_strike_art", "it266_card_strike_text", 6)
	{

	}
};
/*
void AddCard(vectorClass<keyvalueClass<int, idUserInterface*>> uiList, float x, float y)
{
	idStr temp;
	gameLocal.GetLocalPlayer()->spawnArgs.GetString("it266_card", "", temp);
	idUserInterface* card = uiManager->FindGui(temp, true, false, false);

	card->Activate(true, gameLocal.time);
	card->SetStateFloat("cardx", x);
	card->SetStateFloat("cardy", y);

	gameLocal.GetLocalPlayer()->spawnArgs.GetString(cardArt, "", temp);
	card->SetStateString("cardart", temp);

	gameLocal.GetLocalPlayer()->spawnArgs.GetString(name, "", temp);
	card->SetStateString("cardname", "gfx/guis/cards/card");

	card->SetStateInt("isvisible", 1);

	gameLocal.GetLocalPlayer()->uiList.push(keyvalueClass<int, idUserInterface*>
		(2, card));
	gameLocal.GetLocalPlayer()->uiList.sort();
}
*/