#include "shared/entity.h"
#ifndef DUNGEON_OVL_7F43F800_P05_H
#define DUNGEON_OVL_7F43F800_P05_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"

typedef struct {
    u8 pad_00[0x8c];
    void (*ptr_8c)();
    s32 value_90;
    u8 pad_94[2];
    u16 value_96;
    u16 flags_98;
    u8 pad_9a;
    u8 state_9b;
    u8 pad_9c[2];
    union {
        u16 u;
        s16 s;
    } count_9e;
    u8 pad_a0[4];
    s32 value_a4;
} T_80172B6C_State;

typedef struct {
    u8 pad_00[2];
    s16 value_02;
    u8 pad_04[2];
    s16 value_06;
    u8 pad_08[4];
    s32 value_0c;
    s32 value_10;
    s32 value_14;
} T_80172B6C_Motion;



typedef struct {
    u8 pad_00[0x1c];
    s32 flags_1c;
    u8 pad_20[0xa];
    s16 value_2a;
    u8 pad_2c[0x1a];
    u16 flags_46;
} T_80172B6C_Actor;



extern s32 rsin(s32 value);
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern void func_80047784(void *sprite, u8 value, s32 zero);
extern void set_record_integer_tile_center(T_80172B6C_Motion *motion, u8 x, u8 y);
extern void spend_actor_mp(T_80172B6C_Actor *actor, s32 value);
extern s16 get_rounded_facing_and_rounding_flag(u8 x0, u8 y0, u8 x1, u8 y1, s16 *scratch);

extern void on_actor_status_updated(T_80172B6C_Actor *actor);
extern void func_800A9A04(T_80172B6C_Actor *actor);
extern u8 D_80174EA8[];
extern u8 D_80174EB0[];
void update_timed_actor_movement_and_scale(ActorRecord *state, T_80172B6C_Motion *motion, SpriteFrameState *sprite, T_80172B6C_Actor *actor);
void update_actor_behavior_and_direction(ActorRecord *motion, ObjectPosition *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor);
#endif
