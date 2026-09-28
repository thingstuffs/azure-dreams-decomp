#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increments three state bytes while the first is below 0x80, otherwise sets flag bits. */
s32 func_8016ABC8(u16 *words)
{
    u8 state_value = gameWork.view.unk_090;

    if (state_value < 0x80U) {
        gameWork.view.unk_090 = state_value + 4;
        gameWork.view.unk_091 += 4;
        gameWork.view.unk_092 += 4;
        return;
    }

    words[-1] |= 0x8000;
    return objectFlagBlock.flags |= 0x8000;
}
