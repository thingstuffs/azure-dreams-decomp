#include "common.h"

typedef struct {
    u8 pad_00_8c[0x8c];
    u8 *field_8c;
    u8 pad_90_96[6];
    u16 field_96;
    u8 pad_98_9b[3];
    u8 field_9b;
} S810AF65C_0;

typedef struct {
    u8 pad_00_02[2];
    s16 field_02;
    u8 pad_04_06[2];
    s16 field_06;
    u8 pad_08_0c[4];
    s32 field_0c;
    s32 field_10;
    s32 field_14;
} S810AF65C_1;

typedef struct {
    u8 pad_00_14[0x14];
    u16 field_14;
    u8 pad_16_24[0x0e];
    u8 field_24;
    u8 field_25;
} S810AF65C_2;

typedef struct {
    u8 pad_00_1c[0x1c];
    s32 field_1c;
    u8 pad_20_28[8];
    u8 field_28;
    u8 pad_29_6a[0x41];
    u16 field_6a;
} S810AF65C_3;

extern u8 D_80173C94[];
extern s32 D_80083460[3];
extern u8 D_80170E54[];
extern s16 D_8006CCE8[];
extern s16 D_8006CCD8[];

extern void func_800A2B04(S810AF65C_1 *, u8, u8);
extern void func_800AAA54(S810AF65C_0 *, S810AF65C_1 *, S810AF65C_2 *, u8 *);
extern void func_800AD4D0(S810AF65C_3 *);

/* Updates directional movement, then returns the actor to its tile position. */
void func_80172E5C(S810AF65C_0 *animation, S810AF65C_1 *motion,
                   S810AF65C_2 *tile, S810AF65C_3 *actor) {
    s32 timer;
    s32 direction;
    s32 state;
    s32 move_ticks;
    s32 biased_x;
    s32 velocity_x;
    s32 velocity_y;
    s32 biased_y;
    s32 *global_state;

    timer = animation->field_96 - 1;
    direction = ((u16)actor->field_6a >> 9) & 7;
    state = animation->field_9b;
    animation->field_96 = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(actor);
    animation->field_96 = 2;
    animation->field_9b = animation->field_9b + 1;
    if (actor->field_28 == 0) {
        motion->field_14 = 0;
        motion->field_10 = 0;
        motion->field_0c = 0;
        animation->field_96 = 0;
        func_800AAA54(animation, motion, tile, D_80173C94);
        goto done;
    }
    if ((tile->field_14 & 0x8000) != 0) {
        animation->field_9b = 3;
        goto done;
    }
    goto state_1;

state_1:
    if ((s16)animation->field_96 > 0) {
        goto done;
    }
    motion->field_0c = (s16)D_8006CCD8[direction] << 18;
    motion->field_10 = (s16)D_8006CCE8[direction] << 18;
    move_ticks = 5;
    if ((actor->field_1c & 0x228) != 0) {
        move_ticks = 8;
    }
    animation->field_96 = move_ticks;
    velocity_x = motion->field_0c;
    biased_x = velocity_x;
    if (velocity_x < 0) {
        biased_x = velocity_x + 3;
    }
    velocity_y = motion->field_10;
    motion->field_0c = velocity_x - (biased_x >> 2);
    biased_y = velocity_y;
    if (velocity_y < 0) {
        biased_y = velocity_y + 3;
    }
    motion->field_10 = velocity_y - (biased_y >> 2);
    animation->field_9b = animation->field_9b + 1;
    goto state_tail;

state_2:
    motion->field_0c = motion->field_0c - ((s16)D_8006CCD8[direction] << 15);
    motion->field_10 = motion->field_10 - ((s16)D_8006CCE8[direction] << 15);
    if ((s16)animation->field_96 != 0) {
        goto done;
    }
    if (actor->field_28 == 0) {
        motion->field_14 = 0;
        motion->field_10 = 0;
        motion->field_0c = 0;
        func_800AAA54(animation, motion, tile, D_80173C94);
        goto done;
    }
    animation->field_96 = 4;
    animation->field_9b = animation->field_9b + 1;

state_tail:
    goto done;

state_3:
    if ((timer << 16) == 0) {
        goto reset;
    }
    {
        s32 tile_x;
        s32 origin_x;

        tile_x = tile->field_24 << 6;
        origin_x = motion->field_02 - 0x20;
        motion->field_0c = (tile_x - origin_x) << 15;
    }
    {
        s32 tile_y;
        s32 origin_y;

        tile_y = tile->field_25 << 6;
        origin_y = motion->field_06 - 0x20;
        motion->field_10 = (tile_y - origin_y) << 15;
    }
    if ((s16)animation->field_96 > 0) {
        goto done;
    }

reset:
    motion->field_14 = 0;
    motion->field_10 = 0;
    motion->field_0c = 0;
    func_800A2B04(motion, tile->field_24, tile->field_25);
    global_state = D_80083460;
    if (global_state[4] == (s32)((u8 *)actor - 0x20)) {
        global_state[4] = global_state[4] & 0x7fffffff;
    }
    animation->field_8c = D_80170E54;

done:
    return;
}
