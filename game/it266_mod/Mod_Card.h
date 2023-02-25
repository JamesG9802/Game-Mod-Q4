#ifndef Mod_Card_h
#define Mod_Card_h
#include "../../idlib/precompiled.h"
#include "vectorClass.h"
#include "keyvalueClass.h"

class Mod_Card {
public:
	idUserInterface* ui = NULL;

	int cost; 
	char* name;
	char* cardArt;

	Mod_Card(int cost, char* name, char* cardArt)
	{
		this->cost = cost;
		this->name = name;
		this->cardArt = cardArt;
	}
	~Mod_Card()
	{
		HideCard();
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
	virtual void AddCard(float x, float y);
	virtual void HideCard();
};
#endif
