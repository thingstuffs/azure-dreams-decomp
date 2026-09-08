#include "common.h"

typedef struct {
    u8 pad[0x13];
    u8 f13;
} S_D_8006DE24;

extern S_D_8006DE24 D_8006DE24[];

/* Returns the table field selected by the byte at offset 8 of a three-byte entry. */
u8 func_800A35A4(s32 entry_addr, s32 entry_index) {
    S_D_8006DE24 *lookup_table = D_8006DE24;

    entry_addr = entry_addr + entry_index * 3;
    return lookup_table[*(u8 *)(entry_addr + 8)].f13;
}
