#ifndef Mod_Deck_h
#define Mod_Deck_h
#include "Mod_Card.h"
#include "vectorClass.h"

class Mod_Card;
class Mod_Deck {
	vectorClass<Mod_Card*> deck;
	vectorClass<Mod_Card*> hand;
	/// <summary>
	/// Draw num cards from the deck. 
	/// If the deck is empty while drawing, 
	///		reshuffle the deck.
	/// </summary>
	virtual void DrawCard(int num = 1);
	virtual void DiscardCard(Mod_Card* card);
	virtual void Rehuffle();
	virtual void Shuffle();

	/// <summary>
	/// Returns true if the deck is empty;
	/// </summary>
	/// <returns></returns>
	virtual bool isEmpty();
};
#endif