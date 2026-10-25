#ifndef DUNGEON_OVL_7F43F800_P04_H
#define DUNGEON_OVL_7F43F800_P04_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad00[0x9A];
    u8 unk9A;
    u8 unk9B;
    u8 pad9C[2];
    s16 unk9E;
} T_80172664_State;

typedef struct {
    u8 pad00[0x2C];
    u8 *unk2C;
} T_80172664_Context;

typedef struct {
    u8 pad00[0x2A];
    s16 unk2A;
} T_80172664_IndexSource;


// Initializes the state and applies a table entry selected by the combined source and global index.
struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);
extern void func_80047784(T_80172664_Context *, s16, s16);
extern u8 D_80174EA0[9];
void settle_actor_after_movement(T_80172664_State *state, s32 unused, SpriteFrameState *context, T_80172664_IndexSource *source);
#endif
