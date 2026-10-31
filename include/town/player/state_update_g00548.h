#ifndef TOWN_PLAYER_STATE_UPDATE_G00548_H
#define TOWN_PLAYER_STATE_UPDATE_G00548_H
/* Advance and update the player state (G00548). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009D728, PD:town/engine:800D0620. */

#include "common.h"
#include "shared/game_work.h"
#include "shared/town_handler.h"
#include "m2c_compat.h"

typedef struct {
    s32 unk0;
    void *unk4;
    u16 unk8;
    s16 unkA;
    u8 padC[4];
    s16 unk10;
} Entity;

typedef struct {
    s32 unk0;
    void **unk4;
    u16 unk8;
    u16 unkA;
} Struct8009D814;

extern u8 D_800D0190[];
extern u8 player_interaction_handler_entries[];
extern s32 town_player_target_adjustment;
extern u8 D_8009B0EC[];
extern u8 D_8009B014[];
extern u8 town_scene_record_handlers[];
extern void *D_8009AFF4[];

/* Functions defined in this translation unit. */
void update_player_global_state(Entity *entity, void *ptr, void *ptr2);
void advance_player_state_table(Struct8009D814 *state, s32 update_arg, s32 shared_arg);
struct SpriteFrameState;
void forward_player_state_update(void *object, s32 value_1, struct SpriteFrameState *value_2);

#endif
