#ifndef DUNGEON_OVL_7F469800_P04_H
#define DUNGEON_OVL_7F469800_P04_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct T_8017406C_S_8017406C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} T_8017406C_S_8017406C_0;   /* arg0 in func_8017406C */




extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void func_800A9A04(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);
void create_tinted_sprite_effect_supplied_position(T_8017406C_S_8017406C_0 *animation, EntityRec *motion, SpriteFrameState *tile, EntityRec *actor);
extern void update_actor_behavior();
#endif
