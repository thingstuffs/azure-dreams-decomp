#include "modules/dungeon_ovl_190081c.h"

void func_80024594(void *effect, Row_818E0D94_S_818E0D94_3 *position, Rec_D_80082E80 *sprite)
{
    Row_818E0D94_CallRecord transform;
    Row_818E0D94_OutputVector offset;
    Row_818E0D94_S_818E0D94_1 *effect_state;
    u16 size;
    s8 shade;

    effect_state = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_00;
    effect_state->unk_52 |= 0x8000;
    ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u16++;

    size = sprite->unk_1C.at02_u16.v - 0x50;
    sprite->unk_1C.at02_u16.v = size;
    sprite->unk_1C.at00_u16.v = size;

    {
        s32 phase;
        s32 height_jitter;
        s16 height;

        height_jitter = rand() & 0x3F;
        phase = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16 * 0x32;
        height = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_18;
        phase += 0xC8;
        height += 0x200;
        height += height_jitter;
        ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_18 = height;
        offset.x = func_800644B8(phase) / 80;
    }
    offset.y = 0;
    {
        s32 z_jitter;
        s32 neg_tick;

        z_jitter = rand() & 3;
        neg_tick = 0 - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16;
        offset.z = (neg_tick * 4) + z_jitter - 1;
    }

    shade = ((u8)offset.x + 0x28) - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u8;
    sprite->unk_0C.at01_s8.v = shade;
    sprite->unk_0C.at00_s8.v = shade;
    sprite->unk_0C.at02_s8.v = ((u8)offset.x + 0x60) - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u8;

    transform.field0 = &offset;
    transform.field4 = &offset;
    transform.field8 = *(Row_818E0D94_Unaligned8 *)((u8 *)effect + 0x14);
    transform.field10 = *(Row_818E0D94_Unaligned8 *)((u8 *)effect + 0x0C);
    transform.field18 = 1;
    transform.field1A = 0;
    func_800DBA90(&transform);

    position->unk_02 = offset.x;
    position->unk_06 = offset.y;
    position->unk_0A = offset.z;
    func_800478B8(sprite);

    if (sprite->unk_14.at00_u16.v & 0x6000) {
        sprite->unk_04.as_s8 = 0;
        sprite->unk_05.as_s8 = 0;
    }

    if (((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16 >= 0x20) {
        u32 *flags_base;

        ((Row_818E0D94_S_818E0D94_0_pre *)effect)[-1].unk_00 |= 0x8000;
        flags_base = (u32 *)0x80080000;
        flags_base[0x528] |= 0x8000;
    }
}
