#include "common.h"

extern u8 runtime_state_restore_requested;
extern u32 runtime_saved_state_word;
extern u8 runtime_saved_state_byte_04_alias;
extern u8 runtime_saved_state_byte_06;

/* Restores saved state when requested; otherwise saves the current state. */
void runtime_save_or_restore_state(void)
{
    if (runtime_state_restore_requested != 0) {
        u8 *ram_page;
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        ram_page = (u8 *)0x80010000;
        state_word = runtime_saved_state_word;
        state_byte_4 = runtime_saved_state_byte_04_alias;
        state_byte_6 = runtime_saved_state_byte_06;
        runtime_state_restore_requested = 0;
        *(u32 *)(ram_page + 0x3180) = state_word;
        *(u8 *)(ram_page + 0x3184) = state_byte_4;
        *(u8 *)(ram_page + 0x3186) = state_byte_6;
    } else {
        u8 *ram_page;
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        ram_page = (u8 *)0x80010000;
        state_word = *(u32 *)(ram_page + 0x3180);
        state_byte_4 = *(u8 *)(ram_page + 0x3184);
        state_byte_6 = *(u8 *)(ram_page + 0x3186);
        runtime_saved_state_word = state_word;
        runtime_saved_state_byte_04_alias = state_byte_4;
        runtime_saved_state_byte_06 = state_byte_6;
    }
}
