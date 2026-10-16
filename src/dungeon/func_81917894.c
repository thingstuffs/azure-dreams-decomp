#include "modules/dungeon_ovl_1936800.h"

void dungeonAdvanceTheEffectPhaseBrightnessScalePositionUntilLifetimeEnds(void *effect, void *transform, void *visual) {
    s32 scale;
    s16 phase;
    u8 brightness;
    void *owner;

    owner = ((Row_81917894_S_80025094_0 *)effect)->unk_00;
    ((Row_81917894_S_80025094_1 *)owner)->unk_14 = (u16) (((Row_81917894_S_80025094_1 *)owner)->unk_14 + 1);
    func_800478B8(visual);
    ((Row_81917894_S_80025094_0 *)effect)->unk_06.u = (u16) (((Row_81917894_S_80025094_0 *)effect)->unk_06.u + 1);
    ((Rec_D_80082E80 *)visual)->unk_1A.as_u16 = (u16) (((Rec_D_80082E80 *)visual)->unk_1A.as_u16 + 0x200);
    phase = ((Row_81917894_S_80025094_0 *)effect)->unk_04.s;

    switch (phase) {
    case 0:
    {
        u16 radius;

        if (((Row_81917894_S_80025094_0 *)effect)->unk_06.u & 1) {
            radius = ((Row_81917894_S_80025094_0 *)effect)->unk_0A + 2;
        } else {
            radius = ((Row_81917894_S_80025094_0 *)effect)->unk_0A + 1;
        }
        ((Row_81917894_S_80025094_0 *)effect)->unk_0A = radius;
    }
        brightness = ((Rec_D_80082E80 *)visual)->unk_0C.at02_u8.v + 3;
        ((Rec_D_80082E80 *)visual)->unk_0C.at02_u8.v = brightness;
        ((Rec_D_80082E80 *)visual)->unk_0C.at01_u8.v = brightness;
        ((Rec_D_80082E80 *)visual)->unk_0C.at00_u8.v = brightness;
        scale = ((Row_81917894_S_80025094_0 *)effect)->unk_06.s << 5;
        ((Rec_D_80082E80 *)visual)->unk_1C.at02_s16.v = scale;
        ((Rec_D_80082E80 *)visual)->unk_1C.at00_s16.v = scale;
        ((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v =
            (u16) (((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v - 2);
    case 1:
        if ((s16) ((Row_81917894_S_80025094_0 *)effect)->unk_06.u >= 0x20) {
            ((Row_81917894_S_80025094_0 *)effect)->unk_06.u = 0U;
            ((Row_81917894_S_80025094_0 *)effect)->unk_04.u =
                (u16) (((Row_81917894_S_80025094_0 *)effect)->unk_04.u + 1);
        }
        break;
    case 2:
        if ((s16) ((Row_81917894_S_80025094_0 *)effect)->unk_06.u >=
            ((Row_81917894_S_80025094_0 *)effect)->unk_08) {
            dungeonCreateAnOrientedEffectBetweenPositionOwner(effect, transform);
            (*(u16 *)((u8 *)effect + (-2))) =
                (u16) (((Row_81917894_S_80025094_0_pre *)effect)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        break;
    }

    ((Rec_func_80024E80_arg1 *)transform)->unk_00.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_0E
        + ((s32) ((func_80064584(((Row_81917894_S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((Row_81917894_S_80025094_0 *)effect)->unk_0A)
           >> 8));
    ((Rec_func_80024E80_arg1 *)transform)->unk_04.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_12
        + ((s32) ((func_800644B8(((Row_81917894_S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((Row_81917894_S_80025094_0 *)effect)->unk_0A)
           >> 8));
}
