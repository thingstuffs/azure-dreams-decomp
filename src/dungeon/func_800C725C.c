#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


/* Decrements the record countdown and marks completion when it reaches zero. */
void tick_byte_timed_trap_effect(void *record) {
    u8 countdown;

    countdown = *(u8 *)((u8 *)record + 7) - 1;
    *(u8 *)((u8 *)record + 7) = countdown;
    if (!(countdown & 0xFF)) {
        g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) - 1);
        *(u16 *)((u8 *)record - 2) =
            (u16)(*(u16 *)((u8 *)record - 2) | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
