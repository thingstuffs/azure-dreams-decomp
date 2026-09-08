#include "common.h"

typedef struct {
    s8 unused0;
    u8 active;
    u8 unused2[2];
} Slot;

typedef struct {
    u8 unused0[6];
    u8 x;
    u8 y;
    u8 unused8[0x10];
} Status;

extern Status D_800E39C8[];
extern Slot D_800E3648[];
extern void func_800B5F80(s32 arg0);

/* Process each active slot at the given coordinates. */
void func_800B6008(s32 x, s32 y) {
    s32 slot_index;
    s16 target_y;
    s16 target_x;

    slot_index = 0;
    target_x = x;
    target_y = y;
    do {
        if ((D_800E3648[slot_index].active != 0) &&
            (D_800E39C8[slot_index].x == target_x) &&
            (D_800E39C8[slot_index].y == target_y)) {
            func_800B5F80(slot_index);
        }
        slot_index += 1;
    } while (slot_index < 0x20);
}
