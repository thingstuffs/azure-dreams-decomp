#include "common.h"
extern int abs(int);

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define S32(p, off) FIELD(p, s32, off)
#define U16(p, off) FIELD(p, u16, off)
#define S16(p, off) FIELD(p, s16, off)
#define U8(p, off) FIELD(p, u8, off)

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    u8 pad00[0x34];
    u16 frame;
} AnimState;

typedef struct S_81958F28_0 {
    u8 pad_00[0x8];
    void *unk_08;
} S_81958F28_0;   /* state in func_80024728 */

typedef struct S_81958F28_1 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} S_81958F28_1;   /* node in func_80024728 */

extern void func_80024024(void *, s16, Vec3i *);
extern void func_80024654(s16, s16, s16, s16, s16, s16, Vec3s *);
extern s32 func_80025344(s16, s16, s16, s16);
extern void func_8003DE58(s32, u8 *, Vec3s *, s32);
extern void func_8004491C(void *, void *);

extern u16 D_800281F8;
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083780[];
extern s32 D_800CEEFC;
extern s32 *D_800E3D18;
extern u8 *D_800E3D7C;

/* Per-frame update for a following color effect: blend its position and shade toward a target node or a palette color, then fade it out over its lifetime. */
void func_81958F28(AnimState *state, void *pos, void *tint) {
    Vec3s effect;
    Vec3i delta;
    Vec3s color;
    s32 diff;
    s32 iter;
    s16 steps;
    u16 fade;
    u16 raw;
    s16 phase;
    void *node;
    void *target;
    void *child;

    D_800281F8++;
    state->frame++;
    phase = S16(state, 0x2C);

    if (phase == 1) {
        goto main_phase;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto setup_phase;
        }
        return;
    }
    if (phase == 2) {
        goto fade_phase;
    }
    return;

setup_phase:
    func_8004491C((u8 *)state - 0x20, &D_800CEEFC);
    U16(state, 0x2C)++;

main_phase:
    node = ((S_81958F28_0 *)state)->unk_08;
    if (node != 0) {
        goto node_phase;
    }

    phase = S16(state, 0x2E);
    if (phase != 0) {
        goto move_phase;
    }

    func_80024654(
        S16(pos, 2),
        S16(pos, 6),
        S16(pos, 0xA),
        S16(state, 0x14),
        S16(state, 0x16),
        S16(state, 0x18),
        &color);

    {
        u16 value;
        raw = U16(state, 0xC);
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        U16(state, 0xC) = value;
    }
    {
        u16 value;
        raw = U16(state, 0xE);
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        U16(state, 0xE) = value;
    }
    {
        u16 value;
        raw = U16(state, 0x10);
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        U16(state, 0x10) = value;
    }
    {
        u16 value;
        raw = (u16)color.x;
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        color.x = value;
    }
    {
        u16 value;
        raw = (u16)color.y;
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        color.y = value;
    }
    {
        u16 value;
        raw = (u16)color.z;
        value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
        color.z = value;
    }

    {
        s32 currentValue;
        s32 isClose;

        diff = color.x;
        currentValue = S16(state, 0xC);
        diff = diff - currentValue;
        diff = abs(diff);
        isClose = diff < 0x801;
        currentValue = (u16)color.x;
        if (!isClose) {
            color.x = (U16(state, 0xC) & 0xF000) | (currentValue & 0xFFF);
        }
    }

    {
        s32 currentValue;
        s32 isClose;

        diff = color.y;
        currentValue = S16(state, 0xE);
        diff = diff - currentValue;
        diff = abs(diff);
        isClose = diff < 0x801;
        currentValue = (u16)color.y;
        if (!isClose) {
            color.y = (U16(state, 0xE) & 0xF000) | (currentValue & 0xFFF);
        }
    }

    {
        s32 isClose;

        diff = color.z - S16(state, 0x10);
        diff = abs(diff);
        isClose = diff < 0x801;
        {
            s32 rawValue;
            s32 newValue;

            rawValue = U16(state, 0x10);
            if (!isClose) {
                newValue = rawValue & 0xF000;
                newValue |= ((u16)color.z & 0xFFF);
                color.z = newValue;
            }
        }
    }

    U16(state, 0xC) += (color.x - S16(state, 0xC)) >> 2;
    U16(state, 0xE) += (color.y - S16(state, 0xE)) >> 2;
    U16(state, 0x10) += (color.z - S16(state, 0x10)) >> 2;

    func_80024024((u8 *)state + 0xC, S16(state, 0x3A), &delta);
    S32(pos, 0) += delta.x;
    S32(pos, 4) += delta.y;
    S32(pos, 8) += delta.z;

    S16(state, 0x3A) = 0xA0;
    U16(state, 0x30)--;
    if (S16(state, 0x30) <= 0) {
        u8 *base = D_80083780;
        s32 tableAddress;
        color.x = U16(base, 2);
        color.y = U16(base, 6);
        color.z = U16(D_800E3D7C, 0x88) - 0x50;
        tableAddress =
            ((D_80083228 + S16(D_800E3D7C, 0x2A) + 0x100) >> 7) & 0x1C;
        tableAddress += (s32)D_800E3D18;
        func_8003DE58(
            *(s32 *)tableAddress,
            D_80082E80,
            &effect,
            0);
        color.x += effect.x;
        S16(state, 0x14) = color.x;
        color.y += effect.y;
        S16(state, 0x16) = color.y;
        color.z += effect.z;
        S16(state, 0x18) = color.z;
        S16(state, 0x2E) = 1;
        S16(state, 0x30) = 8;
    }
    {
        u32 shade;
        shade = U8(tint, 0xC);
        if (shade >= 0x80) goto update_secondary;
        S32(tint, 0xC) += 0x00080808;
        goto update_secondary;
    }

move_phase:
    if (phase != 1) {
        goto update_secondary;
    }
    steps = S16(state, 0x30);
    if (steps > 0) {
        U16(pos, 2) += (S16(state, 0x14) - S16(pos, 2)) / steps;
        U16(pos, 6) += (S16(state, 0x16) - S16(pos, 6)) / S16(state, 0x30);
        U16(pos, 0xA) += (S16(state, 0x18) - S16(pos, 0xA)) / S16(state, 0x30);
    }
    U16(state, 0x30)--;
    if (S16(state, 0x30) <= 0) {
        S16(state, 0x30) = 0;
        U16(pos, 2) = U16(state, 0x14);
        U16(pos, 6) = U16(state, 0x16);
        U16(pos, 0xA) = U16(state, 0x18);
        if (func_80025344(
                S16(state, 0x14),
                S16(state, 0x16),
                (s16)(U16(state, 0x18) + 0x10),
                0)) {
            iter = 3;
            do {
                func_80025344(
                    S16(state, 0x14),
                    S16(state, 0x16),
                    (s16)(U16(state, 0x18) + 0x10),
                    (s16)iter);
                iter--;
            } while (iter >= 2);
            S16(state, 0x30) = 8;
            U16(state, 0x2C)++;
        }
    }

update_secondary:
    if (U16(state, 0x34) & 1) {
        S32(pos, 0xC) += (S32(pos, 0) - S32(pos, 0xC)) >> 2;
        S32(pos, 0x10) += (S32(pos, 4) - S32(pos, 0x10)) >> 2;
        S32(pos, 0x14) += (S32(pos, 8) - S32(pos, 0x14)) >> 2;
    }
    return;

node_phase:
    if (U16(node, 0x1E) & 0x8000) {
        S16(state, 0x30) = 2;
        U16(state, 0x2C)++;
    }
    node = ((S_81958F28_0 *)state)->unk_08;
    target = ((S_81958F28_1 *)node)->unk_08;
    S32(pos, 0) += (S32(target, 0) - S32(pos, 0)) >> 2;
    S32(pos, 4) += (S32(target, 4) - S32(pos, 4)) >> 2;
    S32(pos, 8) += (S32(target, 8) - S32(pos, 8)) >> 2;

    if (U16(state, 0x34) & 1) {
        S32(pos, 0xC) += (S32(pos, 0) - S32(pos, 0xC)) >> 2;
        S32(pos, 0x10) += (S32(pos, 4) - S32(pos, 0x10)) >> 2;
        S32(pos, 0x14) += (S32(pos, 8) - S32(pos, 0x14)) >> 2;
    }

    node = ((S_81958F28_0 *)state)->unk_08;
    child = ((S_81958F28_1 *)node)->unk_0C;
    if (U8(child, 0xC) < U8(tint, 0xC)) {
        U8(tint, 0xC) = U8(child, 0xC);
    }
    if (U8(child, 0xD) < U8(tint, 0xD)) {
        U8(tint, 0xD) = U8(child, 0xD);
    }
    if (U8(child, 0xE) < U8(tint, 0xE)) {
        U8(tint, 0xE) = U8(child, 0xE);
    }
    if ((s32)U8(tint, 0xC) < 0x80 - (S16(state, 0x38) * 8)) {
        S32(tint, 0xC) += 0x00080808;
    }
    return;

fade_phase:
    if (U16(state, 0x34) & 1) {
        S32(pos, 0xC) += (S32(pos, 0) - S32(pos, 0xC)) >> 2;
        S32(pos, 0x10) += (S32(pos, 4) - S32(pos, 0x10)) >> 2;
        S32(pos, 0x14) += (S32(pos, 8) - S32(pos, 0x14)) >> 2;
    }
    fade = U8(tint, 0xC);
    fade -= fade / S16(state, 0x30);
    U8(tint, 0xC) = fade;
    U8(tint, 0xD) = fade;
    U8(tint, 0xE) = fade;
    U16(state, 0x30)--;
    if (S16(state, 0x30) <= 0) {
        U16(state, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
