/*
	Map
	.	List<Node>
	Node
	.	List<Node> NextNodes
	>	BattleNode
	>	RestNode
	>	ShopNode
	BattleEntity
	.	Health
	.	List<BattleEntity> ExecuteAction()
	>	Player
	>	Pokemon
	>	Enemy
	Deck
	.	List<Card>
	.	DrawCard
	.	Reshuffle
	Battle
	.	List<Card> graveyard
	.	List<BattleEntity> playerTeam
	.	List<BattleEntity> enemyTeam

*/

#ifndef Mod_Battle_h
#define Mod_Battle_h

#include "../../idlib/precompiled.h"
#include "vectorClass.h"
#include "Mod_Battler.h"
class Mod_Battle {
private:
	enum TurnStage{
		s_Nothing,
		s_PlayerRoundStart,
		s_PlayerWaitForMove,
		s_PlayerMakingMove,
		s_PlayerRoundEnd,
		s_EnemyRoundStart,
		s_EnemyMakingMove,
		s_EnemyRoundEnd
	};
public:
	TurnStage currentStage = Mod_Battle::TurnStage::s_Nothing;

	vectorClass<Mod_Battler*> playerTeam;
	vectorClass<Mod_Battler*> enemyTeam;

	Mod_Battler* player;
	bool battleStarted = false;

	Mod_Battle()
	{

	}
	~Mod_Battle()
	{

	}
	/// <summary>
	/// Starts the battle
	/// </summary>
	virtual void StartBattle();
	/// <summary>
	/// Ends the battle
	/// </summary>
	virtual void EndBattle();
	
	/// <summary>
	/// Every frame, Think is called<br/>
	/// Round Start
	/// Player Round Start
	/// Player Moves
	/// Player Round End
	/// Enemy Round Start
	/// Enemy Moves
	/// Enemy Round End
	/// </summary>
	virtual void Think();

	/// <summary>
	/// Player Round start logic
	/// </summary>
	virtual void PlayerRoundStart();
};
#endif // !Mod_Battle_h