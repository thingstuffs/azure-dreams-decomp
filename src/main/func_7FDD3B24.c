#include "common.h"
#include "shared/object_flags.h"

/* Load an indexed value divided by four and propagate the source flag. */
void func_7FDD3B24(void *entry) {
    u8 *value_data = *(u8 **)((u8 *) entry + 4);
    s32 value_index = *(s32 *)((u8 *) entry + 0x18);
    s16 scaled_value;

    scaled_value = (s16)(*(u16 *)(value_data + (value_index * 2) + 0xE) << 0x10 >> 0x12);
    *(s16 *)((u8 *) entry + 0x10) = scaled_value;
    if (*(s16 *)(value_data + 0x16) & 0x8000) {
        *(u16 *)((u8 *) entry - 2) = *(u16 *)((u8 *) entry - 2) | 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
