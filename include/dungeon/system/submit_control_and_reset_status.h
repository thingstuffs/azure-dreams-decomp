#ifndef DUNGEON_CD_CONTROL_H
#define DUNGEON_CD_CONTROL_H
#include "modules/control_cd.h"
extern s8 spell_effect_selector_cache;
extern u8 D_800DF3DC[];
extern u8 D_800DF3E4[];
extern u8 D_800DF3EC[];
void submit_control_and_reset_status(void);
void submit_control_command_six(void);
void submit_indexed_entry_and_finalize(s32);
#endif
