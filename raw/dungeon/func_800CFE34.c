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
    register u8 *owner ASM_REG("$19") = arg0;
    register u8 *dst ASM_REG("$23") = arg1;
    register u8 *entity ASM_REG("$17") = arg2;
    register u8 *record ASM_REG("$21");
    register u8 *effect ASM_REG("$22");
    register u8 *kind ASM_REG("$18");
    register u8 *coords ASM_REG("$20");
    register void *effect_data ASM_REG("$4");
    u8 *table;
    register s32 index ASM_REG("$16");
    register s32 comparison_index ASM_REG("$3");
    u8 *saved_effect;
    void *type;
    register s32 direction_index ASM_REG("$2");
    register s32 computed_index ASM_REG("$2");
    s16 effect_angle;
    u16 effect_angle_bits;

    ASM_KEEP(owner);
    ASM_KEEP(dst);
    ASM_KEEP(entity);
    record = PTR(owner, 0xAC);
    ASM_KEEP(record);
    effect = record + 0x20;
    ASM_KEEP(effect);
    effect_data = PTR(effect, 0x1C);
    ASM_KEEP(effect_data);
    kind = PTR(record, 0xC);
    ASM_KEEP(kind);
    coords = PTR(record, 8);
    ASM_KEEP(coords);

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
    ASM_SCHED_BARRIER();
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
