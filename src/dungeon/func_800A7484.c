#include "common.h"

typedef struct S_800ACBE4_0 {
    u8 pad_00[0x9B];
    u8 unk_9B;
} S_800ACBE4_0;   /* arg0 in func_800ACBE4 */

typedef struct S_800ACBE4_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    union { u8 s; volatile u8 u; } unk_0F;   /* accessed as both */
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800ACBE4_1;   /* arg2 in func_800ACBE4 */

typedef struct S_800ACBE4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800ACBE4_2;   /* actor in func_800ACBE4 */



extern void func_8004491C(void *, void *);
extern void func_80044A50(void *);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A32A4(void *);
extern s32 D_800814A0;
extern s32 D_80083460;
extern s32 D_800C6AEC;

void func_800ACBE4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 actor_status;
    s32 actor_flags;
    s32 effect_size;
    s32 *global_base;
    u8 state;
    u8 level;
    u8 effect_x;
    u8 effect_y;
    void *actor;

    state = ((S_800ACBE4_0 *)arg0)->unk_9B;
    actor = arg3;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    actor = (u8 *)arg0 - 0x20;
    func_80044A50(actor);
    ((S_800ACBE4_1 *)arg2)->unk_12 -= 0x80;
    ((S_800ACBE4_1 *)arg2)->unk_14 |= 0xC;
    func_8004491C(actor, &D_800C6AEC);
    ((S_800ACBE4_1 *)arg2)->unk_0F.s = 0;
    ((S_800ACBE4_0 *)arg0)->unk_9B++;
    goto done;

state_one:
    if (((S_800ACBE4_1 *)arg2)->unk_0F.s < 8) {
        level = ((S_800ACBE4_1 *)arg2)->unk_0E;
        ((S_800ACBE4_1 *)arg2)->unk_0F.s++;
        level += -level / ((S_800ACBE4_1 *)arg2)->unk_0F.u;
        ((S_800ACBE4_1 *)arg2)->unk_0E = level;
        ((S_800ACBE4_1 *)arg2)->unk_0D = level;
        ((S_800ACBE4_1 *)arg2)->unk_0C = level;
        goto done;
    }

    global_base = &D_80083460;
    if (global_base[4] == (s32)((u8 *)actor - 0x20)) {
        global_base[4] &= 0x7FFFFFFF;
    }
    func_800A32A4(actor);
    actor_status = ((S_800ACBE4_2 *)actor)->unk_1C;
    effect_x = ((S_800ACBE4_1 *)arg2)->unk_24;
    effect_y = ((S_800ACBE4_1 *)arg2)->unk_25;
    effect_size = 0x3000;
    if (actor_status & 0x2000) {
        effect_size = 0x300;
    }
    func_8009A3D0(effect_x, effect_y, effect_size);
    actor_flags = ((S_800ACBE4_2 *)actor)->unk_14;
    if (actor_flags & 0x400000) {
        ((S_800ACBE4_2 *)actor)->unk_14 = actor_flags & 0xFFBFFFFF;
        ((S_800ACBE4_2 *)actor)->unk_1C |= 0x400000;
    }
    func_8009A028(actor);
    (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: The four-slot ABI holds a0/a2/a3 in s2/s1/s0, while true-space
   epilogue targets remain local CFG edges under the 0x20-byte frame.
   A volatile post-store byte reload and separate status/effect/flag lifetimes
   reproduce the retail div roles, load-delay fill, and a0/a1/a2 call setup. */
