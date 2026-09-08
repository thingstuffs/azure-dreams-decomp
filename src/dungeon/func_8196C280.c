#include "common.h"

typedef struct S_8196C280_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8196C280_0;   /* arg1 in func_8196C280 */

typedef struct S_8196C280_1 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x22];
    u16 unk_50;
    u8 pad_52[0x3A];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196C280_1;   /* arg0 in func_8196C280 */

typedef struct S_8196C280_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8196C280_2;   /* arg2 in func_8196C280 */



typedef struct PositionRef {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionRef;

extern s32 func_80024AF8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s16 D_800269B4;
extern s32 D_800814A0;
extern PositionRef D_80083780;

/* Move the effect with collision checks, shrink its sprite, and expire it when finished. */
void func_8196C280(void *effect, void *position, void *sprite) {
    u16 age;
    u16 reduced_scale_x;
    u16 reduced_scale_y;
    u16 life_left;
    register u16 scale_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 scale_y;
    u16 next_scale_y;
    register u16 next_scale_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ((S_8196C280_0 *)position)->unk_00.at00.v += ((S_8196C280_1 *)effect)->unk_8C;
    ((S_8196C280_1 *)effect)->unk_8C += ((S_8196C280_1 *)effect)->unk_98;
    {
        u16 check_x;
        u16 check_y;
        s32 check_z;

        check_x = ((S_8196C280_0 *)position)->unk_00.at02.v;
        check_y = ((S_8196C280_0 *)position)->unk_04.at02.v;
        check_z = ((S_8196C280_0 *)position)->unk_08.at02.v;
        D_800269B4 = 1;
        if ((func_800A45D8(check_x, check_y, check_z) << 0x10) != 0) {
            ((S_8196C280_0 *)position)->unk_00.at00.v -= ((S_8196C280_1 *)effect)->unk_8C;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_1 *)effect)->unk_98 = 0;
        }
    }
    ((S_8196C280_0 *)position)->unk_04.at00.v += ((S_8196C280_1 *)effect)->unk_90;
    ((S_8196C280_1 *)effect)->unk_90 += ((S_8196C280_1 *)effect)->unk_9C;
    if ((func_800A45D8(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v, ((S_8196C280_0 *)position)->unk_08.at02.v) << 0x10) != 0) {
        ((S_8196C280_0 *)position)->unk_04.at00.v -= ((S_8196C280_1 *)effect)->unk_90;
        ((S_8196C280_1 *)effect)->unk_90 = 0;
        ((S_8196C280_1 *)effect)->unk_9C = 0;
    }
    ((S_8196C280_0 *)position)->unk_08.at00.v += ((S_8196C280_1 *)effect)->unk_94;
    ((S_8196C280_1 *)effect)->unk_94 += ((S_8196C280_1 *)effect)->unk_A0;
    {
        s32 height;

        height = ((S_8196C280_0 *)position)->unk_08.at02.v;
        if ((func_800BCB04(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v, (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
            ((S_8196C280_1 *)effect)->unk_94 = 0;
            ((S_8196C280_1 *)effect)->unk_90 = 0;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_0 *)position)->unk_08.at02.v = func_800BCB04(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v, (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4)) - 0x11;
            ((S_8196C280_0 *)position)->unk_08.at00u.v = 0;
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
    }
    age = ((S_8196C280_1 *)effect)->unk_50;
    ((S_8196C280_1 *)effect)->unk_50 = age + 1;
    if ((s16)age >= 3) {
        scale_x = ((S_8196C280_2 *)sprite)->unk_1C;
        scale_y = ((S_8196C280_2 *)sprite)->unk_1E;
        reduced_scale_x = scale_x - 0x100;
        next_scale_x = reduced_scale_x;
        if ((s16)reduced_scale_x < 0) {
            next_scale_x = 0;
        }
        reduced_scale_y = scale_y - 0x100;
        next_scale_y = reduced_scale_y;
        if ((s16)reduced_scale_y < 0) {
            next_scale_y = 0;
        }
        if (((next_scale_y << 0x10) == 0) || ((next_scale_x << 0x10) == 0)) {
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
        ((S_8196C280_2 *)sprite)->unk_1C = next_scale_x;
        ((S_8196C280_2 *)sprite)->unk_1E = next_scale_y;
    }
    func_80024AF8(effect, position, sprite,
        (s16)(((S_8196C280_0 *)position)->unk_00.at02.v - D_80083780.x),
        (s16)(((S_8196C280_0 *)position)->unk_04.at02.v - D_80083780.y),
        (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - D_80083780.z));
    life_left = ((S_8196C280_1 *)effect)->unk_2C - 1;
    ((S_8196C280_1 *)effect)->unk_2C = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    if (((S_8196C280_2 *)sprite)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
