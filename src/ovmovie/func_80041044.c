#include "modules/ovmovie_libpress.h"


/* Apply option flags to a command word and dispatch its update. */
void func_80177844(s32 *command, s32 flags)
{
    if (flags & 1) {
        *command &= ~0x08000000;
    } else {
        *command |= 0x08000000;
    }

    if (flags & 2) {
        *command |= 0x02000000;
    } else {
        *command &= ~0x02000000;
    }

    func_80177A9C(command, *(u16 *)command);
}
