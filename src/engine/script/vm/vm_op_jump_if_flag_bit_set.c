#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script/vm.h"

typedef struct Func80039694State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
} Func80039694State;

/* Branches to the script target when the key check succeeds, otherwise skipping the target. */
u32 vm_op_24_jump_if_flag_bit_set(Func80039694State *state) {
    u32 key_addr = (u32)state->read_ptr;
    u32 key_low_byte = *(u8 *)key_addr;
    u32 key_high_byte = *(u8 *)(key_addr + 1);
    s16 key = (s16)(key_low_byte + (key_high_byte << 8));
    u32 target_addr;

    state->read_ptr = (u8 *)(key_addr + 2);
    if (test_resident_bitmap_bit(key) == 0) {
        u32 next_addr = (u32)state->read_ptr + 4;
        state->read_ptr = (u8 *)next_addr;
        return next_addr;
    } else {
        u8 *target_bytes = state->read_ptr;
        target_addr = target_bytes[0] + (target_bytes[1] << 8) + (target_bytes[2] << 16) + (target_bytes[3] << 24);
        state->read_ptr = (u8 *)target_addr;
        return target_addr;
    }
}
