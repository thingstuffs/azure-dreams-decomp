#include "common.h"
#include "records/Rec_func_800B15B8_arg0.h"


typedef s32 M2C_UNK;


extern M2C_UNK func_8004E99C();


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
    void *slot_cursor;
    s32 slot_index;

    u8 *slots;

    slots = owner->unk_CC;
    for (slot_index = 0; slot_index < 5; slot_index++) {
        slot_cursor = slots + slot_index * 4;
        *((S_800B15B8_1 *)slot_cursor)->unk_10 = 0;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_38);
        *((S_800B15B8_1 *)slot_cursor)->unk_38 = 0;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_4C);
        *((S_800B15B8_1 *)slot_cursor)->unk_4C = 0;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_60);
        *((S_800B15B8_1 *)slot_cursor)->unk_60 = 0;
    }

}
