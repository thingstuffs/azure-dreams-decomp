#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800247C0_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800247C0_0;   /* arg0 in func_800247C0 */

typedef struct S_800247C0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800247C0_1;   /* temp_s2 in func_800247C0 */

typedef struct S_800247C0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800247C0_2;   /* arg1 in func_800247C0 */

typedef struct S_800247C0_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800247C0_3;   /* temp_a0 in func_800247C0 */

typedef struct S_800247C0_4 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 s; s16 u; } unk_1C;   /* accessed as both */
    union { u16 s; s16 u; } unk_1E;   /* accessed as both */
} S_800247C0_4;   /* temp_s1 in func_800247C0 */

typedef struct S_800247C0_5 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x5E];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_800247C0_5;   /* temp_s0 in func_800247C0 */

typedef struct S_800247C0_6 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800247C0_6;   /* global_base in func_800247C0 */

typedef struct S_800247C0_7 {
    u8 pad_00[0x28];
    s8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
    s16 unk_64;
} S_800247C0_7;   /* var_sp10 in func_800247C0 */

typedef struct S_800247C0_8 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800247C0_8;   /* ((S_800247C0_1 *)temp_s2)->unk_08 in func_800247C0 */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} LocalVec;

typedef struct {
    void *sp10;
    s32 unused14;
    LocalVec sp18;
} LocalStack;

s16 func_8002458C();
s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 func_80069EF8();
s32 func_800A48F0();
extern s32 D_800246B0;
extern s16 D_8002992E;
extern s32 D_80045340;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s32 D_800DE870;
extern s32 D_800E3D7C;

/* Shrink the effect, spawn inward-moving particles, and finish when its timer expires. */
void func_800247C0(void *effect, void *origin)
{
    void *effect_state;
    u16 offset_x;
    s32 velocity_x;
    s16 next_timer;
    s16 color_channel;
    s16 particle_index;
    s32 offset_y;
    s32 offset_z;
    s32 random_bits;
    s32 completion_state;
    u16 next_scale_x;
    u16 next_scale_y;
    u32 scale_x;
    u16 scale_y;
    u16 timer;
    void *position;
    void *particle_state;
    void *sprite;
    void *object;
    u8 *effect_globals;

    D_8002992E = 1;
    offset_x = (func_80069EF8() & 0x3F) - 0x20;
    offset_y = (func_80069EF8() & 0x3F) - 0x20;
    random_bits = func_80069EF8();
    object = ((S_800247C0_0 *)effect)->unk_20;
    position = ((S_800247C0_1 *)object)->unk_08;
    sprite = ((S_800247C0_1 *)object)->unk_0C;
    ((S_800247C0_2 *)origin)->unk_00.at00.v = ((S_800247C0_3 *)position)->unk_00.at00.v;
    ((S_800247C0_2 *)origin)->unk_04.at00.v = ((S_800247C0_3 *)position)->unk_04;
    offset_z = (random_bits & 0x3F) - 0x20;
    ((S_800247C0_2 *)origin)->unk_08.at00.v = ((S_800247C0_3 *)position)->unk_08;
    scale_x = ((S_800247C0_4 *)sprite)->unk_1C.s;
    object += 0x20;
    effect_state = object;
    if (scale_x >= 0x801U) {
        next_scale_x = scale_x - 0x50;
        ((S_800247C0_4 *)sprite)->unk_1C.s = next_scale_x;
        if ((u32)(next_scale_x & 0xFFFF) < 0x800U) {
            ((S_800247C0_4 *)sprite)->unk_1C.s = 0x800U;
        }
    }
    scale_y = ((S_800247C0_4 *)sprite)->unk_1E.s;
    if (scale_y >= 0x801U) {
        next_scale_y = scale_y - 0x50;
        ((S_800247C0_4 *)sprite)->unk_1E.s = next_scale_y;
        if ((u32)(next_scale_y & 0xFFFF) < 0x800U) {
            ((S_800247C0_4 *)sprite)->unk_1E.s = 0x800U;
        }
    }
    if (((S_800247C0_0 *)effect)->unk_28 >= 0xB) {
        particle_index = 0;
        for (; particle_index < 4; particle_index++) {
            object = func_8003FC64(0x212);
            if (object == NULL) {
                continue;
            }
            particle_state = object + 0x20;
            ((S_800247C0_5 *)particle_state)->unk_28 = 0x14;
            ((S_800247C0_1 *)object)->unk_10 = &D_800246B0;
            func_8004491C(object, &D_80045340);
            sprite = ((S_800247C0_1 *)object)->unk_0C;
            ((S_800247C0_4 *)sprite)->unk_10 = 0x20;
            ((S_800247C0_4 *)sprite)->unk_14 |= 0xC;
            position = ((S_800247C0_1 *)object)->unk_08;
            ((S_800247C0_3 *)position)->unk_00.at02.v =
                ((S_800247C0_2 *)origin)->unk_00.at02.v + offset_x;
            ((S_800247C0_8 *)(((S_800247C0_1 *)object)->unk_08))->unk_06 =
                ((S_800247C0_2 *)origin)->unk_04.at02.v + offset_y;
            ((S_800247C0_8 *)(((S_800247C0_1 *)object)->unk_08))->unk_0A =
                ((S_800247C0_2 *)origin)->unk_08.at02.v + offset_z - 0x10;
            velocity_x = 0 - ((s32)(offset_x << 0x10) >> 7);
            ((S_800247C0_5 *)particle_state)->unk_88 = velocity_x;
            ((S_800247C0_5 *)particle_state)->unk_8C =
                0 - ((s32)(offset_y << 0x10) >> 7);
            ((S_800247C0_5 *)particle_state)->unk_90 =
                0 - ((s32)(offset_z << 0x10) >> 7);
            sprite = ((S_800247C0_1 *)object)->unk_0C;
            ((S_800247C0_4 *)sprite)->unk_1E.u = 0x1000;
            ((S_800247C0_4 *)sprite)->unk_1C.u = 0x1000;
            color_channel = func_8002458C(3);
            ((S_800247C0_4 *)sprite)->unk_0E = 0;
            ((S_800247C0_4 *)sprite)->unk_0D = 0;
            ((S_800247C0_4 *)sprite)->unk_0C = 0;
            if (color_channel == 0) {
                ((S_800247C0_4 *)sprite)->unk_0C = 0x10;
            }
            if (color_channel == 1) {
                ((S_800247C0_4 *)sprite)->unk_0D = 0x10;
            }
            if (color_channel == 2) {
                ((S_800247C0_4 *)sprite)->unk_0E = 0x10;
            }
            ((S_800247C0_4 *)sprite)->unk_12 = 0x7DCF;
            ((S_800247C0_4 *)sprite)->unk_14 |= 0x100;
            func_8003DB94(sprite, &D_800DE870, 0);
        }
    }
    timer = ((S_800247C0_0 *)effect)->unk_28;
    next_timer = timer - 1;
    ((S_800247C0_0 *)effect)->unk_28 = next_timer;
    if ((next_timer << 0x10) <= 0) {
        effect_globals = (u8 *)&D_80083460;
        ((S_800247C0_0 *)effect)->unk_28 = timer;
        if (((S_800247C0_6 *)effect_globals)->unk_10 == NULL) {
            ((S_800247C0_6 *)effect_globals)->unk_10 = ((S_800247C0_0 *)effect)->unk_20;
        }
        object = ((S_800247C0_0 *)effect)->unk_20;
        func_800A48F0(object + 0x20, 0x18, 0x14);
        ((S_800247C0_7 *)effect_state)->unk_28 = 0;
        completion_state = D_800E3D7C;
        ((S_800247C0_7 *)effect_state)->unk_64 = -1;
        ((S_800247C0_7 *)effect_state)->unk_60 = completion_state;
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
