#ifndef TRAP_EFFECTS_CANDIDATE_H
#define TRAP_EFFECTS_CANDIDATE_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
typedef struct ActiveEntry { u8 pad0; u8 active; u8 pad2[2]; } ActiveEntry;
typedef struct FirstEntry { u8 x; u8 y; u8 pad2[2]; u16 value; u8 pad6[6]; } FirstEntry;
typedef struct SecondEntry { u8 pad0[6]; u8 x; u8 y; u8 pad8[10]; u16 value; u8 pad14[4]; } SecondEntry;
extern ActiveEntry floor_objects[32];
extern FirstEntry dungeon_ground_item_positions[64];
extern SecondEntry dungeon_floor_object_positions[32];
extern u8 D_800E03D4[];
extern u8 trap_request_blocked;
extern s32 draw_linked_sprites_clipped();
extern s32 func_80045C34();
#endif
