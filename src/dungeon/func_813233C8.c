#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increments three state bytes while the first is below 0x80, otherwise sets flag bits. */
s32 func_8016ABC8(u16 *words)
{
    u8 state_value = gameWork.unk_0A8;

    if (state_value < 0x80U) {
        gameWork.unk_0A8 = state_value + 4;
        gameWork.unk_0A9 += 4;
        gameWork.unk_0AA += 4;
        return;
    }

    words[-1] |= 0x8000;
    return objectFlagBlock.flags |= 0x8000;
}
