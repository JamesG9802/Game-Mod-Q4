#ifndef Mod_Deck_h
#define Mod_Deck_h
#include "Mod_Card.h"
#include "vectorClass.h"

class Mod_Card;
class Mod_Deck {
public:
	vectorClass<Mod_Card*> deck;
	vectorClass<Mod_Card*> hand;
	vectorClass<Mod_Card*> discard;
	Mod_Deck(vectorClass<Mod_Card*>* deck);
	~Mod_Deck();
	/// <summary>
	/// Draw num cards from the deck. 
	/// If the deck is empty while drawing, 
	///		reshuffle the deck.
	/// </summary>
	virtual void DrawCard(int num = 1);
	virtual void DiscardCard(Mod_Card* card);
	virtual void DiscardHand();
	//	Shuffles the order of the deck
	virtual void Shuffle();
	//	Reshuffles the discard into the deck;
	virtual void Reshuffle();
	/// <summary>
	/// Returns true if the deck is empty;
	/// </summary>
	/// <returns></returns>
	virtual bool isEmpty();
};
#endif