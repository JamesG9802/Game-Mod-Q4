#ifndef Mod_Card_h
#define Mod_Card_h
#include "Mod_Constants.h"
#include "../../idlib/precompiled.h"
#include "vectorClass.h"
#include "keyvalueClass.h"

class idPlayer;
class Mod_Card {
protected:
	int guiZ = MOD_CardUiZ;
public:
	idUserInterface* ui = NULL;
	int currentZ = 0;


	int currentCost;

	int cost; 
	char* name;
	char* cardArt;
	char* cardText; 

	bool isUpgraded;

	Mod_Card(int cost, char* name, char* cardArt, char* cardText, bool isUpgraded = false)
	{
		this->cost = cost;
		this->name = name;
		this->cardArt = cardArt;
		this->cardText = cardText;

		this->isUpgraded = isUpgraded;

		currentCost = cost;
	}
	~Mod_Card()
	{
		DeleteUI();
	}
	/// <summary>
	/// Activates the card's effect.
	/// </summary>
	virtual void Execute();

	/// <summary>
	/// Makes the card visible to the screen.
	/// </summary>
	/// <param name="uiList"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual idUserInterface* AddCard(float x, float y, const char* cardgui = "it266_card", int zMod = 0);
	virtual idUserInterface* AddBattleCard(float x, float y, int zMod = 0);
	virtual bool CanBePlayed();
	virtual void ChangeZ(int newZ);
	virtual void HideCard();
	virtual void DeleteUI();
	virtual Mod_Card* Copy();
};
#endif
