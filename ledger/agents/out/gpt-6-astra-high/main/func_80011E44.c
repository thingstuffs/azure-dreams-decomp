#include "common.h"

extern void func_8004E994();

/* Clear words referenced by three pointer arrays, notifying func_8004E994 for the first array. */
void func_80024E44(void *object) {
    s32 slot_index;
    void *four_slot_base;
    void *ten_slot_base;

    for (slot_index = 0; slot_index < 3; slot_index++) {
        func_8004E994(*(*(s32 **) ((u8 *) object + slot_index * 4 + 0xB4C)));
        *(*(s32 **) ((u8 *) object + slot_index * 4 + 0xB4C)) = 0;
    }

    slot_index = 0;
    four_slot_base = object;
    for (; slot_index < 4; slot_index++) {
        *(*(s32 **) ((u8 *) four_slot_base + 0xB58)) = 0;
        four_slot_base = (u8 *) four_slot_base + 4;
    }

    slot_index = 0;
    ten_slot_base = object;
    for (; slot_index < 0xA; slot_index++) {
        *(*(s32 **) ((u8 *) ten_slot_base + 0xB68)) = 0;
        ten_slot_base = (u8 *) ten_slot_base + 4;
    }
}
