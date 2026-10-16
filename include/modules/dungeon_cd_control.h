#ifndef DUNGEON_CD_CONTROL_H
#define DUNGEON_CD_CONTROL_H
#include "modules/control_cd.h"
extern s8 D_800DCF4D;
extern u8 D_800DF3DC[];
extern u8 D_800DF3E4[];
extern u8 D_800DF3EC[];
void dungeonSubmitControlAndResetStatus(void);
void dungeonSubmitControlCommandSix(void);
void dungeonSubmitIndexedEntryAndFinalize(s32);
#endif
