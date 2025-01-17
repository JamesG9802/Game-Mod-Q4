#ifndef Mod_SysCmds_h
#define Mod_SysCmds_h

#include "./Mod_Card.h"

/// <summary>
/// Upgrades a card.
/// </summary>
/// <param name="card"></param>
void Cmd_UpgradeCard(Mod_Card* card);

/// <summary>
/// Toggles the map ui.
/// </summary>
/// <param name="args"></param>
void Cmd_ToggleMap_f(const idCmdArgs& args);
void Cmd_DeleteNodeUI_f(const idCmdArgs& args);
void Cmd_LoadRestNode();
void Cmd_LoadNode(const idCmdArgs& args, Mod_Node node);
void Cmd_SetActiveNode_f(const idCmdArgs& args);
void Cmd_OpenDeck_f(const idCmdArgs& args);
void Cmd_CloseDeck_f(const idCmdArgs& args);
void Cmd_ToggleDeck_f(const idCmdArgs& args);
void Cmd_PlayerDebug_f(const idCmdArgs& args);
void Cmd_Sleep_f(const idCmdArgs& args);
void Cmd_ShowUpgradeMenu_f(const idCmdArgs& args);
void Cmd_HideUpgradeMenu_f();
void Cmd_ShowUpgradeCard_f(const idCmdArgs& args);
void Cmd_UpgradeBack_f(const idCmdArgs& args);
void Cmd_UpgradeConfirm_f(const idCmdArgs& args);

void Cmd_StartBattle(const idCmdArgs& args);

void Cmd_EndTurn_f(const idCmdArgs& args);
void Cmd_StartTurn_f(const idCmdArgs& args);
void Cmd_SelectBattleCard_f(const idCmdArgs& args);

void Cmd_UnselectCard_f(const idCmdArgs& args);
void Cmd_SelectTarget_f(const idCmdArgs& args);
void Cmd_ExecuteCard_f(const idCmdArgs& args);
void Cmd_WinBattle_f(const idCmdArgs& args);
void Cmd_WinBattle();
void ShowRewardScreen();
void CloseRewardScreen(const idCmdArgs& args);
void CollectGoldReward(const idCmdArgs& args);
void ShowCardReward(const idCmdArgs& args);
void CancelCard(const idCmdArgs& args);
void AddRewardCard(const idCmdArgs& args);


void BuyCard(const idCmdArgs& args);
void CloseShop(const idCmdArgs& args);
#endif // !Mod_SysCmds_h
