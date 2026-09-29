#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 bytes[8];
} ByteBlock8;

extern ByteBlock8 D_80016164;

/* Sum the weights selected by type flags for enabled records. */
s32 func_8001AF7C(void) {
    ByteBlock8 weights;
    s32 record_index;
    s32 total_weight;
    u8 flags;
    u8 *record_data;
    u8 *type_table;
    u8 *record;

    total_weight = 0;
    type_table = **(u8 ***)((u8 *)D_80016000 + 0x30);
    weights = D_80016164;
    record_index = total_weight;
    do {
        record_data = *(u8 **)((u8 *)D_80016000 + 0x38);
        record = record_data + (record_index * 2);
        flags = type_table[(record[0x33A4] << 5) + 2];
        if (flags & 1) {
            total_weight += weights.bytes[(flags >> 3) & 7];
        }
        record_index++;
    } while (record_index < 0x22);
    return total_weight;
}
