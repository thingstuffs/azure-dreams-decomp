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

s32 func_80039470(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Func80039470Entry *base = D_80082660;
    u8 index = arg3;
    Func80039470Entry *entry = base + index;
    Func80039470Block *data;
    volatile Func80039470Block *header;
    void *type;

    if (entry->field_1 != 0) {
        goto failure;
    }
    if (index == 0) {
        goto success;
    }

    data = func_800392A4(index);
    if (data == 0) {
        goto success;
    }

    header = data - 1;
    entry->field_0 = arg3 >> 8;
    entry->field_1 = 1;
    entry->field_2 = arg0;

    if (index == 1 &&
        (type = header->type) != (void *)D_800C3174 &&
        type != (void *)D_800C321C) {
        *(s16 *)((u8 *)data + 0x36) = arg1;
        *(s16 *)((u8 *)data + 0x38) = arg2;
        goto success;
    }

    *(s16 *)((u8 *)data + 0x88) = arg1;
    *(s16 *)((u8 *)data + 0x8A) = arg2;

success:
    return 1;
failure:
    return 0;
}
