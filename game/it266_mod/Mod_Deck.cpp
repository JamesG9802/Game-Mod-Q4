#include "Mod_Deck.h"
#include "Mod_Card.h"
#pragma hdrstop

Mod_Deck::Mod_Deck(vectorClass<Mod_Card*>* deck)
{
	for (int i = 0; i < deck->size(); i++)
	{
		 this->deck.push(deck->get(i)->Copy());
	}
	
}
void Mod_Deck::DrawCard(int num)
{
	int i = 0;
	while (hand.size() < 10 && i < num)
	{
		if (deck.size() == 0)
		{
			if (discard.size() == 0)
				break;
			Reshuffle();
		}
		hand.push(deck.pop());
		i++;
	}
	for (i = 0; i < hand.size(); i++)
	{
		hand.get(i)->AddBattleCard(40 * i, 360, i);
	}
}
void Mod_Deck::DiscardCard(Mod_Card* card)
{

}
void Mod_Deck::DiscardHand()
{
	while (hand.size() > 0)
	{
		hand.get(hand.size()-1)->HideCard();
		discard.push(hand.pop());
	}
}

void Mod_Deck::Shuffle()
{
	vectorClass<Mod_Card*> deckClone;
	while (deck.size() != 0)
	{
		deckClone.push(deck.removeAt(gameLocal.random.RandomInt(deck.size() - 1)));
	}
	while (deckClone.size() != 0)
	{
		deck.push(deckClone.pop());
	}
}
void Mod_Deck::Reshuffle()
{
	while (discard.size() > 0)
	{
		deck.push(discard.pop());
	}
	Shuffle();
}
bool Mod_Deck::isEmpty()
{
	return deck.size() == 0;
}