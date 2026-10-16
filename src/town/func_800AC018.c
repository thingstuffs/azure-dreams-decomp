#include "common.h"
#include "shared/object_flags.h"

extern s32 setResidentBitmapBit(s32 bit_id);
extern s32 serch_item_plown(s32 first_value, s32 second_value);

/* Trigger action 0xAB and mark the record finished when the condition check succeeds. */
void townTriggerActionAndFinishRecord(u16 *record) {
    if (serch_item_plown(0xC, 0xF) != 0) {
        setResidentBitmapBit(0xAB);
        record[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
