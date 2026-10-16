#include "modules/dungeon_ovl_1930844.h"

void dungeonDrawAFullScreenColorOverlayMarkEffectCompleteCountdownEnds(void *effect, void *unused, void *fade_state) {
    s8 green_blue;
    s8 frames_left;
    void *overlay;
    void *effect_state;

    effect_state = ((ovl_1930844_81911A8C_S_81911A8C_0 *)effect)->unk_00;
    ((ovl_1930844_81911A8C_S_81911A8C_1 *)effect_state)->unk_14 = (u16) (((ovl_1930844_81911A8C_S_81911A8C_1 *)effect_state)->unk_14 + 1);
    overlay = ((ovl_1930844_81911A8C_S_81911A8C_5 *)(((ovl_1930844_81911A8C_S_81911A8C_2 *)(((M2C_UNK *)&gameWork.unk_000)))->unk_00.s))->unk_8D0;
    ((ovl_1930844_81911A8C_S_81911A8C_5 *)(((ovl_1930844_81911A8C_S_81911A8C_2 *)(((M2C_UNK *)&gameWork.unk_000)))->unk_00.s))->unk_8D0 =
        (void *) (overlay + 0x10);
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_0C = 0x140;
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_0E = 0xE0;
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_08 = 0;
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_0A = 0;
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_04 = 0xC0;
    green_blue = -0x40 - (((ovl_1930844_81911A8C_S_81911A8C_4 *)fade_state)->unk_05 * 0xC);
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_06 = green_blue;
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_05 = green_blue;
    func_800667A8(overlay);
    ((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_07 = (u8) (((ovl_1930844_81911A8C_S_81911A8C_3 *)overlay)->unk_07 | 2);
    func_8006658C(((ovl_1930844_81911A8C_S_81911A8C_2 *)(((M2C_UNK *)&gameWork.unk_000)))->unk_00.u + 0xB0, overlay);
    frames_left = (u8) ((ovl_1930844_81911A8C_S_81911A8C_4 *)fade_state)->unk_05 - 1;
    ((ovl_1930844_81911A8C_S_81911A8C_4 *)fade_state)->unk_05 = frames_left;
    if ((frames_left << 0x18) == 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((ovl_1930844_81911A8C_S_81911A8C_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
