#include "common.h"


extern s32 clear_indexed_flag_bit_unless();
extern u8 D_807009B8[];
extern u8 D_807009BA[];

/* Process six pairs of 16-bit table entries starting at byte offset four. */
void grid_process_six_entry_pairs_a(void) {
    s32 byte_offset;
    u16 second_entry;

    byte_offset = 4;
    do {
        clear_indexed_flag_bit_unless(*(u16 *)(D_807009B8 + byte_offset));
        second_entry = *(u16 *)(D_807009BA + byte_offset);
        byte_offset += 4;
        clear_indexed_flag_bit_unless(second_entry);
    } while (byte_offset < 0x1C);
}
