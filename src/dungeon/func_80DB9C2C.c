#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017142C_0 {
    s16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    u8 pad_1C[0x8];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x38];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
} S_8017142C_0;   /* arg0 in func_8017142C */

typedef struct S_8017142C_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8017142C_1;   /* arg1 in func_8017142C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800478B8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s32 D_800814A0;

/* Update effect motion, collisions, sprite growth, and timed fading. */
void func_8017142C(void *effect, void *position, void *sprite) {
    s32 move_height;
    s32 fade_height;
    s32 phase;
    s32 fade_level;
    s32 velocity_x;
    s32 velocity_y;
    u16 anim_tick;
    u16 move_scale_x;
    u16 move_scale_y;
    u16 move_ticks_left;
    u16 fade_scale_x;
    u16 fade_scale_y;
    u16 fade_ticks_left;

    if (((S_8017142C_0 *)effect)->unk_00 == 0) {
        ((S_8017142C_1 *)position)->unk_00.at00.v += ((S_8017142C_0 *)effect)->unk_60;
        velocity_x = ((S_8017142C_0 *)effect)->unk_60;
        ((S_8017142C_0 *)effect)->unk_60 = (velocity_x * 2) / 3;
        if ((func_800A45D8(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, ((S_8017142C_1 *)position)->unk_08.at02.v) << 0x10) != 0) {
            ((S_8017142C_1 *)position)->unk_00.at00.v -= ((S_8017142C_0 *)effect)->unk_60;
            ((S_8017142C_0 *)effect)->unk_60 = 0;
            ((S_8017142C_0 *)effect)->unk_6C = 0;
        }
        ((S_8017142C_1 *)position)->unk_04.at00.v += ((S_8017142C_0 *)effect)->unk_64;
        velocity_y = ((S_8017142C_0 *)effect)->unk_64;
        ((S_8017142C_0 *)effect)->unk_64 = (velocity_y * 2) / 3;
        if ((func_800A45D8(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, ((S_8017142C_1 *)position)->unk_08.at02.v) << 0x10) != 0) {
            ((S_8017142C_1 *)position)->unk_04.at00.v -= ((S_8017142C_0 *)effect)->unk_64;
            ((S_8017142C_0 *)effect)->unk_64 = 0;
            ((S_8017142C_0 *)effect)->unk_70 = 0;
        }
        ((S_8017142C_1 *)position)->unk_08.at00.v += ((S_8017142C_0 *)effect)->unk_68;
        ((S_8017142C_0 *)effect)->unk_68 += ((S_8017142C_0 *)effect)->unk_74;
        move_height = ((S_8017142C_1 *)position)->unk_08.at02.v;
        if ((func_800BCB04(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)position)->unk_08.at02.v - 4)) - 0x10) < move_height) {
            ((S_8017142C_0 *)effect)->unk_68 = 0;
            ((S_8017142C_1 *)position)->unk_08.at02.v = func_800BCB04(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)position)->unk_08.at02.v - 4)) - 0x11;
            ((S_8017142C_1 *)position)->unk_08.at00u.v = 0;
            if (((S_8017142C_0 *)effect)->unk_1A == 0) {
                ((S_8017142C_0 *)effect)->unk_1A = 1;
                ((S_8017142C_0 *)effect)->unk_24 = 0;
            }
        }
        anim_tick = ((S_8017142C_0 *)effect)->unk_26 + 1;
        ((S_8017142C_0 *)effect)->unk_26 = anim_tick;
        if (!(anim_tick & 3)) {
            func_800478B8(sprite);
        }
        move_scale_x = ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v + 0x64;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = move_scale_x;
        if ((u32)(move_scale_x & 0xFFFF) >= 0x2001U) {
            ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = 0x2000;
        }
        move_scale_y = ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v + 0x64;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = move_scale_y;
        if ((u32)(move_scale_y & 0xFFFF) >= 0x2001U) {
            ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = 0x2000;
        }
        move_ticks_left = ((S_8017142C_0 *)effect)->unk_24 - 1;
        ((S_8017142C_0 *)effect)->unk_24 = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            ((S_8017142C_0 *)effect)->unk_1A = 0;
            ((S_8017142C_0 *)effect)->unk_00 = (u16)((S_8017142C_0 *)effect)->unk_00 + 1;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
    phase = ((S_8017142C_0 *)effect)->unk_00;
    if (phase == 1) {
        if (((S_8017142C_0 *)effect)->unk_1A == 0) {
            ((S_8017142C_0 *)effect)->unk_1A = phase;
            ((S_8017142C_0 *)effect)->unk_24 = 0x14;
            ((S_8017142C_0 *)effect)->unk_26 = 0x14;
            ((S_8017142C_0 *)effect)->unk_64 = 0;
            ((S_8017142C_0 *)effect)->unk_60 = 0;
        }
        fade_scale_x = ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v + 0xC8;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = fade_scale_x;
        if ((u32)(fade_scale_x & 0xFFFF) >= 0x2001U) {
            ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = 0x2000;
        }
        fade_scale_y = ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v + 0xC8;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = fade_scale_y;
        if ((u32)(fade_scale_y & 0xFFFF) >= 0x2001U) {
            ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = 0x2000;
        }
        ((S_8017142C_1 *)position)->unk_08.at00.v += ((S_8017142C_0 *)effect)->unk_68;
        ((S_8017142C_0 *)effect)->unk_68 += ((S_8017142C_0 *)effect)->unk_74;
        fade_height = ((S_8017142C_1 *)position)->unk_08.at02.v;
        if ((func_800BCB04(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)position)->unk_08.at02.v - 4)) - 0x10) < fade_height) {
            ((S_8017142C_0 *)effect)->unk_68 = 0;
            ((S_8017142C_1 *)position)->unk_08.at02.v = func_800BCB04(((S_8017142C_1 *)position)->unk_00.at02.v, ((S_8017142C_1 *)position)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)position)->unk_08.at02.v - 4)) - 0x11;
            ((S_8017142C_1 *)position)->unk_08.at00u.v = 0;
            if (((S_8017142C_0 *)effect)->unk_1A == 0) {
                ((S_8017142C_0 *)effect)->unk_1A = phase;
                ((S_8017142C_0 *)effect)->unk_24 = 0;
            }
        }
        fade_level = ((s16)((S_8017142C_0 *)effect)->unk_24 << 7) / (s16)((S_8017142C_0 *)effect)->unk_26;
        ((Rec_D_80082E80 *)sprite)->unk_0C.at02_s8.v = 0;
        ((Rec_D_80082E80 *)sprite)->unk_0C.at01_s8.v = fade_level;
        ((Rec_D_80082E80 *)sprite)->unk_0C.at00_s8.v = fade_level;
        fade_ticks_left = ((S_8017142C_0 *)effect)->unk_24 - 1;
        ((S_8017142C_0 *)effect)->unk_24 = fade_ticks_left;
        if ((fade_ticks_left << 0x10) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
