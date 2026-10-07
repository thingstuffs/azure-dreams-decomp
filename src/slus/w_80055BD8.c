#include "shared/sound_state.h"
#include "common.h"

#include "common.h"


extern void func_800553D4(s32 code);
extern void func_80055C50(s16 index);

/* Releases the selected channel and sets its secondary status flag. */
void func_80055BD8(s16 channel)
{
    if ((channel << 16) == 0 && (D_800847D0.flags00 & 0x100)) {
        func_800553D4(0x71);
    }
    func_80055C50(channel);
    D_800847D0.flags04 |= 0x01000000 << channel;
}
