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
	while (!isEmpty() && hand.size() < 10 && i < num)
	{
		hand.push(deck.pop());
		i++;
	}
	for (i = 0; i < hand.size(); i++)
	{
		hand.get(i)->AddBattleCard(70 * i, 360);
	}
}
void Mod_Deck::DiscardCard(Mod_Card* card)
{

}
void Mod_Deck::DiscardHand()
{

}

void Mod_Deck::Shuffle()
{

}
void Mod_Deck::Reshuffle()
{

}
bool Mod_Deck::isEmpty()
{
	return deck.size() == 0;
}