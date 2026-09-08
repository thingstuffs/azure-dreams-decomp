#include "common.h"

typedef struct {
    int val;
    int pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

/* Load an indexed value divided by four and propagate the source flag. */
void func_7FDD3B24(void *entry) {
    u8 *value_data = *(u8 **)((u8 *) entry + 4);
    s32 value_index = *(s32 *)((u8 *) entry + 0x18);
    s16 scaled_value;

    scaled_value = (s16)(*(u16 *)(value_data + (value_index * 2) + 0xE) << 0x10 >> 0x12);
    *(s16 *)((u8 *) entry + 0x10) = scaled_value;
    if (*(s16 *)(value_data + 0x16) & 0x8000) {
        *(u16 *)((u8 *) entry - 2) = *(u16 *)((u8 *) entry - 2) | 0x8000;
        D_800814A0.val |= 0x8000;
    }
}
