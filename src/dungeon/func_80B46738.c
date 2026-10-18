#include "modules/dungeon_resource12_slot0.h"

void dim_effect_after_delay(void *effect) {
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
            ObjectFlagBlock *flags = &object_flag_block;

            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            flags->flags |= 0x8000;
            return;
        } else {
            *(s32 *)((u8 *)effect + 8) += 0xFFEFEFF0;
            return;
        }
    }
}
