#include "common.h"

/* Clears the table byte selected by the record's five-bit index. */
void clear_indexed_table_flag(void *record) {
    u8 *page = (u8 *)0x80010000;
    page[((((u8 *)record)[3] & 0x1F) * 0x54) + 0x303] = 0;
}
