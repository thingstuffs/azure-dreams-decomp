#include "slus/gp_af3_pair.h"

#include "common.h"
s8 D_80080AF3 = -1;
#include "slus/gp_af3_pair.h"

static s16 D_80080AFC;
s32 select_sound_stream(s16 entry_index, s16 mode)
{
    if (D_8006E704[entry_index] == D_80080AF4[D_80080AFC]) {
        return 1;
    }

    D_80080AFC = (u16) D_80080AFC ^ 1;

    if (D_8006E704[entry_index] != D_80080AF4[D_80080AFC]) {
        func_800542BC();

        if (D_80080AF3 != mode) {
            wait_until_sound_idle();
        }

        D_8006E704[entry_index]->field_0 &= ~0x7FFFFF;
        D_8006E704[entry_index]->field_0 |=
            ((D_80080AFC != 0) ? (s32) D_801C4640 : (s32) D_801BEE40) & 0x7FFFFF;

        Control_CD(6, D_8006E704[entry_index], 0);
        D_80080AF4[D_80080AFC] = D_8006E704[entry_index];
        drain_cd_command_queue();
    }

    load_sound_set(mode);

    SD_Call((D_80080AFC != 0) ? 0x22 : 0x21);

    return 0;
}
#include "slus/gp_af3_pair.h"

s32 load_sound_set(s16 state_index)
{
    if (D_80080AF3 != state_index) {
        S_8006E6F4 *state_table = D_8006E6F4;
        S_8006E6F4 *state_entry = state_table + state_index;

        Control_CD(6, (void *)state_entry->field4, 0);
        DrawSync(0);
        {
            void *state_callback = state_entry->field0;
            D_80081480 = D_8008148C;
            Control_CD(6, state_callback, 0);
        }
        D_80080AF3 = (s8)state_index;
        drain_cd_command_queue();
        func_8003F5E0(D_8008148C);
        SD_Call(0x11);
        func_800542BC();
        while (test_sound_channel_availability(0) != 1) {
        }
        return 0;
    }
    return 1;
}
