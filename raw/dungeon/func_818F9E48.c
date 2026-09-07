#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register void *out ASM_REG("$8") = arg1;
    register void *effect ASM_REG("$7") = arg2;
    register s32 tail_value ASM_REG("$2");
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
    ASM_KEEP(out);
    ASM_KEEP(effect);
    D_800266BC = 1;
    FIELD(arg0, u16, 0x98) += 0xC8;

    if (FIELD(arg0, s16, 2) < 0x32) {
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

    timer = FIELD(arg0, s16, 2);
    if (timer < 0x15) {
        tail_value = (timer * 6) - 0x79;
        ASM_TAILSLOT_PIN(tail_value);
        func_80025758();
        return;
    }
    ASM_SCHED_BARRIER();
    if (timer >= 0x50) {
        value = ((0x64 - timer) * 6) - 0x80;
        FIELD(effect, u8, 0xE) = value;
        FIELD(effect, u8, 0xD) = value;
        FIELD(effect, u8, 0xC) = value;
    }

    FIELD(arg0, u16, 0x9A) += 4;
    owner = FIELD(arg0, void *, 0x2C);
    copy = FIELD(owner, void *, -0x18);
    motion = FIELD(owner, void *, -0x14);
    FIELD(out, s32, 0) = FIELD(copy, s32, 0);
    FIELD(out, s32, 4) = FIELD(copy, s32, 4);
    FIELD(out, s32, 8) = FIELD(copy, s32, 8);

    timer = FIELD(arg0, s16, 0);
    if (timer == 0) {
        goto state_zero;
    }
    tail_value = 1;
    ASM_KEEP(tail_value);
    if (timer == tail_value) {
        one = 1;
        goto state_done;
    }
    func_80025908();
    return;

state_zero:
    FIELD(arg0, u16, 0)++;
    flags = FIELD(effect, u16, 0x14) & 0xFF7F;
    FIELD(effect, u16, 0x14) = flags;
    FIELD(effect, u16, 0x14) = flags | (FIELD(motion, u16, 0x14) & 0xC);
    FIELD(effect, u16, 0x10) = FIELD(motion, u16, 0x10);
    FIELD(effect, u8, 0xC) = FIELD(motion, u8, 0xC);
    FIELD(effect, u8, 0xD) = FIELD(motion, u8, 0xD);
    FIELD(effect, u8, 0xE) = FIELD(motion, u8, 0xE);
    FIELD(motion, u16, 0x14) |= 0x80;
    ASM_SCHED_BARRIER();
    one = 1;

state_done:
    derived.x = source.x + ((s16)source.z >> 1);
    derived.y = source.y + 0x48;
    old_x = FIELD(motion, u16, 0x1C);
    old_y = FIELD(motion, u16, 0x1E);
    FIELD(effect, u16, 0x1C) = old_x;
    FIELD(effect, u16, 0x1E) = FIELD(motion, u16, 0x1E);
    FIELD(motion, u16, 0x1E) = 0x1000;
    FIELD(motion, u16, 0x1C) = 0x1000;
    func_80024CD4(arg0, FIELD(arg0, void *, 0x2C), &source, &derived, one, one);
    FIELD(motion, u16, 0x1C) = old_x;
    FIELD(motion, u16, 0x1E) = old_y;

    timer = FIELD(arg0, u16, 2) + 1;
    FIELD(arg0, u16, 2) = timer;
    if (timer >= 0x65) {
        FIELD(arg0, u16, 2) = 0;
        FIELD(arg0, u16, 0)++;
        FIELD(motion, u16, 0x14) &= 0xFF7F;
        FIELD(FIELD(arg0, void *, 0x30), s16, 0x9C) = one;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Separate packed source/derived locals preserve the 0x40 frame and retail slots.
   Guarded $t0/$a3 holds plus EffectState::levels recover the prologue and base-first loop adds.
   Zero-arg noreturn tails, a $v0 tail-slot pin, ordered CFG labels, and seam fences close the ABI. */
