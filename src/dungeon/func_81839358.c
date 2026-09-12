#include "common.h"
#include "m2c_compat.h"

typedef struct S_81839358_0 {
    union { struct { volatile s32 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    union { volatile s32 v; s32 n; } unk_0C;   /* accessed as both */
    union { volatile s32 v; s32 n; } unk_10;   /* accessed as both */
    union { volatile s32 v; s32 n; } unk_14;   /* accessed as both */
} S_81839358_0;   /* arg1 in func_81839358 */

typedef struct S_81839358_1_pre {
    u16 unk_00;
} S_81839358_1_pre;   /* the 0x2 bytes before arg0 in func_81839358, addressed as arg0[-1] */

typedef struct S_81839358_1 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x40];
    u16 unk_48;
    s16 unk_4A;
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_81839358_1;   /* arg0 in func_81839358 */

typedef struct S_81839358_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_81839358_2;   /* temp_v1 in func_81839358 */

typedef struct S_81839358_3 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81839358_3;   /* arg2 in func_81839358 */

typedef struct S_81839358_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81839358_4;   /* &D_800DED28 in func_81839358 */


void func_80024D24(void) __attribute__((noreturn));                         /* extern */
void func_80024D90(void) __attribute__((noreturn));                         /* extern */
void func_80024DCC(void) __attribute__((noreturn));                    /* extern */
void func_8004491C(void *, void *);           /* extern */
void func_800478B8(void *);                 /* extern */
extern M2C_UNK D_80045340;
extern s32 D_800814A0;
extern u8 D_800DEC70[];
extern M2C_UNK D_800DED28;

/* Updates effect motion and advances its timed sprite animation. */
void func_81839358(void *effect, void *motion, void *sprite) {
    s32 state;
    s32 rounded_x;
    s32 rounded_y;
    s32 vel_y;
    s32 vel_z;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 pos_x;
    s32 vel_x;
    s32 sprite_word;
    s32 timer_shift;
    u8 red_level;
    s32 timer;
    u16 sprite_scale;
    u8 green_blue;
    void *owner;

    pos_x = ((S_81839358_0 *)motion)->unk_00.at00.v;
    vel_x = ((S_81839358_0 *)motion)->unk_0C.v;
    vel_y = ((S_81839358_0 *)motion)->unk_10.v;
    vel_z = ((S_81839358_0 *)motion)->unk_14.v;
    ((S_81839358_0 *)motion)->unk_00.at00u.v = pos_x + vel_x;
    ((S_81839358_0 *)motion)->unk_04.at00.v = (s32) (((S_81839358_0 *)motion)->unk_04.at00.v + vel_y);
    ((S_81839358_0 *)motion)->unk_08 = (s32) (((S_81839358_0 *)motion)->unk_08 + vel_z);
    owner = ((S_81839358_1 *)effect)->unk_00;
    ((S_81839358_2 *)owner)->unk_10 = (s32) (((S_81839358_2 *)owner)->unk_10 | 0x8000);
    rounded_x = ((S_81839358_0 *)motion)->unk_00.at02.v;
    if (rounded_x < 0) {
        rounded_x += 0x3F;
    }
    if ((rounded_x >> 6) == ((S_81839358_1 *)effect)->unk_04) {
        rounded_y = ((S_81839358_0 *)motion)->unk_04.at02.v;
        if (rounded_y < 0) {
            rounded_y += 0x3F;
        }
        if ((rounded_y >> 6) == ((S_81839358_1 *)effect)->unk_06) {
            ((S_81839358_0 *)motion)->unk_14.n = 0;
            ((S_81839358_0 *)motion)->unk_10.n = 0;
            ((S_81839358_0 *)motion)->unk_0C.n = 0;
        }
    }
    state = ((S_81839358_1 *)effect)->unk_4C.s;
    timer = ((S_81839358_1 *)effect)->unk_48 - 1;
    ((S_81839358_1 *)effect)->unk_48 = timer;
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    timer_shift = timer << 0x10;
    if (state == 0) {
        goto state_0;
    }
    func_80024DCC();
    return;
state_ge_2:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto update_sprite;
    }
    func_80024DCC();
    return;
state_0:
    if (timer_shift > 0) {
        return;
    }
    func_8004491C(effect - 0x20, &D_80045340);
    ((S_81839358_1 *)effect)->unk_4C.u = ((S_81839358_1 *)effect)->unk_4C.u + 1;
    func_80024DCC();
    return;
state_1:
    {
        func_800478B8(sprite);
        if (((S_81839358_3 *)sprite)->unk_14 & 0x6000) {
            ((S_81839358_3 *)sprite)->unk_04 = 0;
            ((S_81839358_3 *)sprite)->unk_05 = 0;
        }
        red_level = ((S_81839358_3 *)sprite)->unk_0C.at00.v;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (((S_81839358_1 *)effect)->unk_4A >= (s32) red_level) {
            ((S_81839358_0 *)motion)->unk_0C.n = (s32) (((S_81839358_0 *)motion)->unk_0C.n * 5);
            ((S_81839358_0 *)motion)->unk_10.n = (s32) (((S_81839358_0 *)motion)->unk_10.n * 5);
            ((S_81839358_0 *)motion)->unk_14.n = (s32) (((S_81839358_0 *)motion)->unk_14.n * 8);
            ((S_81839358_3 *)sprite)->unk_1E = 0xC00U;
            ((S_81839358_3 *)sprite)->unk_1C = 0xC00U;
            ((S_81839358_3 *)sprite)->unk_0C.at00u.v = ((S_81839358_3 *)sprite)->unk_0C.at00u.v * 4;
            if (((S_81839358_1 *)effect)->unk_48 & 1) {
                u8 *dispatch_ptr;
                dispatch_ptr = D_800DEC70;
                ASM_TAILSLOT_PIN(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_80024D24();
                return;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((S_81839358_3 *)sprite)->unk_00 = &D_800DED28;
            sprite_word = ((S_81839358_4 *)(&D_800DED28))->unk_04;
            ((S_81839358_3 *)sprite)->unk_04 = 0;
            ((S_81839358_3 *)sprite)->unk_05 = 0;
            ((S_81839358_3 *)sprite)->unk_08 = sprite_word;
            ((S_81839358_1 *)effect)->unk_4C.u = ((S_81839358_1 *)effect)->unk_4C.u + 1;
            func_80024D90();
            return;
        }
        sprite_scale = ((S_81839358_3 *)sprite)->unk_1E - 0x200;
        ((S_81839358_3 *)sprite)->unk_1E = sprite_scale;
        ((S_81839358_3 *)sprite)->unk_1C = sprite_scale;
        ((S_81839358_3 *)sprite)->unk_0C.at00.v = (u8) (((S_81839358_3 *)sprite)->unk_0C.at00.v - (u8) ((S_81839358_1 *)effect)->unk_4A);
        green_blue = ((S_81839358_3 *)sprite)->unk_0C.at02.v - ((s32) ((u16) ((S_81839358_1 *)effect)->unk_4A << 0x10) >> 0x12);
        ((S_81839358_3 *)sprite)->unk_0C.at02.v = green_blue;
        ((S_81839358_3 *)sprite)->unk_0C.at01.v = green_blue;
update_sprite:
        func_800478B8(sprite);
        if (((S_81839358_3 *)sprite)->unk_14 & 0x6000) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81839358_1_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
    }
}
/* MECHANISM: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
