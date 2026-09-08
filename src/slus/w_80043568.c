#include "common.h"

#include "common.h"

/* Replace state 0x39 with 2 in entries tagged 0x13 and their linked records. */
void func_80043568(void) {
    s32 slot;
    u32 ram_base;
    volatile u8 *cursor;
    u32 packed_index;
    s32 match_tag;
    s32 old_state;
    register s32 new_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    u32 record_index;

    slot = 0x3F;
    ram_base = 0x80010000;
    match_tag = 0x13;
    old_state = 0x39;
    new_state = 2;
    cursor = (volatile u8 *)(ram_base | 0xFC);
    do {
        if (cursor[0x981] == match_tag && cursor[0x980] == old_state) {
            packed_index = cursor[0x983];
            cursor[0x980] = new_state;
            record_index = packed_index & 0x3F;
            ((u8 *)ram_base)[record_index * 0x54 + 0xA93] = new_state;
        }
        slot -= 1;
        cursor -= 4;
    } while (slot >= 0);

    slot = 0x13;
    ram_base = 0x80010000;
    match_tag = slot;
    old_state = 0x39;
    new_state = 2;
    cursor = (volatile u8 *)(ram_base | 0x4C);
    do {
        if (cursor[0x249] == match_tag && cursor[0x248] == old_state) {
            cursor[0x248] = new_state;
        }
        if (cursor[0x21E9] == match_tag && cursor[0x21E8] == old_state) {
            packed_index = cursor[0x21EB];
            cursor[0x21E8] = new_state;
            record_index = packed_index & 0x1F;
            ((u8 *)ram_base)[record_index * 0x8C + 0x2273] = new_state;
        }
        slot -= 1;
        cursor -= 4;
    } while (slot >= 0);
}
