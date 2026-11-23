#include "common.h"
#include "shared/game_state.h"
#include "engine/entity.h"

/* Reset global state and clear flags in the primary and secondary entry arrays. */
void reset_entry_flags(void) {
    u8 *base;
    s32 i;

    base = (u8 *)0x80010000;
    GAME_STATE->ending_requested = 0;
    GAME_STATE->dungeon_mode_state = 0;
    GAME_STATE->carry.familiar_items[0] = 0xFF;
    GAME_STATE->carry.familiar_items[1] = 0xFF;
    GAME_STATE->carry.player.f4C = 0xFF;
    GAME_STATE->carry.player.f4D = 0xFF;
    for (i = 0; i < 20; i++) {
        GAME_STATE->items[i].unk_03 &= 0x5F;
        *(s32 *)(base + 0x304 + i * 0x54) &= ~0x4000;
    }
    base = (u8 *)0x80010000;
    for (i = 0; i < 64; i++) {
        *(s32 *)(base + 0xA94 + i * 0x54) &= ~0x4000;
    }
}
