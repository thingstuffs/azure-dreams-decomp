/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"

extern s32 setResidentBitmapBit(s32 bit_id);
extern s32 serch_item_plown(s32 first_value, s32 second_value);

void func_800A97F8(u16 *record) {
    if (serch_item_plown(1, 0x12) != 0) {
        setResidentBitmapBit(0xAD);
        record[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
