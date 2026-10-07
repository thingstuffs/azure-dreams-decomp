#include "shared/sound_state.h"
#include "common.h"

#include "common.h"



extern void func_800553D4(s32 a0);
extern void func_800550E8(void);
extern void func_80054F9C(s32 a0, SoundTask *a1);

/* Dispatches a status transition or queues a packed selection for playback. */
void func_8005500C(s32 code)
{
    s32 packed_code = code;

    code &= 0xF000;
    switch (code) {
    case 0:
    case 0x8000:
    case 0x9000:
    {
        SoundPlaybackState *state = &D_800847D0;
        s32 low_byte = packed_code & 0xFF;

        state->unk_26 = (s16)low_byte;
        code = packed_code & 0xF000;
        if (code != 0) {
            state->unk_26 = (s16)(low_byte | code);
        }
        if (D_800847D0.flags00 & 0x100) {
            func_80054F9C(0xB1, &D_800848F8);
            return;
        }
    }
        func_800550E8();
        return;
    case 0x1000:
        code = 0x71;
        break;
    case 0x2000:
        code = 0xE1;
        break;
    case 0x4000:
        code = 0xF1;
        break;
    default:
        return;
    }
    func_800553D4(code);
}
