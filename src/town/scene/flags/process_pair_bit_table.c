/* Relinked copy of town/func_808813CC (func_808813CC.c); retail differs only at relocation sites. */
#include "common.h"


extern void func_80700C28(s32 bit_index);
extern u8 D_80700714[];
extern u8 D_80700716[];

/* Process the pair of 16-bit table entries at byte offset four. */
void process_pair_16_bit_table(void) {
    s32 byte_offset;
    u16 second_entry;

    byte_offset = 4;
    do {
        func_80700C28(*(u16 *)(D_80700714 + byte_offset));
        second_entry = *(u16 *)(D_80700716 + byte_offset);
        byte_offset += 4;
        func_80700C28(second_entry);
    } while (byte_offset < 8);
}
