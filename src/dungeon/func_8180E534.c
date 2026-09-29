#include "common.h"

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_800B835C(void *, void *, s32, s32);
extern u8 D_8002744C[9];
extern u8 D_80028880[9];
extern u8 D_8002888C[9];
extern s16 D_80083228;
extern s32 D_800CEEFC[3];
/* Creates four groups of 32 effect objects with angularly distributed motion. */
void *func_80027534(s16 pos_x, s16 pos_y, s16 pos_z)
{
    s32 rect[2];
    s32 angle;
    u16 facing;
    s32 base_angle;
    s32 motion_angle;
    s32 scale_shift;
    s32 sample_angle;
    s32 sample_index;
    s32 group_index;
    void *effect;
    u8 *positions;
    u8 *effect_state;
    u8 *sprite;
    void *data;
    void *callback = D_8002744C;

    rect[0] = 0x01800380;
    rect[1] = 0x400040;
    angle = ((D_80083228 + 0x500) >> 9) & 7;
    facing = (u8)angle << 9;
    sprite = D_8002888C;
    data = rect;
    func_800B835C(sprite, data, 1, 0);
    base_angle = angle << 9;
    group_index = 0;
next_group:
    sample_index = 0;
    motion_angle = base_angle + 0x400;
    scale_shift = 5 - group_index;
spawn:
    effect = func_8003FC64(0x202);
    if (effect != 0) {
        *(void **)((u8 *)effect + 0x10) = callback;
        data = D_800CEEFC;
        func_8004491C(effect, data);
        positions = *(u8 **)((u8 *)effect + 8);
        *(s16 *)(positions + 2) = pos_x;
        *(s16 *)(positions + 0xE) = pos_x;
        *(s16 *)(positions + 6) = pos_y;
        *(s16 *)(positions + 0x12) = pos_y;
        *(s16 *)(positions + 0xA) = pos_z;
        *(s16 *)(positions + 0x16) = pos_z;
        sample_angle = sample_index << 7;
        effect_state = (u8 *)effect + 0x20;
        *(s32 *)(effect_state + 0xC) = (func_80064584(motion_angle) * func_80064584(sample_angle)) >> scale_shift;
        *(s32 *)(effect_state + 0x10) = (func_800644B8(motion_angle) * func_80064584(sample_angle)) >> scale_shift;
        *(s32 *)(effect_state + 0x14) = func_800644B8(sample_angle) << ((group_index >> 1) + 7);
        sprite = *(u8 **)((u8 *)effect + 0xC);
        data = (void *)0x808080;
        *(s16 *)(sprite + 0x1E) = 0x400;
        *(s16 *)(sprite + 0x1C) = 0x400;
        *(void **)(sprite + 8) = D_80028880;
        *(s16 *)(sprite + 0x10) = 0x20;
        *(s32 *)(sprite + 0xC) = (s32)data;
        *(u16 *)(sprite + 0x14) |= 0xC;
        *(s16 *)(effect_state + 0x66) = 0xC;
        *(u16 *)(effect_state + 0x74) = facing;
    }
    sample_index++;
    if (sample_index < 0x20) {
        goto spawn;
    }
    group_index++;
    if (group_index < 4) {
        goto next_group;
    }
    return effect;
}
