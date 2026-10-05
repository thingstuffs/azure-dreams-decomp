#include "common.h"

extern void func_80021B18(void *dest, s32 suffix_index);
extern s32 func_80021A04(s32 count, u8 *text);
extern s32 func_80021B98(void *path, void *buffer, s32 read_size, s32 block_offset);
extern s32 D_800287CC;
extern s32 D_80084128[];
extern s32 D_80083E98[];

/* Looks up a slot's record and processes it when present. */
s32 func_80021D54(s32 slot) {
    s32 record_data[8];
    s32 *source_id;
    u8 *state_base;
    s32 *slot_state;
    s32 lookup_result;
    s32 result;

    result = 1;
    func_80021B18(record_data, slot);
    source_id = &D_80084128[0];
    if (D_800287CC != 0) {
        source_id = &D_80084128[1];
    }
    lookup_result = func_80021A04(*source_id, (u8 *)record_data + 5);
    state_base = (u8 *)D_80083E98;
    slot_state = (s32 *)(state_base + (slot << 7));
    *slot_state = lookup_result;
    if (lookup_result != 0) {
        result = func_80021B98(record_data, slot_state, 1, 4);
        *slot_state = 1;
    }
    return result;
}
