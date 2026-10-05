#include "common.h"
#include "shared/object_flags.h"

/* Counts down a delay, then dims the effect color until completion. */
void func_80173F38(void *effect) {
    s16 state;
    u16 timer;

    state = *(s16 *)((u8 *)effect + 0xC);
    switch (state) {
    case 0:
        timer = *(u16 *)((u8 *)effect + 0xE) - 1;
        *(u16 *)((u8 *)effect + 0xE) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        *(u16 *)((u8 *)effect + 0xC) += 1;
        return;

    case 1:
        if (*(u8 *)((u8 *)effect + 8) < 0x11) {
            ObjectFlagBlock *flags = &objectFlagBlock;

            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            flags->flags |= 0x8000;
            return;
        } else {
            *(s32 *)((u8 *)effect + 8) += 0xFFEFEFF0;
            return;
        }
    }
}
