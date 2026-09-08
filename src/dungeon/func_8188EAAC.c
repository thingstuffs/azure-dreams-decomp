#include "common.h"

typedef struct S_800262AC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800262AC_0;   /* object in func_800262AC */

typedef struct S_800262AC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800262AC_1;   /* coords in func_800262AC */

typedef struct S_800262AC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
} S_800262AC_2;   /* render in func_800262AC */

typedef struct S_800262AC_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x6];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x36];
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0x2];
    s16 unk_64;
} S_800262AC_3;   /* state in func_800262AC */



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
    register s32 outer ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 inner;
    s32 kind;
    register s32 state_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 render_value;
    void *object;
    S_800262AC_1 *coords;
    S_800262AC_2 *render;
    S_800262AC_3 *state;
    void *callback;
    void *texture;

    if (func_8003FA44(0x30) == 0) {
        register void *zero ASM_REG("$2") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        ASM_TAILSLOT_PIN(zero);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
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
        ((S_800262AC_0 *)object)->unk_10 = callback;
        func_8004491C(object, &D_800CEEFC);
        coords = ((S_800262AC_0 *)object)->unk_08;
        coords->unk_0E = arg0;
        coords->unk_02 = arg0;
        coords->unk_12 = arg1;
        coords->unk_06 = arg1;
        coords->unk_16 = arg2;
        coords->unk_0A = arg2;
        render = ((S_800262AC_0 *)object)->unk_0C;
        render->unk_06 = 0x10;
        if (outer != 0) {
            func_80026378(render);
            return (void *)0x100;
        }
        render->unk_1E.s = 0x800;
        render_value = render->unk_1E.u;
        render->unk_14 = 0xC;
        render->unk_10 = 0x20;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        state_value = 8;
        render->unk_08 = texture;
        render->unk_1C = render_value;
        state = (u8 *)object + 0x20;
        state->unk_1A = state_value;
        state->unk_64 = state_value;
        state->unk_22 = inner;
        state->unk_24 = outer;
        state->unk_5C = arg0;
        state->unk_5E = arg1;
        state->unk_60 = arg2;
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
