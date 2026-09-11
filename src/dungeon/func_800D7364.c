#include "common.h"

typedef struct Entry {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Entry;

extern void func_800DC628(void *arg0, s32 arg1);

/* Initialize nine entry links and values, set defaults, and apply the optional flag. */
void func_800DCAC4(void *entry_data, s32 enable_flag) {
    s32 entry_index;
    s32 record_offset;

    for (entry_index = 0; entry_index < 9; entry_index++) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field4 =
            (s32)(((Entry *)*(s8 **)((s8 *)entry_data + 4)) + entry_index);
    }

    entry_index = 0;
    record_offset = entry_index;
    for (; entry_index < 9; entry_index++, record_offset += 0xC) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field8 =
            (s32)(*(s8 **)((s8 *)entry_data + 8) + record_offset);
    }

    for (entry_index = 0; entry_index < 9; entry_index++) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field0 =
            ((s32 *)*(s8 **)((s8 *)entry_data + 0xC))[entry_index];
    }

    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x12) = 0x5F;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x1E) = 0x61;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x44) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 4) + 0x88) = 0x9A;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 4) + 0x8A) = 0x69;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x68) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x60) = 0x800;

    if (enable_flag != 0) {
        return func_800DC628(entry_data, 0x400);
    }
    func_800DC628(entry_data, 0);
}
