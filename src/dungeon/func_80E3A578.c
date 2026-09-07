#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_80173D78_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    u8 pad_A8[0x4];
    u8 unk_AC;
} S_80173D78_0;   /* arg0 in func_80173D78 */

typedef struct S_80173D78_1 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; struct { u8 pad[0x3]; volatile u8 v; } at03u; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173D78_1;   /* arg2 in func_80173D78 */

typedef struct S_80173D78_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_80173D78_2;   /* arg3 in func_80173D78 */

typedef struct S_80173D78_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80173D78_3;   /* found in func_80173D78 */

typedef struct S_80173D78_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173D78_4;   /* counter_base in func_80173D78 */

typedef struct S_80173D78_5 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_80173D78_5;   /* base in func_80173D78 */


extern void *D_801708A0[];
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern M2C_UNK D_800C6AEC;
extern M2C_UNK D_8017086C;
extern M2C_UNK D_80170898;
extern M2C_UNK D_80170EE4;
extern M2C_UNK D_8017398C;

void func_8004491C();
void func_80044A50();
s32 func_800990FC();
s32 func_80099194();
void func_80099290();
s32 func_8009929C();
s32 func_80099734();
void func_8009A028();
void func_8009A21C();
void func_8009A3D0();
void *func_8009B25C();
void func_800A56E0();
void func_800A5720();
s16 func_800A70E4();
void func_800A9A0C();
void func_800BC318();
void func_801741E8() __attribute__((noreturn));
void func_8017424C() __attribute__((noreturn));
void func_80175DD0();
void *func_8017618C();

void func_80173D78(void *arg0, void *arg1, S_80173D78_1 *arg2, S_80173D78_2 *arg3)
{
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    S_80173D78_3 *found;
    void *created;
    S_80173D78_5 *base;
    s32 x;
    s32 y;
    s32 index;
    s32 temp_s0;
    s32 call_ret;
    void *call_obj;
    register s32 call_arg ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 chain;
    s32 mode;
    s32 map_flags;
    u32 sound_x;
    u32 sound_y;
    s16 step;
    u16 flags16;
    u16 counter;
    u8 state;

    state = ((S_80173D78_0 *)arg0)->unk_9B;
    if (state >= 5U) {
        return;
    }
    (void)jt_keep;
    goto *D_801708A0[(u32)state];

jt_c0:
    flags16 = arg2->unk_14;
    if (!(flags16 & 0xE000)) {
        return;
    }
    if (!(flags16 & 0x8000)) {
        func_800A56E0(0x80D);
    }
    ((S_80173D78_0 *)arg0)->unk_9B = ((S_80173D78_0 *)arg0)->unk_9B + 1;
    if (arg2->unk_14 & 0x8000) {
        ((S_80173D78_0 *)arg0)->unk_96 = 0;
        func_8017424C();
    }
    ((S_80173D78_0 *)arg0)->unk_96 = 0x10;
    func_8017424C();

jt_c1:
    if (!(((S_80173D78_0 *)arg0)->unk_96 & 3)) {
        if (!(arg2->unk_14 & 0x8000)) {
            func_80175DD0(arg0, arg1, arg2, 0);
            func_80175DD0(arg0, arg1, arg2, 1);
        }
    }
    counter = ((S_80173D78_0 *)arg0)->unk_96 - 1;
    ((S_80173D78_0 *)arg0)->unk_96 = counter;
    if ((s16)counter > 0) {
        return;
    }

    index = ((u16)arg3->unk_2A >> 8) & 0xE;
    x = arg2->unk_24 + *(u16 *)((s8 *)&D_8006CCD8 + index);
    y = arg2->unk_25 + *(u16 *)((s8 *)&D_8006CCE8 + index);
    arg3->unk_60.i = 0;

    if (((S_80173D78_0 *)arg0)->unk_AC == 0) {
        found = func_8009B25C(arg3, x & 0xFFFF, y & 0xFFFF,
                             arg3->unk_88);
        arg3->unk_60.p = found;
        if (found != 0) {
            state = found->unk_13;
            if (((u32)(state - 1) >= 0x2DU) || (state == 0x1E)) {
                call_ret = func_800990FC();
                call_obj = arg3;
                ASM_KEEP(call_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
                call_arg = call_ret;
                ASM_KEEP(call_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
                chain = func_80099734(call_obj, temp_s0 = call_arg);
                func_80099290(
                    func_80099194(&D_80170898,
                        func_80099734(found,
                            func_8009929C(0xA,
                                func_80099194(&D_8017086C, chain)))));
                func_800A5720(temp_s0);
                func_800A56E0(0x506);
                arg3->unk_60.i = 0;
            }
        }
    }

    if (((S_80173D78_0 *)arg0)->unk_AC < 2U) {
        if (arg3->unk_60.i == 0) {
            step = func_800A70E4((s16)x, (s16)y,
                                 arg3->unk_88);
            if (step >= 0) {
                arg3->unk_60.i = step + 1;
            }
        }
    }

    if (arg3->unk_60.i == 0) {
        void *counter_base;

        func_800A9A0C(arg3);
        ((S_80173D78_0 *)arg0)->unk_8C = &D_80170EE4;
        counter_base = &D_80083460;
        ((S_80173D78_4 *)counter_base)->unk_0A =
            ((S_80173D78_4 *)counter_base)->unk_0A - 1;
        arg3->unk_1C &= 0xEFFFFFFF;
        func_8017424C();
    }

    ((S_80173D78_0 *)arg0)->unk_9B = ((S_80173D78_0 *)arg0)->unk_9B + 1;
    map_flags = arg3->unk_14;
    sound_x = arg2->unk_24;
    sound_y = arg2->unk_25;
    mode = 0x3000;
    if (map_flags & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(sound_x, sound_y, mode);

    arg3->unk_1C |= 0x10000;
    created = func_8017618C(arg0, arg1, arg2, arg3);
    ((S_80173D78_0 *)arg0)->unk_A4 = created;
    if (created != 0) {
        base = (s8 *)arg0 - 0x20;
        func_80044A50(base);
        func_8004491C(base, &D_800C6AEC);
        arg2->unk_0C.at03.v = 0;
        arg2->unk_12 = arg2->unk_12 - 0x80;
        arg2->unk_14 |= 0xC;
        func_8009A028(arg3);
        base->unk_10 |= 0x80000000;
        func_801741E8();
    }

    map_flags = arg3->unk_14;
    sound_x = arg2->unk_24;
    sound_y = arg2->unk_25;
    mode = 0x3000;
    if (map_flags & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(sound_x, sound_y, mode);
    arg3->unk_1C &= 0xFFFEFFFF;
    func_8017424C();

jt_c2:
    state = arg2->unk_0C.at03.v;
    if (state < 7U) {
        arg2->unk_0C.at03.v = state + 1;
        arg2->unk_0C.at00.v =
            arg2->unk_0C.at00.v +
            (-(s32)arg2->unk_0C.at00.v /
             (8 - arg2->unk_0C.at03u.v));
        arg2->unk_0C.at01.v =
            arg2->unk_0C.at01.v +
            (-(s32)arg2->unk_0C.at01.v /
             (8 - arg2->unk_0C.at03.v));
        arg2->unk_0C.at02.v =
            arg2->unk_0C.at02.v +
            (-(s32)arg2->unk_0C.at02.v /
             (8 - arg2->unk_0C.at03.v));
        func_8017424C();
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    base = (s8 *)arg0 - 0x20;
    func_80044A50(base);
    func_800BC318(base);
    arg2->unk_0C.at03.v = 0;
    arg2->unk_0C.at00u.v = 0x00808080;
    arg2->unk_14 |= 0x800;
    arg2->unk_12 = arg2->unk_12 + 0x80;
    arg2->unk_14 &= 0xFFF3;
    ((S_80173D78_0 *)arg0)->unk_9B = ((S_80173D78_0 *)arg0)->unk_9B + 1;
    func_8017424C();

jt_c3:
{
    void *counter_base;

    ((S_80173D78_0 *)arg0)->unk_9A = 0x18;
    ((S_80173D78_0 *)arg0)->unk_9B = 0;
    ((S_80173D78_0 *)arg0)->unk_8C = &D_8017398C;
    counter_base = &D_80083460;
    ((S_80173D78_4 *)counter_base)->unk_0A =
        ((S_80173D78_4 *)counter_base)->unk_0A - 1;
    arg3->unk_6D = 0;
    arg3->unk_1C &= 0xEFFFFFFF;
    arg3->unk_46 &= 0x7FFF;
}
jt_c4:
    return;
}

/* MECHANISM: The true-rowbase function keeps the four arguments in s4/s7/s1/s3 and preserves the retail 0x38 frame.
   Guarded ABI staging reproduces the RNG-result a1-to-s0 call slot; sibling block-local counter bases select v1.
   A volatile byte reread restores the first color-step load, and named map_flags fixes both load schedules.
   ASM_SCHED_BARRIER keeps arg0-0x20 in the taken block instead of gcc stealing it into the branch delay. */
