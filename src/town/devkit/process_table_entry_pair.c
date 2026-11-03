#include "common.h"
#include "town/scene/flags.h"
#include "town/devkit.h"
extern u8 D_80700638[];
extern u8 D_8070063A[];

/* Process the pair of 16-bit table entries at byte offset four. */
void process_table_entry_pair(void) {
    s32 byte_offset;
    u16 second_entry;

    byte_offset = 4;
    do {
        clear_indexed_flag_bit_unless_index_one_80700d20(*(u16 *)(D_80700638 + byte_offset));
        second_entry = *(u16 *)(D_8070063A + byte_offset);
        byte_offset += 4;
        clear_indexed_flag_bit_unless_index_one_80700d20(second_entry);
    } while (byte_offset < 8);
}
