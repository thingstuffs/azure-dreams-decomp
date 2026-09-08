#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E3D7C;

typedef struct S_800C82B8_0 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800C82B8_0;   /* var_v1 in func_800C82B8 */

typedef struct S_800C82B8_1 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C82B8_1;   /* arg0 in func_800C82B8 */

/* Counts the two occupied slots when the current entity has flag 8 set. */
s32 func_800C82B8(void *entity) {
    s32 slot_index;
    s32 active_count;
    void *slot_base;

    active_count = 0;
    if (entity == D_800E3D7C) {
        slot_index = 1;
        slot_base = entity + 4;
        do {
            if ((((S_800C82B8_0 *)slot_base)->unk_AC != 0) && (((S_800C82B8_1 *)entity)->unk_54 & 8)) {
                active_count += 1;
            }
            slot_index -= 1;
            slot_base -= 4;
        } while (slot_index >= 0);
    }
    return active_count;
}
