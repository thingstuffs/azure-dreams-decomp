#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern s32 func_80401AA4(s32 arg0, void *arg1);
extern s32 func_80401C70(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 D_804094EC[];
extern s32 D_80136140[];
extern u8 D_8009DDD8[];

/* Looks up a slot's data and processes its record when the lookup succeeds. */
s32 func_8001AE2C(s32 slot_index) {
    u8 slot_data[32];
    s32 *lookup_key;
    s32 slot_offset;
    s32 lookup_result;
    s32 result;

    result = 1;
    func_80401BF4(slot_data, slot_index);
    if (D_804094EC[0] != 0) {
        lookup_key = D_80136140 + 1;
    } else {
        lookup_key = D_80136140;
    }
    slot_offset = slot_index << 7;
    lookup_result = func_80401AA4(*lookup_key, &slot_data[5]);
    *(s32 *)(D_8009DDD8 + slot_offset) = lookup_result;
    if (lookup_result != 0) {
        result = func_80401C70(slot_data, D_8009DDD8 + slot_offset, 1, 4);
        *(s32 *)(D_8009DDD8 + slot_offset) = 1;
    }
    return result;
}
