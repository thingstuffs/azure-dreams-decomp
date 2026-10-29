#include "common.h"
#include "records/Rec_func_800B15B8_arg0.h"


#include "slus.h"
#include "town/shop.h"





typedef struct S_800B15B8_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x24];
    s32 * unk_38;
    u8 pad_3C[0x10];
    s32 * unk_4C;
    u8 pad_50[0x10];
    s32 * unk_60;
} S_800B15B8_1;

/* Resets five slots and clears their associated resource handles. */
void reset_five_shop_slots(Rec_func_800B15B8_arg0 *owner) {
    S_800B15B8_1 *slot_cursor;
    s32 slot_index;

    u8 *slots;

    slots = owner->unk_CC;
    for (slot_index = 0; slot_index < 5; slot_index++) {
        slot_cursor = (S_800B15B8_1 *)(slots + slot_index * 4);
        *slot_cursor->unk_10 = 0;
        flag_optional_object_for_removal(*slot_cursor->unk_38);
        *slot_cursor->unk_38 = 0;
        flag_optional_object_for_removal(*slot_cursor->unk_4C);
        *slot_cursor->unk_4C = 0;
        flag_optional_object_for_removal(*slot_cursor->unk_60);
        *slot_cursor->unk_60 = 0;
    }

}
