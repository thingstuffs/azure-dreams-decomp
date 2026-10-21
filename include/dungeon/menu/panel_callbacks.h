#ifndef DUNGEON_MENU_PANEL_CALLBACKS_H
#define DUNGEON_MENU_PANEL_CALLBACKS_H

#include "common.h"

typedef s32 (*hud_fade_predicate_fn)(void);

extern hud_fade_predicate_fn D_800DF030[3];
s32 check_global_record_field_zero(void);
s32 check_global_data_byte_zero(void);
s32 check_current_record_value_not_29(void);

#endif
