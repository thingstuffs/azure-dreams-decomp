#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increment three dungeon state bytes by two, or set flags when the first reaches 0x80. */
s32 func_80170230(u16 *dataCursor)
{
    u8 firstStateByte = gameWork.view.unk_090;


    if (firstStateByte < 0x80U) {
        gameWork.view.unk_090 = firstStateByte + 2;
        gameWork.view.unk_091 += 2;
        gameWork.view.unk_092 += 2;
        return;
    }

    dataCursor[-1] |= 0x8000;
    return objectFlagBlock.flags |= 0x8000;
}
