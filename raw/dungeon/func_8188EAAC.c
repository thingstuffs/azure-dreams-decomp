#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80026378(void *);
extern void func_800263D4(void) __attribute__((noreturn));
extern s32 func_8003FA44(s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern s32 D_80025E48;
extern s32 D_80026490;
extern s32 D_800CEEFC[3];

void *func_800262AC(s16 arg0, s16 arg1, s16 arg2)
{
    register s32 outer ASM_REG("$18");
    s32 inner;
    s32 kind;
    register s32 state_value ASM_REG("$2");
    u16 render_value;
    void *object;
    void *coords;
    void *render;
    void *state;
    void *callback;
    void *texture;

    if (func_8003FA44(0x30) == 0) {
        register void *zero ASM_REG("$2") = 0;

        ASM_TAILSLOT_PIN(zero);
        func_800263D4();
    }
    outer = 2;

    callback = &D_80025E48;
    texture = &D_80026490;

outer_loop:
    inner = 15;
inner_loop:
    kind = 2;
    if (inner != 0) {
        kind = 0x202;
    }
    object = func_8003FC64(kind);
    if (object != 0) {
        FIELD(object, void *, 0x10) = callback;
        func_8004491C(object, &D_800CEEFC);
        coords = FIELD(object, void *, 8);
        FIELD(coords, s16, 0xE) = arg0;
        FIELD(coords, s16, 2) = arg0;
        FIELD(coords, s16, 0x12) = arg1;
        FIELD(coords, s16, 6) = arg1;
        FIELD(coords, s16, 0x16) = arg2;
        FIELD(coords, s16, 0xA) = arg2;
        render = FIELD(object, void *, 0xC);
        FIELD(render, s16, 6) = 0x10;
        if (outer != 0) {
            func_80026378(render);
            return (void *)0x100;
        }
        FIELD(render, u16, 0x1E) = 0x800;
        render_value = FIELD(render, volatile u16, 0x1E);
        FIELD(render, s16, 0x14) = 0xC;
        FIELD(render, s16, 0x10) = 0x20;
        ASM_SCHED_BARRIER();
        state_value = 8;
        ASM_KEEP(state_value);
        FIELD(render, void *, 8) = texture;
        FIELD(render, u16, 0x1C) = render_value;
        ASM_SCHED_BARRIER();
        state = (u8 *)object + 0x20;
        FIELD(state, s16, 0x1A) = state_value;
        FIELD(state, s16, 0x64) = state_value;
        FIELD(state, s16, 0x22) = inner;
        ASM_KEEP(outer);
        FIELD(state, s16, 0x24) = outer;
        FIELD(state, s16, 0x5C) = arg0;
        FIELD(state, s16, 0x5E) = arg1;
        FIELD(state, s16, 0x60) = arg2;
    }

    inner--;
    if (inner >= 0) {
        goto inner_loop;
    }
    outer--;
    if (outer >= 0) {
        goto outer_loop;
    }
    return object;
}

/* MECHANISM: Descending s2/s1 loops plus two held bases force the retail 0x38 nine-save frame.
   LEAD28 sinks a pinned zero into the first noreturn-j slot; LEAD22 preserves the second tail.
   A volatile u16 reread, two barriers, and a short v0=8 pin recover retail's v0/v1 schedule.
   Pinning outer to s2 before ASM_KEEP defeats zero-equivalence CSE without rotating the counters. */
