#include "common.h"

typedef struct S_818F9E48_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x28];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x64];
    u16 unk_98;
    u16 unk_9A;
} S_818F9E48_0;   /* arg0 in func_818F9E48 */

typedef struct S_818F9E48_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_1;   /* effect in func_818F9E48 */

typedef struct S_818F9E48_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818F9E48_2_pre;   /* the 0x18 bytes before owner in func_818F9E48, addressed as owner[-1] */

typedef struct S_818F9E48_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_3;   /* out in func_818F9E48 */

typedef struct S_818F9E48_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_4;   /* copy in func_818F9E48 */

typedef struct S_818F9E48_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_5;   /* motion in func_818F9E48 */

typedef struct S_818F9E48_6 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_818F9E48_6;   /* ((S_818F9E48_0 *)arg0)->unk_30 in func_818F9E48 */



typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;

typedef struct EffectState {
    u8 pad[0x38];
    u8 levels[0x60];
} EffectState;

extern PackedVector D_8002400C;
extern s16 D_800266BC;
extern s32 D_800814A0;

extern void func_80024CD4();
extern void func_80025714() __attribute__((noreturn));
extern void func_80025758() __attribute__((noreturn));
extern void func_80025908() __attribute__((noreturn));

void func_818F9E48(void *arg0, void *arg1, void *arg2) {
    void *out = arg1;
    void *effect = arg2;
    s32 tail_value;
    PackedVector source;
    Pair16 derived;
    s32 i;
    u8 value;
    s16 timer;
    u16 flags;
    void *owner;
    void *motion;
    void *copy;
    u16 old_x;
    u16 old_y;
    s32 one;

    source = D_8002400C;
    ASM_KEEP(out);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(effect);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    D_800266BC = 1;
    ((S_818F9E48_0 *)arg0)->unk_98 += 0xC8;

    if (((S_818F9E48_0 *)arg0)->unk_02.s < 0x32) {
        i = 0;
        do {
            ((EffectState *)arg0)->levels[i]++;
            i++;
        } while (i < 0x60);
        func_80025714();
        return;
    }

    i = 0;
    do {
        value = ((EffectState *)arg0)->levels[i];
        if (value != 0) {
            ((EffectState *)arg0)->levels[i] = value - 1;
        }
        i++;
    } while (i < 0x60);

    timer = ((S_818F9E48_0 *)arg0)->unk_02.s;
    if (timer < 0x15) {
        tail_value = (timer * 6) - 0x79;
        ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025758();
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    if (timer >= 0x50) {
        value = ((0x64 - timer) * 6) - 0x80;
        ((S_818F9E48_1 *)effect)->unk_0E = value;
        ((S_818F9E48_1 *)effect)->unk_0D = value;
        ((S_818F9E48_1 *)effect)->unk_0C = value;
    }

    ((S_818F9E48_0 *)arg0)->unk_9A += 4;
    owner = ((S_818F9E48_0 *)arg0)->unk_2C;
    copy = ((S_818F9E48_2_pre *)owner)[-1].unk_00;
    motion = ((S_818F9E48_2_pre *)owner)[-1].unk_04;
    ((S_818F9E48_3 *)out)->unk_00 = ((S_818F9E48_4 *)copy)->unk_00;
    ((S_818F9E48_3 *)out)->unk_04 = ((S_818F9E48_4 *)copy)->unk_04;
    ((S_818F9E48_3 *)out)->unk_08 = ((S_818F9E48_4 *)copy)->unk_08;

    timer = ((S_818F9E48_0 *)arg0)->unk_00.s;
    if (timer == 0) {
        goto state_zero;
    }
    tail_value = 1;
    if (timer == tail_value) {
        one = 1;
        goto state_done;
    }
    func_80025908();
    return;

state_zero:
    ((S_818F9E48_0 *)arg0)->unk_00.u++;
    flags = ((S_818F9E48_1 *)effect)->unk_14 & 0xFF7F;
    ((S_818F9E48_1 *)effect)->unk_14 = flags;
    ((S_818F9E48_1 *)effect)->unk_14 = flags | (((S_818F9E48_5 *)motion)->unk_14 & 0xC);
    ((S_818F9E48_1 *)effect)->unk_10 = ((S_818F9E48_5 *)motion)->unk_10;
    ((S_818F9E48_1 *)effect)->unk_0C = ((S_818F9E48_5 *)motion)->unk_0C;
    ((S_818F9E48_1 *)effect)->unk_0D = ((S_818F9E48_5 *)motion)->unk_0D;
    ((S_818F9E48_1 *)effect)->unk_0E = ((S_818F9E48_5 *)motion)->unk_0E;
    ((S_818F9E48_5 *)motion)->unk_14 |= 0x80;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    one = 1;

state_done:
    derived.x = source.x + ((s16)source.z >> 1);
    derived.y = source.y + 0x48;
    old_x = ((S_818F9E48_5 *)motion)->unk_1C;
    old_y = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_1 *)effect)->unk_1C = old_x;
    ((S_818F9E48_1 *)effect)->unk_1E = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_5 *)motion)->unk_1E = 0x1000;
    ((S_818F9E48_5 *)motion)->unk_1C = 0x1000;
    func_80024CD4(arg0, ((S_818F9E48_0 *)arg0)->unk_2C, &source, &derived, one, one);
    ((S_818F9E48_5 *)motion)->unk_1C = old_x;
    ((S_818F9E48_5 *)motion)->unk_1E = old_y;

    timer = ((S_818F9E48_0 *)arg0)->unk_02.u + 1;
    ((S_818F9E48_0 *)arg0)->unk_02.u = timer;
    if (timer >= 0x65) {
        ((S_818F9E48_0 *)arg0)->unk_02.u = 0;
        ((S_818F9E48_0 *)arg0)->unk_00.u++;
        ((S_818F9E48_5 *)motion)->unk_14 &= 0xFF7F;
        ((S_818F9E48_6 *)(((S_818F9E48_0 *)arg0)->unk_30))->unk_9C = one;
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Separate packed source/derived locals preserve the 0x40 frame and retail slots.
   Guarded $t0/$a3 holds plus EffectState::levels recover the prologue and base-first loop adds.
   Zero-arg noreturn tails, a $v0 tail-slot pin, ordered CFG labels, and seam fences close the ABI. */
