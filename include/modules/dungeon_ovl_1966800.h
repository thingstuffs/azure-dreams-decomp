#ifndef DUNGEON_OVL_1966800_H
#define DUNGEON_OVL_1966800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
/* The module owns a typed entry pointer before this complete code member. */

/* Advance a timed action, spawn its effect, and update completion flags. */
s32 resolve_record_orientation_or_fallback(s32, void *, void *, s32);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
s32 func_80053EF0(s32);
void play_sound_if_enabled(s32);
extern s32 D_80024374;
void decrement_flagged_item_parameters(void *action, void *saved_position);
#endif
