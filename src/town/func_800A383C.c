#include "common.h"

typedef struct TownObject {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    u8 pad_06[2];
    s16 field_08;
    s16 field_0A;
    s32 field_0C;
    s16 field_10;
    s16 field_12;
    u8 pad_14[0x40];
    void *items[6];
    s16 field_6C;
    s16 field_6E;
    s16 field_70;
    s16 field_72;
    u8 pad_74[4];
    s16 field_78;
    s16 field_7A;
} TownObject;

extern void *func_800A1C94(TownObject *, s32, void *);

/* Initializes the object's items in reverse order and sets its default fields. */
s32 func_800A0F9C(TownObject *object, void *item_data, s32 item_count) {
    void **items;
    s32 remaining;

    remaining = item_count;
    items = object->items;
    while (remaining > 0) {
        remaining--;
        items[remaining] = func_800A1C94(object, remaining, item_data);
        if (items == 0) {
            return remaining + 1;
        }
    }

    object->field_00 = 0;
    object->field_02 = 0x800;
    object->field_04 = 0;
    object->field_08 = 0x180;
    object->field_10 = 0;
    object->field_0C = 0;
    object->field_12 = 0xFF;
    object->field_6C = 0x340;
    object->field_6E = 0;
    object->field_70 = 0x80;
    object->field_72 = 0x80;
    object->field_78 = 0x80;
    object->field_7A = 0xA0;
    object->field_0A = 0;
    return 0;
}
