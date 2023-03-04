#ifndef Mod_Card_h
#define Mod_Card_h
#include "../../idlib/precompiled.h"
#include "vectorClass.h"
#include "keyvalueClass.h"

class idPlayer;
class Mod_Card {
protected:
	int guiZ = 5;
public:
	idUserInterface* ui = NULL;
	
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
	virtual void Execute() = 0;

	/// <summary>
	/// Makes the card visible to the screen.
	/// </summary>
	/// <param name="uiList"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual idUserInterface* AddCard(float x, float y);
	virtual void HideCard();
	virtual void DeleteUI();
};
#endif
