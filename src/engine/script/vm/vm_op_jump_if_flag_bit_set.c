#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script/vm.h"

/* Opcode 0x18: If the 16-bit event flag is set, jump to the 32-bit address. */
u32 script_jump_if_flag_set(ScriptReader *state) {
    u32 key_addr = (u32)state->cursor;
    u32 key_low_byte = *(u8 *)key_addr;
    u32 key_high_byte = *(u8 *)(key_addr + 1);
    s16 key = (s16)(key_low_byte + (key_high_byte << 8));
    u32 target_addr;

    state->cursor = (u8 *)(key_addr + 2);
    if (test_resident_bitmap_bit(key) == 0) {
        u32 next_addr = (u32)state->cursor + 4;
        state->cursor = (u8 *)next_addr;
        return next_addr;
    } else {
        u8 *target_bytes = state->cursor;
        target_addr = target_bytes[0] + (target_bytes[1] << 8) + (target_bytes[2] << 16) + (target_bytes[3] << 24);
        state->cursor = (u8 *)target_addr;
        return target_addr;
    }
}
