#include "common.h"
#include "shared/dungeon_status.h"

typedef struct S_800A2B5C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800A2B5C_0;   /* state in func_800A2B5C */



extern u16 func_800A2B28();

/* Sets or reuses the requested value and calls func_800A2B28 when state permits. */
s16 func_800A2B5C(s32 requested_value) {
    s32 current_value = ((s32)dungeonStatus.unk_0C);

    if (current_value != requested_value) {
        if (current_value != 0) {
            return 1;
        }
        if (((s32)dungeonStatus.unk_10) != 0) {
            return 1;
        }
        if (dungeonStatus.unk_0A != 0) {
            return 1;
        }
        if (dungeonStatus.flags & 8) {
            return 1;
        }
        dungeonStatus.unk_0C = requested_value;
    }
    return func_800A2B28();
}
