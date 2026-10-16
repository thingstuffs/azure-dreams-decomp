#include "modules/dungeon_ovl_cc5000.h"

void func_801609A8(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 next_state;
    s32 start_state;
    u16 timer;

    state = ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B;
    start_state = 1;
    switch (state) {
    case 0:
        ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B = start_state;
                        /* fall through */
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }

        ((CL_CC5000_801729A8_S_801729A8_3 *)motion)->unk_14 = 0;
        ((CL_CC5000_801729A8_S_801729A8_3 *)motion)->unk_10 = 0;
        ((CL_CC5000_801729A8_S_801729A8_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801632DC;
        func_80047784(sprite,
            D_801632DC[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        next_state = ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B;
        ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.s = 0;
        next_state++;
        ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B = next_state;
        return;
    case 2:
        timer = ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.s + 1;
        ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.s = timer;
        if ((s16)timer == 7 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
        }
        if (((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.u == 6) {
            func_800A56E0(0x808);
        }
        if (((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.u == 8) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_96.u == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            next_state = ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B;
            next_state++;
            ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_9B = next_state;
        }
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((CL_CC5000_801729A8_S_801729A8_0 *)action)->unk_8C = func_8015F02C;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(actor);
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
