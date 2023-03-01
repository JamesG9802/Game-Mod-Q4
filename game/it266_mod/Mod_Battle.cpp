#include "../../idlib/precompiled.h"
#include "./Mod_Battle.h"
#pragma hdrstop

void Mod_Battle::StartBattle()
{
	this->battleStarted = true;
}
void Mod_Battle::EndBattle()
{
	this->battleStarted = false;
}
void Mod_Battle::Think()
{

}
void Mod_Battle::PlayerRoundStart()
{

}