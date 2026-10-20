#include "common.h"
#include "shared/object_flags.h"

typedef struct MainValue {
    u8 pad0[0xC];
    s16 type;
    u8 padE[8];
    s16 flags;
} MainValue;

extern u16 D_8008B368[];
extern u16 D_8008B36A[];
extern u16 D_8008B36C[];

/* Sets output fields from the value's type and propagates its high flag bit. */
void fill_value_output_fields(MainValue **value_slot, u8 *output, MainValue *value)
{
    value = *value_slot;
    if (value->type == 0 && (value->flags & 2) != 0) {
        *(u16 *)(output + 2) = D_8008B36A[0];
    } else {
        *(u16 *)(output + 2) = D_8008B368[0];
    }
    *(u16 *)(output + 6) = D_8008B36C[value->type];
    if ((value->flags & 0x8000) != 0) {
        *(u16 *)((u8 *)value_slot - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
