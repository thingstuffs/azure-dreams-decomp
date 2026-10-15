#include "common.h"

extern s32 D_800D0460;
extern void SD_Call(s32);

/* Choose the sound command from the global mode flag. */
void func_80094910(void) {
    if (D_800D0460 != 0) {
        SD_Call(0x517);
        return;
    }
    SD_Call(0x508);
}
