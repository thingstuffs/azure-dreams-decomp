#include "common.h"

typedef struct {
    unsigned char bytes[16];
} Raw16;

typedef struct {
    s32 unused;
    s32 *dst;
} Entry;

typedef struct {
    unsigned char pad[0x5C];
    Entry **entries;
} Arg0;

extern Raw16 D_80089298;

/* Writes the table value at entry_index - 2 to the selected entry's destination. */
void func_800B3D04(Arg0 *entry_table, s32 entry_index) {
    Raw16 values;

    values = D_80089298;
    entry_table->entries[entry_index]->dst[0] = ((s32 *)values.bytes)[entry_index - 2];
}
