#ifndef Mod_Card_h
#define Mod_Card_h
#include "vectorClass.h"
#include "keyvalueClass.h"

class Mod_Card {
public:
	int cost; 
	char* name;
	char* cardArt;

	Mod_Card(int cost, char* name, char* cardArt)
	{
		this->cost = cost;
		this->name = name;
		this->cardArt = cardArt;
	}
	virtual void Execute() = 0;
};
#endif
