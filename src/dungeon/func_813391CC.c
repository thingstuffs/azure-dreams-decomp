#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"


/* Decrease three state bytes, or set entry and global flags below the threshold. */
void func_801701CC(u16 *entry)
{

    if (gameWork.view.unk_090 >= 0x3D) {
        gameWork.view.unk_090 -= 2;
        gameWork.view.unk_091 -= 2;
        gameWork.view.unk_092 -= 2;
        return;
    }

    entry[-1] |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
