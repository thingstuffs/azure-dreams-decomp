#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"


/* Decrease three state bytes, or set entry and global flags below the threshold. */
void func_801701CC(u16 *entry)
{

    if (gameWork.unk_0A8 >= 0x3D) {
        gameWork.unk_0A8 -= 2;
        gameWork.unk_0A9 -= 2;
        gameWork.unk_0AA -= 2;
        return;
    }

    entry[-1] |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
