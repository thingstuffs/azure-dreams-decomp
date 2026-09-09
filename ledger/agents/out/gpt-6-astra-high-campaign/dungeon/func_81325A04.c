#include "common.h"

typedef struct S_func_81325A04_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x06];
    union {
        s16 s;
        u16 u;
    } unk_96;
    u8 pad_98[0x03];
    u8 unk_9B;
    u8 pad_9C[0x17];
    u8 unk_B3;
    u8 unk_B4;
} S_func_81325A04_0;

typedef struct S_func_81325A04_1 {
    u8 pad_00[0x02];
    s16 unk_02;
    u8 pad_04[0x02];
    s16 unk_06;
    u8 pad_08[0x04];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81325A04_1;

typedef struct S_func_81325A04_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x0E];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x06];
    s32 unk_2C;
} S_func_81325A04_2;

typedef struct S_func_81325A04_3 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x01];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_func_81325A04_3;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern s32 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];
extern u8 D_801746C4[];
extern u8 D_801746CC[];

extern s32 func_800A2B04();
extern s32 func_800AAA54();
extern s32 func_800AD4D0();
extern s32 func_80047784();

/* Updates timed movement, returns the entity to its tile, and restores its animation. */
u8 *func_8016D204(S_func_81325A04_0 *action, S_func_81325A04_1 *motion, S_func_81325A04_2 *entity, S_func_81325A04_3 *actor) {
    s32 state;
    s16 timer;
    s16 next_timer;
    u16 timer_bits;
    s32 facing;
    s32 anim_addr;
    s32 timer_ending;
    s32 velocity_x;
    s32 velocity_y;
    s32 tile_x;
    s32 offset_x;
    s32 tile_y;
    s32 offset_y;
    s32 *shared_state;
    u8 *final_state;
    register u32 result_bits ASM_REG("$2");
    u8 *anim_table;

    state = action->unk_9B;
    if (state == 1) {
        goto slow_move;
    }
    if (state < 2) {
        if (state == 0) {
            goto start_move;
        }
        return;
    }

    if (state == 2) {
        goto return_to_tile;
    }
    if (state == 3) {
        goto finish_move;
    }
    return;

start_move:
    func_800AD4D0(actor);
    action->unk_96.s = 12;
    action->unk_9B = (u8)(action->unk_9B + 1);
    if (actor->unk_28 == 0) {
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (action->unk_B4 != 0) {
            result_bits = (u32)D_8016B778;
            action->unk_9B = 0;
            goto store_handler;
        }
        goto initialize;
    }
    final_state = (u8 *)3;
    if (!(entity->unk_14 & 0x8000)) {
        return final_state;
    }
    action->unk_96.s = 0;
    action->unk_9B = (u32)final_state;
    return;

slow_move:
    timer_bits = action->unk_96.u;
    timer_bits--;
    action->unk_96.u = timer_bits;
    timer = (s16)timer_bits;
    if (timer >= 11) {
        motion->unk_0C =
            *(s16 *)((u8 *)D_8006CCD8 + ((actor->unk_6A >> 8) & 0xE)) << 20;
        motion->unk_10 =
            *(s16 *)((u8 *)D_8006CCE8 + ((actor->unk_6A >> 8) & 0xE)) << 20;
        entity->unk_14 |= 0x800;
        return;
    }
    if (timer >= 7) {
        velocity_x = motion->unk_0C;
        if (velocity_x < 0) {
            velocity_x += 3;
        }
        velocity_y = motion->unk_10;
        motion->unk_0C = velocity_x >> 2;
        if (velocity_y < 0) {
            velocity_y += 3;
        }
        motion->unk_10 = velocity_y >> 2;
        return;
    }
    timer_ending = timer < 2;
    if (!timer_ending) {
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        return;
    }
    if (timer == state) {
        entity->unk_14 &= 0xF7FF;
        return;
    }
    if (timer != 0) {
        return (u8 *)(u32)timer_ending;
    }
    timer = 4;
    result_bits = action->unk_9B;
    action->unk_96.s = timer;
    goto increment_state;
return_to_tile:
    timer = action->unk_96.s;
    if (timer != 0) {
        tile_x = entity->unk_24 << 6;
        offset_x = motion->unk_02 - 32;
        motion->unk_0C = ((tile_x - offset_x) << 16) / timer;
        tile_y = entity->unk_25 << 6;
        offset_y = motion->unk_06 - 32;
        motion->unk_10 =
            ((tile_y - offset_y) << 16) / action->unk_96.s;
    }
    result_bits = action->unk_96.u;
    next_timer = (s16)(result_bits - 1);
    result_bits <<= 16;
    action->unk_96.s = next_timer;
    if ((s32)result_bits > 0) {
        return (u8 *)result_bits;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    result_bits = action->unk_9B;
increment_state:
    action->unk_9B = (u8)(result_bits + 1);
    return;

finish_move:
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, entity->unk_24, entity->unk_25);
    if (actor->unk_28 != 0) {
        goto restore_animation;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    if (action->unk_B4 != 0) {
        goto reset_action;
    }
initialize:
    action->unk_9B = 0;
    func_800AAA54(action, motion, entity, D_801746CC);
    return;

reset_action:
    result_bits = (u32)D_8016B778;
    ASM_KEEP(result_bits);
    action->unk_9B = 0;
    goto store_handler;

restore_animation:
    anim_addr = entity->unk_2C;
    if (anim_addr == (s32)D_801746C4) {
        if (action->unk_B3 == 0) {
            anim_table = D_8017467C;
        } else {
            result_bits = (u32)D_80174684;
            anim_table = (u8 *)result_bits;
        }
        if (anim_addr != (s32)anim_table) {
            entity->unk_2C = (s32)anim_table;
            facing = D_80083228[0] + actor->unk_2A;
            func_80047784(entity, *(u8 *)((u32)(((facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
        }
    }
    shared_state = D_80083460;
    if (shared_state[4] == (s32)((u8 *)actor - 0x20)) {
        shared_state[4] &= 0x7FFFFFFF;
    }
    result_bits = (u32)D_8016B778;
store_handler:
    action->unk_8C = (u8 *)result_bits;
    return (u8 *)result_bits;
}
