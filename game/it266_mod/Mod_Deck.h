#ifndef Mod_Deck_h
#define Mod_Deck_h
#endif

class Mod_Deck {
	Mod_Card deck;

	/// <summary>
	/// Draw num cards from the deck. 
	/// If the deck is empty while drawing, 
	///		reshuffle the deck.
	/// </summary>
	virtual void DrawCard(int num = 1);
	virtual void Rehuffle();
	virtual void Shuffle();

	/// <summary>
	/// Returns true if the deck is empty;
	/// </summary>
	/// <returns></returns>
	virtual bool isEmpty();
};