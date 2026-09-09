#include "common.h"

extern void func_800A020C(void *, void *);
extern void func_800478B8(void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80042900(void *, s32);

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

/* Updates entity appearance, position, and facing from its owner and effect state. */
void func_800D5594(void *owner_data, void *position_data, void *entity_data)
{
    register u8 *owner ASM_REG("$19") = owner_data;
    u8 *position = position_data;
    u8 *entity = entity_data;
    register u8 *record ASM_REG("$21");
    u8 *effect;
    u8 *appearance;
    register u8 *coords ASM_REG("$20");
    void *effect_data;
    u8 *angle_table;
    register s32 facing_index ASM_REG("$16");
    register s32 facing_check ASM_REG("$3");
    u8 *saved_effect;
    void *appearance_type;
    s32 direction_index;
    register s32 angle_sector ASM_REG("$2");
    s16 effect_angle;
    u16 effect_angle_bits;

    ASM_KEEP(owner);
    ASM_KEEP(position);
    ASM_KEEP(entity);
    record = PTR(owner, 0xAC);
    effect = record + 0x20;
    ASM_KEEP(effect);
    effect_data = PTR(effect, 0x1C);
    appearance = PTR(record, 0xC);
    ASM_KEEP(appearance);
    coords = PTR(record, 8);

    func_800A020C(effect_data, entity + 0xC);

    saved_effect = effect;
    if ((*(u32 *)(effect + 0x1C) & 0x20) == 0) {
        func_800478B8(entity);
    }

    if (PTR(appearance, 0x2C) == D_800E2400) {
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

    angle_table = D_80083160;
    angle_sector =
        (S16(angle_table, 0xC8) + S16(owner, 0x2A) + 0x100) >> 9;
    facing_index = angle_sector & 7;
    facing_check = facing_index;
    if (S16(owner, 0x94) != facing_check) {
        func_80047784(entity, PTR(entity, 0x2C)[facing_check], 0);
        S16(owner, 0x94) = facing_index;
    }

    U16(entity, 0x14) = U16(appearance, 0x14);
    U16(position, 2) = U16(coords, 2);
    U16(position, 6) = U16(coords, 6);
    U16(position, 0xA) = U16(coords, 0xA);

    direction_index =
        (S16(angle_table, 0xC8) + S16(owner, 0x2A) + 0x100) >> 9 & 7;
    S16(entity, 6) = (s32)D_800DCECC[direction_index] * 4;
    U16(entity, 0x1C) = U16(appearance, 0x1C);
    U16(entity, 0x1E) = U16(appearance, 0x1E);
    U16(entity, 0x12) = U16(appearance, 0x12);

    if ((U16(record, 0x1E) & 0x8000) == 0) {
        appearance_type = PTR(appearance, 0x2C);
        if (appearance_type == D_800E23F8 ||
            appearance_type == D_800E2408 ||
            appearance_type == D_800E2420 ||
            appearance_type == D_800E2428 ||
            appearance_type == D_800E2450 ||
            appearance_type == D_800E2458 ||
            appearance_type == D_800E2460 ||
            appearance_type == D_800E2440 ||
            appearance_type == D_800E2438) {
            U16(owner, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            U8(saved_effect, 0xB0)--;
            return;
        }
        if ((func_80042900(effect, 0xA) << 16) == 0) {
            return;
        }
    }

    U16(owner, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
