#include "slus/gp_af3_pair.h"

static s16 D_80080AFC;
s32 func_8004437C(s16 entry_index, s16 mode)
{
    if (D_8006E704[entry_index] == D_80080AF4[D_80080AFC]) {
        return 1;
    }

    D_80080AFC = (u16) D_80080AFC ^ 1;

    if (D_8006E704[entry_index] != D_80080AF4[D_80080AFC]) {
        func_800542BC();

        if (D_80080AF3 != mode) {
            func_80044698();
        }

        D_8006E704[entry_index]->field_0 &= ~0x7FFFFF;
        D_8006E704[entry_index]->field_0 |=
            ((D_80080AFC != 0) ? (s32) D_801C4640 : (s32) D_801BEE40) & 0x7FFFFF;

        Control_CD(6, D_8006E704[entry_index], 0);
        D_80080AF4[D_80080AFC] = D_8006E704[entry_index];
        drain_cd_command_queue();
    }

    func_8004450C(mode);

    SD_Call((D_80080AFC != 0) ? 0x22 : 0x21);

    return 0;
}
