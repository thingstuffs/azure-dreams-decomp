#include "common.h"

extern void func_800A020C(void *, void *);
extern void func_800478B8(void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_800D5838(void);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s8 D_800DCECC[];
extern u8 D_800E23F8[];
extern u8 D_800E2400[];
extern u8 D_800E2408[];
extern u8 D_800E2420[];
extern u8 D_800E2428[];
extern u8 D_800E2438[];
extern u8 D_800E2440[];
extern u8 D_800E2450[];
extern u8 D_800E2458[];
extern u8 D_800E2460[];

#define PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))
#define S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define U8(base, off) (*(u8 *)((u8 *)(base) + (off)))

void func_800D5594(void *arg0, void *arg1, void *arg2)
{
    register u8 *owner ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *dst = arg1;
    u8 *entity = arg2;
    register u8 *record ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *effect;
    u8 *kind;
    register u8 *coords ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *effect_data;
    u8 *table;
    register s32 index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 comparison_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *saved_effect;
    void *type;
    s32 direction_index;
    register s32 computed_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 effect_angle;
    u16 effect_angle_bits;

    ASM_KEEP(owner);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    record = PTR(owner, 0xAC);
    effect = record + 0x20;
    ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    effect_data = PTR(effect, 0x1C);
    kind = PTR(record, 0xC);
    ASM_KEEP(kind);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    coords = PTR(record, 8);

    func_800A020C(effect_data, entity + 0xC);

    saved_effect = effect;
    if ((*(u32 *)(effect + 0x1C) & 0x20) == 0) {
        func_800478B8(entity);
    }

    if (PTR(kind, 0x2C) == D_800E2400) {
        func_800478B8(entity);
        func_800478B8(entity);
    }

    effect_angle = S16(effect, 0x2A);
    effect_angle_bits = U16(effect, 0x2A);
    if (S16(owner, 0x2A) != effect_angle) {
        U16(owner, 0x2A) = effect_angle_bits;
        func_80047784(
            entity,
            PTR(entity, 0x2C)[(D_80083228 + effect_angle + 0x100) >> 9 & 7],
            0);
    }

    table = D_80083160;
    computed_index =
        (S16(table, 0xC8) + S16(owner, 0x2A) + 0x100) >> 9;
    index = computed_index & 7;
    comparison_index = index;
    if (S16(owner, 0x94) != comparison_index) {
        func_80047784(entity, PTR(entity, 0x2C)[comparison_index], 0);
        S16(owner, 0x94) = index;
    }

    U16(entity, 0x14) = U16(kind, 0x14);
    U16(dst, 2) = U16(coords, 2);
    U16(dst, 6) = U16(coords, 6);
    U16(dst, 0xA) = U16(coords, 0xA);

    direction_index =
        (S16(table, 0xC8) + S16(owner, 0x2A) + 0x100) >> 9 & 7;
    S16(entity, 6) = (s32)D_800DCECC[direction_index] * 4;
    U16(entity, 0x1C) = U16(kind, 0x1C);
    U16(entity, 0x1E) = U16(kind, 0x1E);
    U16(entity, 0x12) = U16(kind, 0x12);

    if ((U16(record, 0x1E) & 0x8000) == 0) {
        type = PTR(kind, 0x2C);
        if (type == D_800E23F8 ||
            type == D_800E2408 ||
            type == D_800E2420 ||
            type == D_800E2428 ||
            type == D_800E2450 ||
            type == D_800E2458 ||
            type == D_800E2460 ||
            type == D_800E2440 ||
            type == D_800E2438) {
            U16(owner, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            U8(saved_effect, 0xB0)--;
            func_800D5838();
            return;
        }
        if ((func_80042900(effect, 0xA) << 16) == 0) {
            return;
        }
    }

    U16(owner, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}

/* MECHANISM: Unpinning the table base lets GCC save $fp and match the 0x40 frame/hold set.
   A non-volatile duplicate effect pointer naturally spills to sp+0x10 and fills the bnez delay.
   Split v0->s0->v1 index live ranges preserve the exact calculation and comparison coloring.
   func_800D5838 is a zero-source-argument tail call, reusing inherited $a0 and preserving its nop. */
