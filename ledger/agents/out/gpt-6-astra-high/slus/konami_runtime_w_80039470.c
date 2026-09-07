#include "common.h"

#include "common.h"

typedef struct Func80039470Entry {
    s8 field_0;
    s8 field_1;
    u8 field_2;
    u8 pad_3;
    void *field_4;
} Func80039470Entry;

typedef struct Func80039470Block {
    u8 pad_00[0x10];
    void *type;
    u8 pad_14[0xC];
} Func80039470Block;

extern Func80039470Entry D_80082660[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern Func80039470Block *func_800392A4(s32 index);

/* Activates an unused entry and stores its pair of values according to the block type. */
s32 func_80039470(s32 entry_value, s32 first_value, s32 second_value, s32 packed_index) {
    Func80039470Entry *entries = D_80082660;
    u8 entry_index = packed_index;
    Func80039470Entry *entry = entries + entry_index;
    Func80039470Block *block;
    volatile Func80039470Block *header;
    void *type;

    if (entry->field_1 != 0) {
        goto failure;
    }
    if (entry_index == 0) {
        goto success;
    }

    block = func_800392A4(entry_index);
    if (block == 0) {
        goto success;
    }

    header = block - 1;
    entry->field_0 = packed_index >> 8;
    entry->field_1 = 1;
    entry->field_2 = entry_value;

    if (entry_index == 1 &&
        (type = header->type) != (void *)D_800C3174 &&
        type != (void *)D_800C321C) {
        *(s16 *)((u8 *)block + 0x36) = first_value;
        *(s16 *)((u8 *)block + 0x38) = second_value;
        goto success;
    }

    *(s16 *)((u8 *)block + 0x88) = first_value;
    *(s16 *)((u8 *)block + 0x8A) = second_value;

success:
    return 1;
failure:
    return 0;
}
