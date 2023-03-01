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
	
	int cost; 
	char* name;
	char* cardArt;
	const char* cardArtUpgrade;

	bool isUpgradeable;
	Mod_Card(int cost, char* name, char* cardArt, bool isUpgradeable = true)
	{
		idStr str;

		this->cost = cost;
		this->name = name;
		this->cardArt = cardArt;
		
		str = cardArt;
		str += "_upgrade";
		cardArtUpgrade = str.c_str();
		this->isUpgradeable = isUpgradeable;

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
