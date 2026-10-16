#include "modules/dungeon_ovl_7e71d800.h"

void func_800249DC(void *motion, Row_818E71DC_S_800249DC_2 *position, Row_818E71DC_S_800249DC_3 *visual) {
    s32 current_x;
    s32 current_y;
    s32 current_z;
    s32 delta;
    u16 ticks_left;
    Row_818E71DC_S_800249DC_1 *owner;

    owner = ((Rec_func_800249DC_arg0 *)motion)->unk_00.at00_pv.v;
    owner->unk_10 =
        (s32)(owner->unk_10 | 0x8000);

    ticks_left = ((Rec_func_800249DC_arg0 *)motion)->unk_48 - 1;
    ((Rec_func_800249DC_arg0 *)motion)->unk_48 = ticks_left;
    if ((ticks_left << 16) > 0) {
        ((Rec_func_800249DC_arg0 *)motion)->unk_1C =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_1C + ((Rec_func_800249DC_arg0 *)motion)->unk_34);
        ((Rec_func_800249DC_arg0 *)motion)->unk_20 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_20 + ((Rec_func_800249DC_arg0 *)motion)->unk_38);
        ((Rec_func_800249DC_arg0 *)motion)->unk_24 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_24 + ((Rec_func_800249DC_arg0 *)motion)->unk_3C);
    }

    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_1C;
    current_x = position->unk_00;
    delta -= current_x;
    position->unk_00 =
        (s32)(current_x + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_20;
    current_y = position->unk_04;
    delta -= current_y;
    position->unk_04 =
        (s32)(current_y + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_24;
    current_z = position->unk_08;
    delta -= current_z;
    position->unk_08 =
        (s32)(current_z + (delta / 5));

    func_800478B8(visual);
    if (visual->unk_14 & 0x6000) {
        visual->unk_04 = 0;
        visual->unk_05 = 0;
    }

    if ((u8)visual->unk_0C.u8 >= 0x60U) {
        ((Row_818E71DC_S_800249DC_0_pre *)motion)[-1].unk_00 =
            (u16)(((Row_818E71DC_S_800249DC_0_pre *)motion)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
        return;
    }

    visual->unk_0C.s32 += 0xC0C0C;
}
